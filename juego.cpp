#include "juego.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QIcon>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <stdio.h>

#include "comun.h"
#include "dobles.h"
#include "sorpresa.h"
#include <QGraphicsScene>
#include "ventana.h"
#include <QGraphicsItem>
#include <QList>
#include "profundos.h"
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

    QTimer *cronometro = new QTimer();
    connect(cronometro, SIGNAL(timeout()),this,SLOT(activarCronometro()));
    cronometro->start(500);


    gameOver = false;
    gameWin = false;
    CB = true;

    //Diseño y posiscion inicial de la raqueta

    raqueta = new Raqueta();
    raqueta->setPos((anchoVentana - raqueta->ancho)/2, largoVentana-100);
    scene->addItem(raqueta);

    bola = new Bola();
    bola2 = new Bola();
    bola3 = new Bola();
    //bola2->bolaNueva();
    //bola3->bolaNueva();
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
void Juego::activarCronometro(){
    contador++;
    if(contador == 15){
        scene->addItem(bola2);
        bola2->setLanzamiento(true);
    }
    else if(contador == 30){
        scene->addItem(bola3);
        bola3->setLanzamiento(true);
        contador=0;
    }

}

void Juego::CrearBloque(double y) //Dibujas los bloques
{
    QList<QGraphicsItem *> colliding_items;

    srand(time(NULL));

    int n1;
    int n2;
    int n3;
    int n5;


    for (size_t k = 0, j = 4; k < j; ++k) //Creacion de columnas
    {
        for (size_t i = 0, n = 10; i < n; ++i) //Creacion de filas
        {
            if (k == 0){
                n1 =1 + rand() % (8);
                if (n1 >=7){
                    n2 =1 + rand() % (4);
                    sorpresita = new Sorpresa(n2);
                    sorpresita->setPos(i*103, y);
                    scene->addItem(sorpresita);

                }
                else {
                    bloquesito1 = new Dobles(2);
                    bloquesito1->setPos(i*103,y);
                    scene->addItem(bloquesito1);


                }
            }

            if (k == 1){
                n3 =1 + rand() % (5);
                if (n3 == 2){
                    profundo = new Profundos();
                    profundo->setPos(i*103, y);
                    scene->addItem(profundo);
                }
                else {
                    bloquesito = new Comun();
                    bloquesito->setPos(i*103,y);
                    scene->addItem(bloquesito);

                }
            }
            if (k ==2){
                int n4 = 1 + rand()%(7);
                if (n4 >= 5){
                    sorpresita = new Sorpresa(n2);
                    sorpresita->setPos(i*103, y);
                    scene->addItem(sorpresita);
                }
                else {
                    bloquesito1 = new Dobles(2);
                    bloquesito1->setPos(i*103,y);
                    scene->addItem(bloquesito1);

                }
            }
            if (k == 3){
                n5 =1 + rand() % (8);
                if (n5 >= 7){
                    profundo = new Profundos();
                    profundo->setPos(i*103, y);
                    scene->addItem(profundo);
                }
                else {

                    bloquesito = new Comun();
                    bloquesito->setPos(i*103,y);
                    scene->addItem(bloquesito);

                }
            }
        }
        y += 57; //Distancia entre y
    }
    //size_t i = 0, n = colliding_items.size(); i < n; ++i
}




void Juego::Iniciar() { //Inicializar los bloques

    if (gameOver == true){

        if (gameWin == true){
            QList<QGraphicsItem*> allItems = scene->items();
                    for (size_t i = 0,q = scene->items().size() ; i < q ; ++i){
                        Comun* comun = dynamic_cast<Comun*>(allItems[i]);
                        if (comun){
                            scene->removeItem(comun);
                        }
                        Dobles* doble = dynamic_cast<Dobles*>(allItems[i]);
                        if(doble){
                            scene->removeItem(doble);
                        }
                        Triples* triple = dynamic_cast<Triples*>(allItems[i]);
                        if(triple){
                            scene->removeItem(triple);
                        }

                        Sorpresa* sorpresita = dynamic_cast<Sorpresa*>(allItems[i]);
                        if (sorpresita){
                            scene->removeItem(sorpresita);
                        }
                        Profundos* profundo = dynamic_cast<Profundos*>(allItems[i]);
                        if (sorpresita){
                            scene->removeItem(profundo);
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
    case Qt::Key_Left:
        if(raqueta){
            for (size_t i = 0, n = scene->items().size(); i < n; ++i)

            {

            }

            raqueta->movIzq();
            if(!bola->lanzada) bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);
        }
        break;

    case Qt::Key_Right:
        if(raqueta){
            raqueta->movDer();
            if(!bola->lanzada) bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);

        }
        break;
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
    else if(bola2){
        if(raqueta->nuevoAncho != 50){
            raqueta->reducirRaqueta();
        }
        else{
            juegoTerminado();
        }
    }
    else if(bola3){
        if(raqueta->nuevoAncho != 50){
            raqueta->reducirRaqueta();
        }
        else{
            juegoTerminado();
        }
    }
}

void Juego::jugadorGana(){
    scene->removeItem(bola);
    scene->removeItem(raqueta);
    QGraphicsTextItem *textoGanador = new QGraphicsTextItem;
    textoGanador -> setDefaultTextColor(Qt::white);
    textoGanador->setFont(fuente);
    qDebug() << textoGanador->font().pointSize();
    QString mensaje = "Ganaste!";
    textoGanador->setPlainText(mensaje);
    textoGanador->setPos(400,largoVentana/2);
    scene->addItem(textoGanador);
}

void Juego::mostrarPuntaje(){
    if(scene->items().contains(texto)) scene->removeItem(texto);    
    texto->setPlainText("Puntos: " + QString::number(puntos));
    texto->setPos((anchoVentana - 1000), largoVentana-70);
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
