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
    bool golpe = false;
    int vX;
    int vY;
    int velocidadX = 3;
    int velocidadY = 3;
    //Comun *bloquesito;
    bool lanzada = false;
    void setLanzamiento(bool value);
    void seguirRaqueta();
    void reducirBola();
    void aumentarBola();
    void playSound();


private slots:
    void movimiento();

private:
    //modi


    QMediaPlayer *golpeBloques = nullptr;


signals:
    void bolaPerdida();

};

#endif // BOLA_H
