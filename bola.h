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
#include <list>
#include "comun.h"

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
    Comun *bloquesito;
    bool lanzada = false;
    void setLanzamiento(bool value);
    void seguirRaqueta();


private slots:
    void movimiento();

private:
    //modi
    int velocidadX = 2;
    int velocidadY = 2;
    bool golpe = false;
    QMediaPlayer *golpeBloques = nullptr;
    void playSound();

signals:
    void bolaPerdida();

};

#endif // BOLA_H
