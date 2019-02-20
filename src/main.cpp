#include "mainwindow.h"
#include <QApplication>

QString g_strInitDir;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_strInitDir = qApp->applicationDirPath();
    MainWindow w;
    w.show();

    return a.exec();
}
