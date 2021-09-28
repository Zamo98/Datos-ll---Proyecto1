#include "dobles.h"

#include <QGraphicsItemGroup>
#include<QtGui>
Dobles::Dobles(QGraphicsItem* parent): QGraphicsItemGroup(parent)
{

}

QRectF Dobles:: boundingRect() const{
    return QRectF (0,0,95,55);
}

void Dobles:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: red);
    painter -> drawRoundedRect(0,0, 95, 55, 10, 10);




}
