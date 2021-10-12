/**
  * @file triples.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora.
  */

#include "triples.h"
#include <QGraphicsItemGroup>
#include <QtGui>

/**
 * @brief Triples::Triples Clase para la creación de bloques dobles.
 * @param _Vidas Este parametro es para saber cuantas colisiones resiste el bloque.
 * @param parent Parametro por defecto.
 */
Triples::Triples(int _Vidas,QGraphicsItem* parent): QGraphicsItemGroup(parent)
{
    Vida = _Vidas;
}
QRectF Triples:: boundingRect() const{
    return QRectF (0,0,95,40);
}

/**
 * @brief Triples::paint Este metodo sirve para las caracteristicas de diseño del bloque
 * @param painter Parametro por defecto.
 * @param option Parametro por defecto.
 * @param widget Parametro por defecto.
 */
void Triples:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: green);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);
}
/**
 * @brief Triples::Vidas Este metodo sirve para que el bloque se rompa en 2 colisiones
 * @return bool, que es de utilidad para saber cuando se tiene que destruir.
 */

bool Triples::Vidas(){
    Vida = (Vida - 1);
    //cout<<"La vida es"<<" "<<Vida<<" "<<":D";
    if(Vida <= 0){
        return true;
    }
    else{
        return false;
    }
}

