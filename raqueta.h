#ifndef RAQUETA_H
#define RAQUETA_H

#include <QGraphicsPathItem>
#include <QObject>


class Raqueta : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Raqueta(QGraphicsItem *parent=nullptr);
    int ancho=0;
    int largo=0;
    void movDer();
    void movIzq();
    void mover(QPoint p);

private:
    int velocidad=10;
};

#endif // RAQUETA_H
