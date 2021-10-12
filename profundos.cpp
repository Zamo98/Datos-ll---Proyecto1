#include "profundos.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>
using namespace std ;
/**
 * @brief Profundos::Profundos
 * Clase para la creacion de los bloques profundos
 * @param parent
 */

Profundos::Profundos(QGraphicsItem* parent): QGraphicsItemGroup(parent)
{

}
QRectF Profundos:: boundingRect() const{
    return QRectF (0,0,95,40);
}


void Profundos:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: black);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);


}

/**
 * @brief Profundos::Masprofundidad
 * Metodo que aumenta la profundidad
 * @param x, profundidad actual
 */

void Profundos::Masprofundidad(int x){
    x += 1;
}
/**
 * @brief Profundos::Menosprofundidad
 * Disminuye la profundidad al colisionar con el bloque
 * @param x, profundidad actual
 */

void Profundos::Menosprofundidad(int x){
    x-= 1;
 }
/**
 * @brief Profundos::cant_profundidad
 * @return entero, sirve para ver cuantos niveles de profundidad se tiene
 */

int Profundos::cant_profundidad(){
    return profundida;
}
