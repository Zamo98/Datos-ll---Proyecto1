#include "bloques.h"


Bloques::Bloques(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{}

#include <QBrush>
#include <iostream>
#include <list>
#include <QGraphicsItemGroup>
using namespace std ;

list <double> :: iterator posi;
list <double> ComunesX;
list <double> ComunesY;
list <double> DoblesX;
list <double> DoblesY;
list <double> TriplesX;
list <double> TriplesY;
list <double> ProfundoX;
list <double> ProfundoY;
list <double> SorpresaX;
list <double> SorpresaY;

Bloques::Bloques(int _color, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{

    color= _color;
    //setRect( 0,0,60,25);
    //QBrush brush;
    //brush.setStyle(Qt::SolidPattern);
    //brush.setColor(QColor(90, 40, 50, 255));
    //setBrush(brush);

    if (color == 1){
        setRect( 0,0,95,55);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor("Red"));
        setBrush(brush);
    }
    if (color == 2){
        setRect( 0,0,95,55);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor("Green"));
        setBrush(brush);

    }
    if (color == 3){

        setRect( 0,0,95,55);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor("White"));
        setBrush(brush);

    }

    if (color == 4){

        setRect( 0,0,95,55);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor("Black"));
        setBrush(brush);

    }
    if (color == 5){

        setRect( 0,0,95,55);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor("Brown"));
        setBrush(brush);

    }

}

void Bloques:: Clasificacion(int _tipo, double _pX, double _pY){

// INSERTA CADA POSICION EN LA LISTA, SEGUN CORRESPONDA


   if (_tipo == 1 ){ //COMUN
        ComunesX.push_back(_pX);
        ComunesY.push_back(_pY);


    }


    if (_tipo == 2) { //DOBLE
        DoblesX.push_back(_pX+50);
        DoblesY.push_back(_pY+22);

    }

    if (_tipo == 3) { //TRIPLE
        TriplesX.push_back(_pX+50);
        TriplesY.push_back(_pY+22);


    }


    if (_tipo == 4) { //TRIPLE
        ProfundoX.push_back(_pX);
        ProfundoY.push_back(_pY);


    }

    if (_tipo == 5) { //TRIPLE
        SorpresaX.push_back(_pX);
        SorpresaY.push_back(_pY);


    }

    cout <<"Aquie es Clasi";  // SOLAMENTE PARA SABER SI EENTRA EN ESTA FUNCION



}





bool Bloques:: Comun(double _px,  double _py) {

    if (*find(ComunesX.begin(), ComunesX.end(), _px) == _px){ //Verifica si las posiciones estan en la lista
        if (*find(ComunesX.begin(), ComunesX.end(), _px) == _px){
            if (*find(ComunesY.begin(), ComunesY.end(), _py) == _py){

                if (*find(ComunesY.end(), ComunesY.end(), _py) ==_py) {

                    //BORRA LAS POSICIONES DE LAS LISTAS
                    //ComunesX.erase(remove(ComunesX.begin(), ComunesX.end(), _px), ComunesX.end());
                    //ComunesY.erase(remove(ComunesY.begin(), ComunesY.end(), _py), ComunesY.end());
                    return true;
                        }

                 }

            }

    }
    return false;


}


bool Bloques:: Doble(double _px, double _py){

    //Intentando otro metodo xD

    for(posi = DoblesX.begin(); posi == DoblesX.end(); posi++ ){
        if (*posi == _px){
            //DoblesX.erase(posi);
            return true;
        }
    }

    for(posi = DoblesY.begin(); posi == DoblesY.end(); posi++ ){
        if (*posi == _py){
            //DoblesX.erase(posi);
            return true;
        }
    }
    return false;

}

bool Bloques:: Triple(double _px, double _py){

    for(posi = TriplesX.begin(); posi == TriplesX.end(); posi++ ){
         if (*posi == _px){
             //TriplesX.erase(posi);
             return true;

             }

         }
    for(posi = TriplesY.begin(); posi == TriplesY.end(); posi++ ){
         if (*posi == _py){
             //TriplesX.erase(posi);
             return true;

             }

         }

    return false;

}

bool Bloques:: Profundo(double px, double py){

    if (*find(ProfundoX.begin(), ProfundoX.end(), px) == px){ //Verifica si las posiciones estan en la lista
            if (*find(ProfundoY.begin(), ProfundoY.end(), py) == py){

                return true;

            }
    }
    return false;

}
bool Bloques:: Sorpresa(double px, double py){

}






