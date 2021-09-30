
#ifndef COMUN_H
#define COMUN_H

#ifndef QG_H
#define QG_H

#include <QGraphicsItem>
#include <QGraphicsItemGroup>


class Comun : public QGraphicsItemGroup
{
public:
    Comun(QGraphicsItem* parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect ()const;
    QGraphicsItemGroup addToGroup(QGraphicsItem *item);
};

#endif // COMUN_H

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect () const;
    QGraphicsItemGroup addToGroup(QGraphicsItem *item);
};





#endif // QG_H

