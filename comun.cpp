#include "comun.h"
#include <QGraphicsItemGroup>
#include <QtGui>

/**
 * @brief Comun::Comun
 * Esta clase es para la creacion del bloque comun
 * @param parent
 */

Comun::Comun(QGraphicsItem* parent): QGraphicsItemGroup(parent){}

QRectF Comun:: boundingRect() const{
    return QRectF (0,0,95,40);
}
/**
 * @brief Comun::paint
 * Este metodo sirve para las caracteristicas de diseño del bloque
 * @param painter
 * @param option
 * @param widget
 */

void Comun:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: yellow);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);

}
