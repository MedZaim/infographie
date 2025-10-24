#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QProcess>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMessageBox>
#include <QCoreApplication>
#include <QLabel>
#include <QFile>
#include <QLayout>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QGridLayout>
#include <QRegularExpression>
#include <QTemporaryDir>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuration - adjust these if needed
    // Prefer the 32-bit TDM-GCC user requested
    gppPath = R"(C:/TDM-GCC-32/bin/g++.exe)";
    // sourceRoot relative to the application binary: go up two levels to project root then into code_graphics/src_graphics
    QString appDir = QCoreApplication::applicationDirPath();
    QDir d(appDir);
    // try to find the project root by walking up until we find a folder that contains code_graphics
    QString foundRoot;
    QDir cur = d;
    for (int i = 0; i < 6; ++i) {
        if (cur.exists("code_graphics")) {
            foundRoot = cur.absolutePath();
            break;
        }
        cur.cdUp();
    }
    if (foundRoot.isEmpty()) {
        // fallback: assume current working dir's parent structure
        foundRoot = QDir::current().absoluteFilePath(".");
    }

    sourceRoot = QDir(foundRoot).filePath("code_graphics/src_graphics");

    // Add the BGI graphics folder include path if present
    // User requested these libraries
    extraLibs = "-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32";

    // Connect refresh button
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);

    buildDynamicLauncher();
}

MainWindow::~MainWindow()
{
    delete ui;
}

static void clearLayout(QLayout *layout) {
    if (!layout) return;
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *w = item->widget()) {
            delete w;
        } else if (QLayout *l = item->layout()) {
            clearLayout(l);
            delete l;
        }
        delete item;
    }
}

QStringList MainWindow::cppFilesInDir(const QString &path) const
{
    QStringList files;
    QDir dir(path);
    if (!dir.exists())
        return files;

    QFileInfoList list = dir.entryInfoList(QStringList() << "*.cpp", QDir::Files | QDir::Readable);
    for (const QFileInfo &fi : list)
        files << fi.absoluteFilePath();
    return files;
}

QString MainWindow::makeCompileCommand(const QString &cppPath, const QString &outExe) const
{
    // Build arguments vector for QProcess
    // Add include for code_graphics/Graphics if exists
    QString includes = "-I" + QDir(sourceRoot).absoluteFilePath("../Graphics");
    QStringList args;
    args << cppPath << includes << "-L" + QDir(sourceRoot).absoluteFilePath("../Graphics") << extraLibs << "-o" << outExe;
    return args.join(' ');
}

void MainWindow::buildDynamicLauncher()
{
    // Use the scrollArea widget from the UI and populate its contents
    QWidget *contents = ui->scrollArea->widget();
    if (!contents) {
        // fallback: nothing to do
        return;
    }

    // prefer a QGridLayout to place panels in rows of two
    QLayout *oldLayout = contents->layout();
    if (oldLayout && qobject_cast<QGridLayout*>(oldLayout) == nullptr) {
        // remove previous layout widgets
        clearLayout(oldLayout);
        delete oldLayout;
        oldLayout = nullptr;
    }

    QGridLayout *grid = qobject_cast<QGridLayout*>(contents->layout());
    if (!grid) {
        grid = new QGridLayout(contents);
        grid->setSpacing(8);
        grid->setContentsMargins(6,6,6,6);
        contents->setLayout(grid);
    }

    // clear previous items from grid
    clearLayout(grid);

    QDir rootDir(sourceRoot);
    if (!rootDir.exists()) {
        QLabel *lbl = new QLabel(tr("Source folder not found: %1").arg(sourceRoot), contents);
        grid->addWidget(lbl, 0, 0);
        return;
    }

    // iterate subdirectories (panels) and add them into a 2-column grid
    QFileInfoList subs = rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    int row = 0;
    int col = 0;
    const int columns = 4; // show 4 panels per row as requested

    for (const QFileInfo &sub : subs) {
        QString subPath = sub.absoluteFilePath();
        QStringList cppFiles = cppFilesInDir(subPath);
        if (cppFiles.isEmpty())
            continue; // skip empty panels

        QGroupBox *grp = new QGroupBox(sub.fileName(), contents);
        QVBoxLayout *grpLayout = new QVBoxLayout(grp);

        for (const QString &cpp : cppFiles) {
            QFileInfo fi(cpp);
            QString baseName = fi.baseName();
            QPushButton *btn = new QPushButton(baseName, grp);
            // store the path to the source file and intended exe output on the button
            btn->setProperty("cppPath", cpp);
            // output exe path placed in a build_exes folder inside found project root
            QDir outDir = QDir(QDir(sourceRoot).absolutePath());
            outDir.cdUp(); // move to code_graphics
            outDir.cdUp(); // move to project root
            outDir.mkdir("build_exes");
            QString exePath = QDir(outDir.filePath("build_exes")).absoluteFilePath(baseName + ".exe");
            btn->setProperty("exePath", exePath);

            connect(btn, &QPushButton::clicked, this, &MainWindow::onRunButtonClicked);
            grpLayout->addWidget(btn);
        }
        grp->setLayout(grpLayout);

        grid->addWidget(grp, row, col);
        col++;
        if (col >= columns) { col = 0; row++; }
    }

    // If the last row is partial (col != 0), add a horizontal spacer item that spans remaining columns
    if (col != 0) {
        int remaining = columns - col;
        QSpacerItem *hSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        // place the spacer in the next cell and span the remaining columns to push panels to the left
        grid->addItem(hSpacer, row, col, 1, remaining);
    }

    // push rows up so content stays at the top
    grid->setRowStretch(row + 1, 1);
}

static bool tryRemoveExeWithKillOption(QWidget *parent, const QString &exePath, const QString &exeName) {
    QFile f(exePath);
    if (!f.exists()) return true;
    if (f.remove()) return true;

    // Couldn't remove — likely in use. Offer to kill process
    QMessageBox::StandardButton b = QMessageBox::question(parent, QObject::tr("File locked"),
        QObject::tr("The executable %1 is in use and cannot be overwritten.\nWould you like to try to terminate it?\n(Requires privileges)").arg(exeName),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (b == QMessageBox::Yes) {
        // Run taskkill to force close the exe
        QProcess kill;
        QStringList args;
        args << "/F" << "/IM" << exeName;
        kill.start("taskkill", args);
        bool started = kill.waitForStarted(3000);
        if (!started) return false;
        kill.waitForFinished(5000);
        // try remove again
        return f.remove();
    }
    return false;
}

static QString detectEntryPointName(const QString &cppPath) {
    QFile f(cppPath);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return QString();
    QString content = QString::fromUtf8(f.readAll());

    // Prefer a standard main
    QRegularExpression reMain("\\bint\\s+main\\s*\\(\\s*(?:int\\s*\\w*\\s*,\\s*char\\s*\\*\\s*\\*\\s*\\w*\\s*)?\\)");
    if (reMain.match(content).hasMatch()) return QStringLiteral("main");

    // Look for functions named like int main_xxx()
    QRegularExpression reAlt("\\bint\\s+(main_[A-Za-z0-9_]+)\\s*\\(");
    QRegularExpressionMatch m = reAlt.match(content);
    if (m.hasMatch()) return m.captured(1);

    return QString();
}

static QString createWrapperForEntry(const QString &entryName, const QString &outDir, const QString &baseName) {
    QString wrapperPath = QDir(outDir).filePath(baseName + "_wrapper.cpp");
    QFile wf(wrapperPath);
    if (!wf.open(QIODevice::WriteOnly | QIODevice::Text)) return QString();
    QTextStream ts(&wf);
    ts << "// Auto-generated wrapper for UI launcher\n";
    ts << "int " << entryName << "();\n";
    ts << "int main(){ return " << entryName << "(); }\n";
    wf.close();
    return wrapperPath;
}

void MainWindow::onRunButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn)
        return;
    QString cppPath = btn->property("cppPath").toString();
    QString exePath = btn->property("exePath").toString();
    if (cppPath.isEmpty() || exePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Missing path information."));
        return;
    }

    QFileInfo exeFi(exePath);
    QString exeName = exeFi.fileName();

    // If exe exists, try to remove it (or offer to kill running process)
    if (!tryRemoveExeWithKillOption(this, exePath, exeName)) {
        QMessageBox::critical(this, tr("Cannot overwrite"), tr("Cannot remove or terminate running executable: %1").arg(exeName));
        return;
    }

    // Determine entry point and optional wrapper
    QString entry = detectEntryPointName(cppPath);
    QString wrapperPath;
    if (entry.isEmpty()) {
        QMessageBox::critical(this, tr("No entry point"), tr("%1 does not contain a main() or main_*() function.").arg(QFileInfo(cppPath).fileName()));
        return;
    }
    if (entry != QLatin1String("main")) {
        // Create wrapper next to output exe to persist between runs
        QDir outDir = QFileInfo(exePath).dir();
        QString baseName = QFileInfo(cppPath).baseName();
        wrapperPath = createWrapperForEntry(entry, outDir.absolutePath(), baseName);
        if (wrapperPath.isEmpty()) {
            QMessageBox::critical(this, tr("Wrapper error"), tr("Failed to create wrapper for %1").arg(entry));
            return;
        }
    }

    // Prepare process to compile
    QProcess compile;
    QStringList args;
    args << cppPath;
    if (!wrapperPath.isEmpty()) args << wrapperPath;
    // include the project's Graphics include if present
    QString graphicsInclude = QDir(sourceRoot).absoluteFilePath("../Graphics");
    QString includsInclude = QDir(sourceRoot).absoluteFilePath("../includs");
    // project root (two levels up from sourceRoot)
    QDir projectRootDir = QDir(QDir(sourceRoot).absolutePath());
    projectRootDir.cdUp();
    projectRootDir.cdUp();
    QString projectRoot = projectRootDir.absolutePath();
    args << "-I" + graphicsInclude;
    args << "-I" + includsInclude;
    args << "-I" + projectRoot; // allow includes like code_graphics/Graphics/graphics.h
    args << "-L" + graphicsInclude;

    // Add C++17 standard to support Qt6
    args << "-std=c++17";
    // Enable optimizations
    args << "-O2";

    // Define PI macro for sources that use it without defining
    args << "-DPI=3.14159265358979323846";

    // split extraLibs into tokens
    args.append(extraLibs.split(' ', Qt::SkipEmptyParts));
    // link libm explicitly for TDM-GCC math symbols
    args << "-lm";

    // Ensure the produced exe uses the console subsystem (prevents linker looking for WinMain)
    args << "-mconsole";
    args << "-Wl,-subsystem,console";

    args << "-o" << exePath;

    // Run the compiler (synchronously here, could be async)
    compile.start(gppPath, args);
    bool started = compile.waitForStarted(10000);
    if (!started) {
        QMessageBox::critical(this, tr("Compile error"), tr("Failed to start compiler: %1").arg(gppPath));
        return;
    }
    bool finished = compile.waitForFinished(60000); // wait up to 60s for heavier samples
    QString stdOut = compile.readAllStandardOutput();
    QString stdErr = compile.readAllStandardError();

    if (!finished || compile.exitCode() != 0) {
        QMessageBox::critical(this, tr("Compile failed"), tr("Exit code: %1\nOutput:\n%2\nErrors:\n%3").arg(compile.exitCode()).arg(stdOut).arg(stdErr));
        return;
    }

    // Run the produced exe detached
    bool ok = QProcess::startDetached(exePath);
    if (!ok) {
        QMessageBox::warning(this, tr("Run failed"), tr("Could not start %1").arg(exePath));
    }
}

void MainWindow::onRefreshClicked()
{
    buildDynamicLauncher();
}
