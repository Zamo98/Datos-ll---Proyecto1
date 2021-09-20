#include "juego.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QIcon>
#include "bloques.h"


Juego::Juego(QGraphicsView *parent) : QGraphicsView(parent)
{

    //Dise;o de la ventana

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,anchoVentana, largoVentana);
    scene->setBackgroundBrush(QBrush(QImage(":/imagenes/fondo")));
    window()->setWindowIcon(QIcon(":/imagenes/icono"));
    window()->setWindowTitle(nombreJuego);
    setFixedSize(anchoVentana, largoVentana);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    //Dise;o y posiscion inicial de la raqueta

    raqueta = new Raqueta();
    raqueta->setPos((anchoVentana - raqueta->ancho)/2, largoVentana-100);
    scene->addItem(raqueta);

    show();
}

void Juego::CrearBloque(double y) //Dibujas los bloques
{
    for (size_t k = 0, j = 5; k < j; ++k) //Creacion de columnas
    {
        for (size_t i = 0, n = 10; i < n; ++i) //Creacion de filas
        {
            Bloques* bloques = new Bloques();
            bloques->setPos(i*107,y); //Posicion en x,y
            scene->addItem(bloques);
        }
        y += 40; //Distancia entre y
    }
}

void Juego::Iniciar() { //Inicializar los bloques
    CrearBloque(0);

}

//Mover la raqueta con las teclas
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


//Mover la raqueta con el mouse
void Juego::mouseMoveEvent(QMouseEvent *evento){
    if(raqueta){
        raqueta->mover(evento->pos());

    }
}

void Juego::juegoTerminado(){

}
