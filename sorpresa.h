#ifndef SORPRESA_H
#define SORPRESA_H
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

class Sorpresa: public QGraphicsItemGroup
{
public:
    Sorpresa(int Ksorpresa, QGraphicsItem* parent = nullptr);
    int _Ksorpresa;
    void KSorpresa();
   // void colision ();

protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect () const;
};

#endif // SORPRESA_H
