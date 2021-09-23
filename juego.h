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
#include <QFont>


class Juego : public QGraphicsView
{
    Q_OBJECT
public:
    Juego(QGraphicsView *parent=nullptr);
    QGraphicsScene *scene=nullptr;
    bool gameOver;
    bool gameWin;
    Raqueta *raqueta=nullptr;
    Bola *bola;
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
