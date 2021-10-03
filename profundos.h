#ifndef PROFUNDOS_H
#define PROFUNDOS_H
#include <QGraphicsItem>
#include <QGraphicsItemGroup>


class Profundos: public QGraphicsItemGroup
{
public:
    Profundos( QGraphicsItem* parent = nullptr);
    bool Eprofundo = false;
    int cant_profundidad ();
    void Masprofundidad (int x);
    void Menosprofundidad(int x);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect () const;
    int profundida = 0;


};



#endif // PROFUNDOS_H
