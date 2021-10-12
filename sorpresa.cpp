/**
  * @file sorpresa.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora.
  */

#include "sorpresa.h"
#include "dobles.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>
#include "raqueta.h"
#include "juego.h"
#include "bola.h"
extern Juego* juego;
using namespace std ;
/**
 * @brief Sorpresa::Sorpresa Clase para la creacion de bloques sorpresa
 * @param Ksorpresa Tipo de sorpresa.
 * @param parent Parametro por defecto.
 */
Sorpresa::Sorpresa(int Ksorpresa, QGraphicsItem* parent): QGraphicsItemGroup(parent)
{
    _Ksorpresa = Ksorpresa;
}

QRectF Sorpresa:: boundingRect() const{
    return QRectF (0,0,95,40);
}
/**
 * @brief Sorpresa::paint Este metodo sirve para las caracteristicas de diseño del bloque
 * @param painter Parametro por defecto.
 * @param option Parametro por defecto.
 * @param widget Parametro por defecto.
 */
void Sorpresa:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: cyan);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);
}

/**
 * @brief Sorpresa::KSorpresa Este metodo sirve para saber que sorpresa tiene cada bloque
 */

void Sorpresa::KSorpresa(){
    cout <<"HOLA EN SORPRESA";
    if( _Ksorpresa ==1){
        cout <<" AURAQUETA";
        juego->raqueta->aumentarRaqueta();
    }
    if( _Ksorpresa ==2){
        cout <<" RERAQUETA";
        if(juego->raqueta->nuevoAncho != 50){
            juego->raqueta->reducirRaqueta();
        }
        else{
            juego->juegoTerminado();
        }

    }
    if( _Ksorpresa ==3){
        cout<< "REBOLA";
        juego->bola->reducirBola();
    }
    if( _Ksorpresa ==4){
        cout <<"AUBOLA";
        juego->bola->aumentarBola();
    }

}


        
