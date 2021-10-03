#include "comun.h"
#include <QGraphicsItemGroup>
#include <QtGui>

Comun::Comun(QGraphicsItem* parent): QGraphicsItemGroup(parent){}

QRectF Comun:: boundingRect() const{
    return QRectF (0,0,95,40);
}

void Comun:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: yellow);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);

}
