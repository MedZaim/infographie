#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QGroupBox;
class QTimer;
class QResizeEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRunButtonClicked();
    void onRefreshClicked();

    // New UI actions
    void onToggleTheme();
    void onPickCompiler();
    void onOpenBuildDir();
    void onOpenSourceDir(); // new: open code_graphics/src_graphics

    // resize debounce handler
    void onResizeDebounced();

private:
    Ui::MainWindow *ui;

    // helper functions
    void buildDynamicLauncher();
    QStringList cppFilesInDir(const QString &path) const;
    QString makeCompileCommand(const QString &cppPath, const QString &outExe) const;

    // configuration (can be adjusted)
    QString sourceRoot; // relative to project root
    QString gppPath;    // full path to g++ executable
    QString extraLibs;  // extra linker flags

    // UI enhancement helpers
    void setupUiEnhancements();
    void applyTheme(bool dark);

    bool darkTheme = true;

    // debounce timer used to avoid rebuilding on every pixel of resize
    QTimer *resizeDebounceTimer = nullptr;

    // standard button height for uniform buttons
    int standardButtonHeight = 0;

protected:
    // override resizeEvent to trigger responsive layout (debounced)
    void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINWINDOW_H
