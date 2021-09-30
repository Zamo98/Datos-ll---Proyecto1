#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QDebug>
#include "raqueta.h"
#include "ventana.h"
#include "bola.h"
#include "bloques.h"
#include "comun.h"
#include "dobles.h"
#include <QFont>
#include "sorpresa.h"
#include <list>
#include <QGraphicsItem>


class Juego : public QGraphicsView
{
    Q_OBJECT
public:
    Juego(QGraphicsView *parent=nullptr);
    QGraphicsScene *scene=nullptr;
    bool gameOver;
    bool gameWin;
    bool CB;
    Raqueta *raqueta=nullptr;
    Comun *bloquesito;
    Dobles *bloquesito1;
    Sorpresa *sorpresita;
    Bola *bola;

    //void Cc (QGraphicsItem* Bloquesito);
    void Iniciar();
    void CrearBloque(double y);
    void juegoTerminado();
    int puntos = 0;
    void setPuntos();


protected:
    void keyPressEvent(QKeyEvent* evento);
    void mousePressEvent(QMouseEvent* evento);
    void mouseMoveEvent(QMouseEvent* evento);

private:
    void mostrarPuntaje();
    int vidas = 5;
    QFont fuente;
    QGraphicsTextItem *texto=nullptr;
    QMediaPlayer *pierdes=nullptr;
    QMediaPlayer *reproducir=nullptr;

private slots:
    void jugadorPierde();
};

#endif // JUEGO_H
