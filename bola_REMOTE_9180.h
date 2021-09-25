#ifndef BOLA_H
#define BOLA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <list>

class Bola : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bola(QGraphicsItem *parent = nullptr);
    int anchoBola = 0;
    int largoBola = 0;
    int vX;
    int vY;
    int gC = 1;
    int gD = 1;
    int gT = 1;
    bool lanzada = false;
    void setLanzamiento(bool value);
    //void move();



private slots:
    void movimiento();

private:
    //modi
    int velocidadX = -3;
    int velocidadY = -3;
    bool golpe = false;

signals:
    void bolaPerdida();

};

#endif // BOLA_H
