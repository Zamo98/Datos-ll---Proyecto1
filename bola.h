#ifndef BOLA_H
#define BOLA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "raqueta.h"

class Bola : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bola(QGraphicsItem *parent = nullptr);
    int anchoBola = 0;
    int largoBola = 0;
    int vX;
    int vY;
    bool lanzada = false;
    void setLanzamiento(bool value);
    void seguirRaqueta();


private slots:
    void movimiento();

private:
    //modi
    int velocidadX = 3;
    int velocidadY = 3;
    bool golpe = false;
    QMediaPlayer *golpeBloques = nullptr;
    void playSound();

signals:
    void bolaPerdida();

};

#endif // BOLA_H
