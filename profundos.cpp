/**
  * @file profundos.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora.
  */

#include "profundos.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>
using namespace std ;
/**
 * @brief Profundos::Profundos Clase para la creacion de los bloques profundos
 * @param parent Parametro por defecto.
 */

Profundos::Profundos(QGraphicsItem* parent): QGraphicsItemGroup(parent){}

QRectF Profundos:: boundingRect() const{
    return QRectF (0,0,95,40);
}

/**
 * @brief Profundos::paint Este metodo sirve para las caracteristicas de diseño del bloque.
 * @param painter Parametro por defecto.
 * @param option Parametro por defecto.
 * @param widget Parametro por defecto.
 */
void Profundos:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: black);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);
}

/**
 * @brief Profundos::Masprofundidad Metodo que aumenta la profundidad.
 * @param x, profundidad actual
 */

void Profundos::Masprofundidad(int x){
    x += 1;
}
/**
 * @brief Profundos::Menosprofundidad Disminuye la profundidad al colisionar con el bloque
 * @param x, profundidad actual
 */

void Profundos::Menosprofundidad(int x){
    x-= 1;
 }
/**
 * @brief Profundos::cant_profundidad Metodo que retorna la profundidad actual.
 * @return entero, sirve para ver cuantos niveles de profundidad se tiene
 */

int Profundos::cant_profundidad(){
    return profundida;
}
