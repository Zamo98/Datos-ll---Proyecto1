#ifndef BOLA_H
#define BOLA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

class Bola : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bola(QGraphicsItem *parent = nullptr);
    int anchoBola = 0;
    int largoBola = 0;
    bool lanzada = false;
    void setLanzamiento(bool value);

private slots:
    void movimiento();

private:
    int velocidadX = -3;
    int velocidadY = -3;
    bool golpe = false;

signals:
    void bolaPerdida();
};

#endif // BOLA_H
