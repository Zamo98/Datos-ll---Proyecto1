#include "bloques.h"
#include <QBrush>

Bloques::Bloques(QGraphicsItem *parent) :QGraphicsRectItem(parent)
{
    setRect( 0,0,60,25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(90, 40, 50, 255));
    setBrush(brush);

}
