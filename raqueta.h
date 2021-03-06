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
    int nuevoAncho=90;
    void movDer();
    void movIzq();
    void mover(QPoint p);
    void disparo();
    void reducirRaqueta();
    void aumentarRaqueta();

private:
    int velocidad=15;
};

#endif // RAQUETA_H
