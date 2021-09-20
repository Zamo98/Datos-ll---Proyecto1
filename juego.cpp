#include "juego.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QIcon>


Juego::Juego(QGraphicsView *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,anchoVentana, largoVentana);
    scene->setBackgroundBrush(QBrush(QImage(":/imagenes/fondo")));

    window()->setWindowIcon(QIcon(":/imagenes/icono"));
    window()->setWindowTitle(nombreJuego);
    setFixedSize(anchoVentana, largoVentana);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    raqueta = new Raqueta();
    raqueta->setPos((anchoVentana - raqueta->ancho)/2, largoVentana-100);
    scene->addItem(raqueta);

    show();
}

void Juego::keyPressEvent(QKeyEvent *evento){
    switch (evento->key()) {

    case Qt::Key_Left:
        if(raqueta){
            raqueta->movIzq();
        }
        break;

    case Qt::Key_Right:
        if(raqueta){
            raqueta->movDer();
        }
        break;
    }
}

//void Juego::mousePressEvent(QMouseEvent *evento){
  //  switch(evento->button()){

    //case Qt::LeftButton:
      //  if(raqueta){

        //}
    //}
//}

void Juego::mouseMoveEvent(QMouseEvent *evento){
    if(raqueta){
        raqueta->mover(evento->pos());

    }
}

void Juego::juegoTerminado(){

}
