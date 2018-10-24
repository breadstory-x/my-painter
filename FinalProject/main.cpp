#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MyPainter mypainter;
    //mypainter.show();
    MainWindow w;
    w.show();

    return a.exec();
}
