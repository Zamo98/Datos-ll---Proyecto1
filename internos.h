#ifndef INTERNOS_H
#define INTERNOS_H

#include <QGraphicsItem>
#include <QGraphicsItemGroup>

class Internos : public QGraphicsItemGroup
{
public:
    Internos(QGraphicsItem* parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect ()const;
    QGraphicsItemGroup addToGroup(QGraphicsItem *item);
};

#endif // INTERNOS_H
