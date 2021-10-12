#include "internos.h"
#include <QGraphicsItemGroup>
#include <QtGui>
/**
 * @brief Internos::Internos
 * Clase para la creacion de los bloques internos
 * @param parent
 */
Internos::Internos(QGraphicsItem* parent): QGraphicsItemGroup(parent){}

QRectF Internos:: boundingRect() const{
    return QRectF (0,0,95,40);
}
/**
 * @brief Internos::paint
 * Este metodo sirve para las caracteristicas de diseño del bloque
 * @param painter
 * @param option
 * @param widget
 */
void Internos:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt::darkMagenta);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);

}
