#include "dobles.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>

using namespace std;
/**
 * @brief Dobles::Dobles
 * Clase para la creacion de bloques dobles
 * @param _Vida, este parametro es para saber cuantas colisiones resiste el bloque
 * @param parent
 */

Dobles::Dobles(int _Vida, QGraphicsItem* parent): QGraphicsItemGroup(parent)
{
    Vida = _Vida;
}

QRectF Dobles:: boundingRect() const{
    return QRectF (0,0,95,40);
}

/**
 * @brief Dobles::paint
 * Este metodo sirve para las caracteristicas de diseño del bloque
 * @param painter
 * @param option
 * @param widget
 */

void Dobles:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    
    painter->setBrush (Qt:: red);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);
}
/**
 * @brief Dobles::Vidas
 * Este metodo sirve para que el bloque se rompa en 2 colisiones
 * @return bool, que es de utilidad para saber cuando se tiene que destruir.
 */

bool Dobles::Vidas(){
    Vida -= 1;
    cout << "<La vida es" << " " <<Vida<< " " << ":D";
    if (Vida <= 0){
        return true;
    }
    else{
        return false;
    }
}


