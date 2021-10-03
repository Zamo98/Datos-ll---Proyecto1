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

#include "comun.h"
#include "dobles.h"
#include "triples.h"

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
    Sorpresa *sorpresita;
    Bola *bola, *bola2, *bola3, *bola4;
    Comun *comun;
    Dobles *doble;
    Triples *triple;
    void Iniciar();
    void CrearBloque(double y);
    void juegoTerminado();
    int puntos = 0;
    int contador = 0;

    void setPuntos();

public slots:
    void jugadorGana();


protected:
    void keyPressEvent(QKeyEvent* evento);
    void mousePressEvent(QMouseEvent* evento);
    void mouseMoveEvent(QMouseEvent* evento);

private:
    void mostrarPuntaje();
    QFont fuente;
    QGraphicsTextItem *texto=nullptr;
    QMediaPlayer *pierdes=nullptr;
    QMediaPlayer *reproducir=nullptr;

private slots:
    void jugadorPierde();
    void activarCronometro();
};

#endif // JUEGO_H
