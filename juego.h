#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include "raqueta.h"
#include "ventana.h"

class Juego : public QGraphicsView
{
    Q_OBJECT
public:
    Juego(QGraphicsView *parent=nullptr);
    Raqueta *raqueta=nullptr;

protected:
    void keyPressEvent(QKeyEvent* evento);
  //  void mousePressEvent(QMouseEvent* evento);
    void mouseMoveEvent(QMouseEvent* evento);

private:
    void juegoTerminado();
    QGraphicsScene *scene=nullptr;
};

#endif // JUEGO_H
