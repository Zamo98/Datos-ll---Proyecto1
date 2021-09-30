#ifndef TRIPLES_H
#define TRIPLES_H



#include <QGraphicsItem>
#include <QGraphicsItemGroup>


class Triples : public QGraphicsItemGroup
{
public:
    Triples(int _Vidas, QGraphicsItem* parent = nullptr);
    bool Vidas();
    int Vida;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect ()const;
};

#endif // TRIPLES_H
