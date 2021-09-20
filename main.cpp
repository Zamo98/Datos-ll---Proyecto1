#include "mainwindow.h"

#include <QApplication>
#include "juego.h"

Juego *juego=nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow ventana;
    //ventana.show();
    juego = new Juego();
    return a.exec();
}
