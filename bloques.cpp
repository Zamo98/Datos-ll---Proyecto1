#include "bloques.h"
#include <QBrush>

Bloques::Bloques(QGraphicsItem *parent) :QGraphicsRectItem(parent)
{
    setRect( 0,0,60,25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("red"));
    setBrush(brush);


}
