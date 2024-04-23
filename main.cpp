#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Controlador controlador;
    MainWindow w(controlador);
    w.show();
    return a.exec();
}
