#include "mainwindow.h"

#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow ventana;
    ventana.show();
    cout<<"Hola Mundo"<<endl;
    return a.exec();
}
