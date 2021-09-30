#include "juego.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QIcon>
#include "bloques.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <stdio.h>

using namespace std;



Juego::Juego(QGraphicsView *parent) : QGraphicsView(parent)
{
    //Diseño de la ventana

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,anchoVentana, largoVentana);
    scene->setBackgroundBrush(QBrush(QImage(":/imagenes/fondo")));
    window()->setWindowIcon(QIcon(":/imagenes/icono2"));
    window()->setWindowTitle(nombreJuego);
    setFixedSize(anchoVentana, largoVentana);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);


    gameOver = false;
    gameWin = false;

    //Diseño y posiscion inicial de la raqueta

    raqueta = new Raqueta();
    raqueta->setPos((anchoVentana - raqueta->ancho)/2, largoVentana-100);
    scene->addItem(raqueta);

    bola = new Bola();
    bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);
    connect(bola, SIGNAL(bolaPerdida()), this, SLOT(jugadorPierde()));
    scene->addItem(bola);

    int identificador = QFontDatabase::addApplicationFont(":/fuente/letras.ttf");
    if(identificador>=0){
        qDebug()<<"Fuente cargada";
        QString family = QFontDatabase::applicationFontFamilies(identificador).at(0);
        fuente = QFont(family, 24);
    }
    else{
        qDebug()<<"Error al cargar la fuente";
    }

    texto = new QGraphicsTextItem();
    texto->setDefaultTextColor(Qt::white);
    texto->setFont(fuente);
    mostrarPuntaje();

    //Reproduce musica de fondo
    QMediaPlaylist *musica = new QMediaPlaylist();
    musica->addMedia(QUrl("qrc:/sonidos/tono_arkanoid_amstrad_cpc_1987.mp3"));
    musica->setPlaybackMode(QMediaPlaylist::Loop);
    reproducir = new QMediaPlayer();
    reproducir->setPlaylist(musica);
    reproducir->setVolume(10);
    reproducir->play();

    //Reproduce sonido game over
    QMediaPlaylist *sonido = new QMediaPlaylist();
    sonido->addMedia(QUrl("qrc:/sonidos/game_over.mp3"));
    pierdes = new QMediaPlayer();
    pierdes->setPlaylist(sonido);

    show();
}

void Juego::CrearBloque(double y) //Dibujas los bloques
{
    QList<QGraphicsItem *> colliding_items;
    int num;
    srand(time(NULL));

    for (size_t k = 0, j = 4; k < j; ++k) //Creacion de columnas
    {
        for (size_t i = 0, n = 10; i < n; ++i) //Creacion de filas
        {
            num =1 + rand() % (3);

            if (num ==1){
                comun = new Comun();
                comun->setPos(i*103,y);
                scene->addItem(comun);
            }
            if (num ==2){
                doble = new Dobles(2);
                doble->setPos(i*103,y);
                scene->addItem(doble);
            }
            if (num ==3){
                triple = new Triples(3);
                triple->setPos(i*103,y);
                scene->addItem(triple);
            }
        }
        y += 57; //Distancia entre y
    }
}

void Juego::Iniciar() { //Inicializar los bloques

    if (gameOver == true){

        if (gameWin == true){
            QList<QGraphicsItem*> allItems = scene->items();
                    for (size_t i = 0,q = scene->items().size() ; i < q ; ++i){
                        Comun* bloquesito = dynamic_cast<Comun*>(allItems[i]);
                        if (bloquesito){
                            scene->removeItem(bloquesito);
                        }
                        Dobles* doble = dynamic_cast<Dobles*>(allItems[i]);
                        if(doble){
                            scene->removeItem(doble);
                        }
                        Triples* triple = dynamic_cast<Triples*>(allItems[i]);
                        if(triple){
                            scene->removeItem(triple);
                        }
                    }
        gameOver = false;
        gameWin = false;
        }

    }

    CrearBloque(0);


}

//Mover la raqueta con las teclas
void Juego::keyPressEvent(QKeyEvent *evento){
    switch (evento->key()) {

    /*case Qt::Key_Left:
        if(raqueta){
            raqueta->movIzq();
            if(!bola->lanzada) bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);
        }
        break;

    case Qt::Key_Right:
        if(raqueta){
            raqueta->movDer();
            if(!bola->lanzada) bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);

        }
        break;*/

    case Qt::Key_Space:
        if(raqueta){
            raqueta->disparo();
            bola->setLanzamiento(true);
        }
        break;
    }
}

void Juego::mousePressEvent(QMouseEvent *evento){
    switch(evento->button()){

    case Qt::LeftButton:
        if(raqueta){
            raqueta->disparo();
            bola->setLanzamiento(true);
        }
        break;

    case Qt::RightButton:
        break;

    default:
        break;
    }
}


//Mover la raqueta con el mouse
void Juego::mouseMoveEvent(QMouseEvent *evento){
    if(raqueta){
        raqueta->mover(evento->pos());


    }
}

void Juego::jugadorPierde(){
    if(bola){
        if(raqueta->nuevoAncho != 50){
        raqueta->reducirRaqueta();
        bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);
        }
        else{
            juegoTerminado();
        }
    }
}

void Juego::mostrarPuntaje(){
    if(scene->items().contains(texto)) scene->removeItem(texto);
    texto->setPlainText("Puntos: " + QString::number(puntos));

    texto->setPos((anchoVentana - 1000), largoVentana-70);

    //texto->setPos((anchoVentana - (0.68 * texto->font().pointSize()*texto->toPlainText().length()))/2, largoVentana-70);
    scene->addItem(texto);
}

void Juego::setPuntos(){
    mostrarPuntaje();
}

void Juego::juegoTerminado(){
    scene->removeItem(bola);
    scene->removeItem(raqueta);
    QGraphicsTextItem *texto = new QGraphicsTextItem;
    texto -> setDefaultTextColor(Qt::white);
    texto->setFont(fuente);
    qDebug() << texto->font().pointSize();
    QString mensaje = "Has perdido!";
    texto->setPlainText(mensaje);
    texto->setPos(400,largoVentana/2);
    scene->addItem(texto);

    pierdes->play();
    reproducir->pause();

    gameOver = true;
    if(scene->items().size()==2){
        gameWin = true;

    }
}
