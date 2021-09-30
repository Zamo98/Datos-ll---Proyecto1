#ifndef DOBLES_H
#define DOBLES_H
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

class Dobles : public QGraphicsItemGroup
{
public:
    Dobles(int _Vida, QGraphicsItem* parent = nullptr);
    int Vida;
    bool Vidas();

protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect () const;
};

#endif // DOBLES_H
