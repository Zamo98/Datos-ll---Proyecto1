/**
  * @file internos.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora.
  */

#include "internos.h"
#include <QGraphicsItemGroup>
#include <QtGui>
/**
 * @brief Internos::Internos Clase para la creacion de los bloques internos.
 * @param parent Parametro por defecto.
 */
Internos::Internos(QGraphicsItem* parent): QGraphicsItemGroup(parent){}

QRectF Internos:: boundingRect() const{
    return QRectF (0,0,95,40);
}
/**
 * @brief Internos::paint Este metodo sirve para las características de diseño del bloque
 * @param painter Parametro por defecto.
 * @param option Parametro por defecto.
 * @param widget Parametro por defecto.
 */
void Internos:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt::magenta);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);

}
