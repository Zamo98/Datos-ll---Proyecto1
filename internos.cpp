#include "internos.h"
#include <QGraphicsItemGroup>
#include <QtGui>

Internos::Internos(QGraphicsItem* parent): QGraphicsItemGroup(parent){}

QRectF Internos:: boundingRect() const{
    return QRectF (0,0,95,40);
}

void Internos:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt::darkMagenta);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);

}
