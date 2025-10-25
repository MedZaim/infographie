#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QStyle>
#include <QSettings>
#include <QPalette>
#include <QColor>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Force Fusion style so stylesheet fully controls widget rendering
    a.setStyle(QStyleFactory::create("Fusion"));

    // Read saved theme (default: dark)
    QSettings settings("infographie", "launcher");
    bool darkTheme = settings.value("ui/dark", true).toBool();

    // Debug: print active style and loaded theme to the console
    qDebug() << "[launcher] Qt style:" << qApp->style()->objectName() << " darkTheme=" << darkTheme;

    // Apply a minimal global stylesheet and palette immediately so created widgets follow it
    QString baseBg   = darkTheme ? "#161a1f" : "#f4f6f8";
    QString panelBg  = darkTheme ? "#1f242b" : "#ffffff";
    QString textCol  = darkTheme ? "#e6e9ee" : "#1c1e21";
    QString btnBg    = darkTheme ? "#27313a" : "#f0f2f5";
    QString accent   = darkTheme ? "#3b82f6" : "#2563eb";

    QString globalStyle = QString(R"(
        QWidget { background: %1; color: %3; }
        QToolBar { background: %2; }
        QGroupBox { background: %2; }
        QMenuBar { background: %2; }
        QStatusBar { background: %2; }
    )")
    .arg(baseBg, panelBg, textCol);

    a.setStyleSheet(globalStyle);

    QPalette pal = a.palette();
    pal.setColor(QPalette::Window, QColor(baseBg));
    pal.setColor(QPalette::WindowText, QColor(textCol));
    pal.setColor(QPalette::Button, QColor(btnBg));
    pal.setColor(QPalette::ButtonText, QColor(textCol));
    // Additional roles to ensure consistent look
    pal.setColor(QPalette::Base, QColor(panelBg));
    pal.setColor(QPalette::AlternateBase, QColor(baseBg));
    pal.setColor(QPalette::ToolTipBase, QColor(panelBg));
    pal.setColor(QPalette::ToolTipText, QColor(textCol));
    pal.setColor(QPalette::Text, QColor(textCol));
    pal.setColor(QPalette::BrightText, QColor("#ff0000"));
    pal.setColor(QPalette::Highlight, QColor(accent));
    pal.setColor(QPalette::HighlightedText, QColor("#ffffff"));
    a.setPalette(pal);

    MainWindow w;
    w.show();
    return a.exec();
}
