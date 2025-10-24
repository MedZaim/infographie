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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRunButtonClicked();
    void onRefreshClicked();

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
};

#endif // MAINWINDOW_H
