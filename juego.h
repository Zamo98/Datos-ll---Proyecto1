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

protected:
    void keyPressEvent(QKeyEvent* evento);
    void mousePressEvent(QMouseEvent* evento);
    void mouseMoveEvent(QMouseEvent* evento);

private:
    void juegoTerminado();
    QGraphicsScene *scene=nullptr;
    int puntos = 0;
    int vidas = 1;
    QGraphicsTextItem *texto=nullptr;

private slots:
    void jugadorPierde();
};

#endif // JUEGO_H
