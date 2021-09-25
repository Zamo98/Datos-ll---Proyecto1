#include <QApplication>
#include "juego.h"

Juego *juego = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    juego = new Juego();
    juego->Iniciar();

    return a.exec();

}
