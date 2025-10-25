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
#include <QToolBar>
#include <QAction>
#include <QStyle>
#include <QFont>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QComboBox>
#include <QStyleFactory>
#include <QTimer>
#include <QResizeEvent>
#include "flowlayout.h"

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

    // Load persisted theme choice (default: dark)
    QSettings settings("infographie", "launcher");
    darkTheme = settings.value("ui/dark", true).toBool();

    // Connect refresh button
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);

    // Enhance the UI (toolbar, theme, header styling)
    setupUiEnhancements();

    // Connect new footer widgets if they exist
    if (ui->openBuildExesButton) {
        connect(ui->openBuildExesButton, &QPushButton::clicked, this, &MainWindow::onOpenBuildDir);
    }
    if (ui->openSourceButton) {
        connect(ui->openSourceButton, &QPushButton::clicked, this, &MainWindow::onOpenSourceDir);
    }
    if (ui->themeCombo) {
        QComboBox *combo = ui->themeCombo;
        // Ensure combo has items (UI created them in .ui) and set to saved state
        combo->setCurrentIndex(darkTheme ? 1 : 0);
        connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
            bool d = (index == 1);
            applyTheme(d);
            QSettings s("infographie", "launcher");
            s.setValue("ui/dark", d);
        });
    }

    // Create resize debounce timer
    resizeDebounceTimer = new QTimer(this);
    resizeDebounceTimer->setSingleShot(true);
    resizeDebounceTimer->setInterval(160); // 160ms debounce
    connect(resizeDebounceTimer, &QTimer::timeout, this, &MainWindow::onResizeDebounced);

    buildDynamicLauncher();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- UI Enhancements --------------------------------------------------------

void MainWindow::setupUiEnhancements() {
    // Window min size and title
    // Removed forced minimum size to allow flexible resizing
    // setMinimumSize(900, 650);
    setWindowTitle("Infographie Launcher");

    // Header label styling
    if (auto lbl = ui->labelHeader) {
        QFont f = lbl->font();
        f.setPointSize(16);
        f.setBold(true);
        lbl->setFont(f);
        lbl->setText("Infographie Projects Launcher");
        lbl->setMargin(8);
    }

    // Toolbar with modern actions
    QToolBar *tb = addToolBar("Main");
    tb->setMovable(false);
    tb->setIconSize(QSize(18, 18));

    QAction *actRefresh = new QAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("Refresh"), this);
    QAction *actTheme   = new QAction(style()->standardIcon(QStyle::SP_DialogYesButton), tr("Toggle Theme"), this);
    QAction *actPickGpp = new QAction(style()->standardIcon(QStyle::SP_DirOpenIcon), tr("Pick g++"), this);
    QAction *actOpenOut = new QAction(style()->standardIcon(QStyle::SP_DirIcon), tr("Open build_exes"), this);
    QAction *actOpenSrc = new QAction(style()->standardIcon(QStyle::SP_DirIcon), tr("Open src_graphics"), this);

    connect(actRefresh, &QAction::triggered, this, &MainWindow::onRefreshClicked);
    connect(actTheme,   &QAction::triggered, this, &MainWindow::onToggleTheme);
    connect(actPickGpp, &QAction::triggered, this, &MainWindow::onPickCompiler);
    connect(actOpenOut, &QAction::triggered, this, &MainWindow::onOpenBuildDir);
    connect(actOpenSrc, &QAction::triggered, this, &MainWindow::onOpenSourceDir);

    tb->addAction(actRefresh);
    tb->addSeparator();
    tb->addAction(actTheme);
    tb->addSeparator();
    tb->addAction(actPickGpp);
    tb->addAction(actOpenOut);
    tb->addAction(actOpenSrc);

    // Add a persistent status label to display current theme and style
    QLabel *themeLabel = new QLabel(this);
    themeLabel->setObjectName("themeStatusLabel");
    themeLabel->setText("Theme: -- | Style: --");
    statusBar()->addPermanentWidget(themeLabel);

    // Ensure footer buttons have a consistent height
    // Compute and store standard button height from the application's font metrics
    standardButtonHeight = fontMetrics().height() + 14; // base padding
    if (ui->refreshButton) ui->refreshButton->setFixedHeight(standardButtonHeight);
    if (ui->openBuildExesButton) ui->openBuildExesButton->setFixedHeight(standardButtonHeight);
    if (ui->openSourceButton) ui->openSourceButton->setFixedHeight(standardButtonHeight);
    if (ui->themeCombo) ui->themeCombo->setFixedHeight(standardButtonHeight);

    // Apply initial theme
    applyTheme(darkTheme);
}

void MainWindow::applyTheme(bool dark) {
    darkTheme = dark;
    QString baseBg   = dark ? "#161a1f" : "#f4f6f8";
    QString panelBg  = dark ? "#1f242b" : "#ffffff";
    QString textCol  = dark ? "#e6e9ee" : "#1c1e21";
    QString accent   = dark ? "#3b82f6" : "#2563eb";
    QString btnBg    = dark ? "#27313a" : "#f0f2f5";
    QString btnBgHov = dark ? "#2d3943" : "#e6e9ee";
    QString border   = dark ? "#2a3139" : "#d0d7de";

    // Use Fusion style to ensure stylesheet takes full effect independent of Windows theme
    qApp->setStyle(QStyleFactory::create("Fusion"));

    QString style = QString(R"(
        QMainWindow { background: %1; }
        QWidget { background: %1; color: %3; }
        QToolBar { background: %2; border: 0; spacing: 8px; padding: 6px; }
        QStatusBar { background: %2; color: %3; }
        QLabel#labelHeader { color: %3; }
        QScrollArea { background: transparent; border: none; }
        QGroupBox { background: %2; border: 1px solid %6; border-radius: 8px; margin-top: 12px; }
        QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 2px 6px; color: %3; }
        QPushButton { background: %5; color: %3; border: 1px solid %6; border-radius: 6px; padding: 6px 10px; }
        QPushButton:hover { background: %7; }
        QPushButton:pressed { background: %6; }
        QMenuBar { background: %2; color: %3; }
        QComboBox { background: %5; color: %3; }
    )")
    .arg(baseBg, panelBg, textCol, accent, btnBg, border, btnBgHov);

    qApp->setStyleSheet(style);

    // Ensure the central widget and scroll area viewport actually use styled background
    if (ui && ui->centralwidget) {
        ui->centralwidget->setAttribute(Qt::WA_StyledBackground, true);
        ui->centralwidget->setAutoFillBackground(true);
    }
    if (ui && ui->scrollArea && ui->scrollArea->viewport()) {
        QWidget *vp = ui->scrollArea->viewport();
        vp->setAttribute(Qt::WA_StyledBackground, true);
        vp->setAutoFillBackground(true);
    }
    if (menuBar()) menuBar()->setAttribute(Qt::WA_StyledBackground, true);
    if (statusBar()) statusBar()->setAttribute(Qt::WA_StyledBackground, true);

    // Also update the application palette so any native-controls fallback uses correct colors
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QColor(baseBg));
    pal.setColor(QPalette::WindowText, QColor(textCol));
    pal.setColor(QPalette::Button, QColor(btnBg));
    pal.setColor(QPalette::ButtonText, QColor(textCol));
    pal.setColor(QPalette::Base, QColor(panelBg));
    pal.setColor(QPalette::AlternateBase, QColor(baseBg));
    pal.setColor(QPalette::ToolTipBase, QColor(panelBg));
    pal.setColor(QPalette::ToolTipText, QColor(textCol));
    pal.setColor(QPalette::Text, QColor(textCol));
    pal.setColor(QPalette::BrightText, QColor("#ff0000"));
    pal.setColor(QPalette::Highlight, QColor(accent));
    pal.setColor(QPalette::HighlightedText, QColor("#ffffff"));
    qApp->setPalette(pal);

    // Update persistent status label with the active style and theme
    if (QLabel *lbl = findChild<QLabel*>("themeStatusLabel")) {
        lbl->setText(QString("Theme: %1 | Style: %2").arg(dark ? "Dark" : "Light").arg(qApp->style()->objectName()));
    }

    // Status tip
    statusBar()->showMessage(dark ? tr("Dark theme applied") : tr("Light theme applied"), 1500);
}

void MainWindow::onToggleTheme() {
    applyTheme(!darkTheme);
}

void MainWindow::onPickCompiler() {
    QString startDir = QFileInfo(gppPath).absolutePath();
    QString file = QFileDialog::getOpenFileName(this, tr("Select g++ executable"), startDir, tr("Executables (*.exe)"));
    if (!file.isEmpty()) {
        gppPath = file;
        statusBar()->showMessage(tr("Compiler set: %1").arg(gppPath), 3000);
    }
}

void MainWindow::onOpenBuildDir() {
    // Compute build_exes at project root
    QDir outDir = QDir(QDir(sourceRoot).absolutePath());
    outDir.cdUp(); // code_graphics
    outDir.cdUp(); // project root
    QString path = outDir.filePath("build_exes");
    QDir().mkpath(path);
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::onOpenSourceDir() {
    // Open the source root (code_graphics/src_graphics) in the file explorer
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir(sourceRoot).absolutePath()));
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // Start or restart debounce timer on resize
    if (resizeDebounceTimer)
        resizeDebounceTimer->start();

    // allow base class to handle default behavior
    QMainWindow::resizeEvent(event);
}

void MainWindow::onResizeDebounced()
{
    // rebuild layout based on new available width
    buildDynamicLauncher();
}

void MainWindow::buildDynamicLauncher()
{
    // Use the scrollArea widget from the UI and populate its contents
    QWidget *contents = ui->scrollArea->widget();
    if (!contents) {
        // fallback: nothing to do
        return;
    }

    // prefer a FlowLayout to place panels and allow wrapping like flex
    QLayout *oldLayout = contents->layout();
    if (oldLayout && qobject_cast<FlowLayout*>(oldLayout) == nullptr) {
        // remove previous layout widgets
        clearLayout(oldLayout);
        delete oldLayout;
        oldLayout = nullptr;
    }

    FlowLayout *flow = qobject_cast<FlowLayout*>(contents->layout());
    if (!flow) {
        flow = new FlowLayout(contents, 10, 12, 12); // margins, hSpacing, vSpacing
        contents->setLayout(flow);
    }

    // clear previous items from flow
    clearLayout(flow);

    QDir rootDir(sourceRoot);
    if (!rootDir.exists()) {
        QLabel *lbl = new QLabel(tr("Source folder not found: %1").arg(sourceRoot), contents);
        flow->addWidget(lbl);
        return;
    }

    // estimate a minimum reasonable panel width (including margins)
    const int minPanelWidth = 220; // make a bit bigger for readable panels

    QFileInfoList subs = rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &sub : subs) {
        QString subPath = sub.absoluteFilePath();
        QStringList cppFiles = cppFilesInDir(subPath);
        if (cppFiles.isEmpty())
            continue; // skip empty panels

        QGroupBox *grp = new QGroupBox(sub.fileName(), contents);
        // Make group boxes expand horizontally so they share available width in their cell
        grp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        grp->setMinimumWidth(minPanelWidth);

        QVBoxLayout *grpLayout = new QVBoxLayout(grp);
        grpLayout->setSpacing(6);
        grpLayout->setContentsMargins(10, 10, 10, 10);

        for (const QString &cpp : cppFiles) {
            QFileInfo fi(cpp);
            QString baseName = fi.baseName();
            QPushButton *btn = new QPushButton(baseName, grp);
            btn->setCursor(Qt::PointingHandCursor);
            // Buttons expand to fill group width
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            // Set a uniform fixed height for all dynamic buttons
            QFontMetrics fm(btn->font());
            int btnHeight = qMax(standardButtonHeight, fm.height() + 14);
            btn->setFixedHeight(btnHeight);

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

        flow->addWidget(grp);
    }

    // Ensure flow layout takes remaining space nicely
    contents->adjustSize();
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
