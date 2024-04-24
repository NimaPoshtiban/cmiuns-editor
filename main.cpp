#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Cminus Editor");
    QApplication::setApplicationDisplayName("Cminus Editor");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setDesktopFileName("cminus_editor");
    QApplication::setOrganizationDomain("Poshtibannima@gmail.com");
    MainWindow w;

    w.show();
    return a.exec();
}
