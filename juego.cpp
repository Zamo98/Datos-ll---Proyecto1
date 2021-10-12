/**
  * @file juego.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora.
  */

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
/**
 * @brief Juego::Juego Clase del juego, aqui se definen todos los objetos y se dibujan en pantalla.
 * @param parent Parametro por defecto.
 */

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

    //Diseño y posiscion inicial de la raqueta

    raqueta = new Raqueta();
    raqueta->setPos((anchoVentana - raqueta->ancho)/2, largoVentana-100);
    scene->addItem(raqueta);

    bola = new Bola();
    bola2 = new Bola();
    bola3 = new Bola();
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
/**
 * @brief Juego::activarCronometro Este metodo activa el cronometro para que aparezcan más bolas despues de un tiempo.
 */

void Juego::activarCronometro(){ //Metodo que activa el cronometro
    contador++;
    if(contador == 15){
        scene->addItem(bola2);
        bola2->setLanzamiento(true);
    }
    else if(contador == 30){
        scene->addItem(bola3);
        bola3->setLanzamiento(true);
        //contador=0;
    }
    else if(contador == 45){
        bola->velocidadX++;
        bola->velocidadY++;
        bola2->velocidadX++;
        bola2->velocidadY++;
        bola3->velocidadX++;
        bola3->velocidadY++;

        contador=0;

    }

}
/**
 * @brief Juego::CrearBloque Este metodo crea los diferentes tipos de bloques.
 * @param y
 */

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
                    sorpresa = new Sorpresa(n2);
                    sorpresa->setPos(i*103, y);
                    scene->addItem(sorpresa);
                }
                else {
                    interno = new Internos();
                    interno->setPos(i*103,y);
                    scene->addItem(interno);
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
                    triple = new Triples(3);
                    triple->setPos(i*103,y);
                    scene->addItem(triple);

                }
            }
            if (k ==2){
                int n4 = 1 + rand()%(7);
                if (n4 >= 5){
                    sorpresa = new Sorpresa(n2);
                    sorpresa->setPos(i*103, y);
                    scene->addItem(sorpresa);
                }
                else {
                    doble = new Dobles(2);
                    doble->setPos(i*103,y);
                    scene->addItem(doble);

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

                    comun = new Comun();
                    comun->setPos(i*103,y);
                    scene->addItem(comun);

                }
            }
        }
        y += 57; //Distancia entre y
    }
    //size_t i = 0, n = colliding_items.size(); i < n; ++i
}

/**
 * @brief Juego::Iniciar Este metodo inicializa los bloques
 */


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

                        Sorpresa* sorpresa = dynamic_cast<Sorpresa*>(allItems[i]);
                        if (sorpresa){
                            scene->removeItem(sorpresa);
                        }
                        Internos* interno = dynamic_cast<Internos*>(allItems[i]);
                        if (interno){
                            scene->removeItem(interno);
                        }
                        Profundos* profundo = dynamic_cast<Profundos*>(allItems[i]);
                        if (profundo){
                            scene->removeItem(profundo);
                        }
                    }
        gameOver = false;
        gameWin = false;
        }
    }

    CrearBloque(0);
}

/**
 * @brief Juego::keyPressEvent Este metodo se utiliza para disparar la bola.
 * @param evento
 */
void Juego::keyPressEvent(QKeyEvent *evento){
    switch (evento->key()) {
    case Qt::Key_Space:
        if(raqueta){
            raqueta->disparo();
            bola->setLanzamiento(true);
        }
        break;
    }
}

//Mover la raqueta con el mouse
/**
 * @brief Juego::mouseMoveEvent Este metodo se utiliza para mover la raqueta con el mouse
 * @param evento
 */
void Juego::mouseMoveEvent(QMouseEvent *evento){
    if(raqueta){
        raqueta->mover(evento->pos());
    }
}
/**
 * @brief Juego::jugadorPierde Este metodo se utiliza para inicializar las acciones de cuando el jugador pierde
 */

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
/**
 * @brief Juego::jugadorGana Este metodo inicializaa las acciones del juego cuando el jugador gane. 
 */

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
/**
 * @brief Juego::mostrarPuntaje Metodo que sirve para mostrar el puntaje del jugador en la pantalla.
 */

void Juego::mostrarPuntaje(){
    if(scene->items().contains(texto)) scene->removeItem(texto);    
    texto->setPlainText("Puntos: " + QString::number(puntos));
    texto->setPos((anchoVentana - 1000), largoVentana-70);
    scene->addItem(texto);
}
/**
 * @brief Juego::setPuntos Metodo que sirve para actualizar el puntaje del jugador.
 */

void Juego::setPuntos(){
    mostrarPuntaje();
}

/**
 * @brief Juego::juegoTerminado Este metodo inicializa las acciones que debe tomar el juego, cuando el usuario pierde.
 */


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
