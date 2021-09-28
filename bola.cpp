#include "bola.h"
#include "ventana.h"
#include "raqueta.h"
#include "bloques.h"
#include "juego.h"
#include "comun.h"
#include "dobles.h"
#include "iostream"
extern Juego* juego;
#include "comun.h"
using namespace std;
#include <QGraphicsScene>



Bola::Bola(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/imagenes/bola"));
    anchoBola = pixmap().width();
    largoBola = pixmap().height();
    lanzada = false;
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(movimiento()));
    timer->start(10);
    QMediaPlaylist *rebote = new QMediaPlaylist();
    rebote->addMedia(QUrl("qrc:/sonidos/resources_sounds_bounce.wav"));
    golpeBloques = new QMediaPlayer();
    golpeBloques->setPlaylist(rebote);
}

void Bola::seguirRaqueta(){
    setPos(juego->raqueta->x() + (juego->raqueta->ancho - anchoBola)/2, juego->raqueta->y() - largoBola);
}


void Bola::setLanzamiento(bool value){
    lanzada = value;
}

void Bola::playSound(){
    if(golpeBloques->state() == QMediaPlayer::PlayingState) golpeBloques->setPosition(0);
    else if(golpeBloques->state() == QMediaPlayer::StoppedState) golpeBloques->play();
}

void Bola::movimiento(){

    QList<QGraphicsItem *> colliding_items = collidingItems();

    double bolax;
    double bolay;
    double bloquex;
    double bloquey;


    if(y() > largoVentana-50){
        qDebug() <<"Bola perdida";
        lanzada = false;
        emit(bolaPerdida());
    }

    if(lanzada){
        for(auto i : colliding_items){
            if(typeid(*i) == typeid (Raqueta) && !golpe){
                playSound();

                velocidadY = -velocidadY;
                setPos(x()+velocidadX, y()+velocidadY);
                golpe = true;
                return;
            }
        }
    }
    else if(!lanzada){
        seguirRaqueta();
    }

    vX = x()+velocidadX;
    vY = y()+velocidadY;
    if(vX < 0 || vX+anchoBola > anchoVentana){
        velocidadX = -velocidadX;
        //playSound();
        golpe = false;
        cout <<anchoBola;
        cout <<largoBola;
    }
    if(vY < 0 || vY+largoBola > largoVentana){
        velocidadY = -velocidadY;
        //playSound();
        golpe = false;
    }


    //Colision con los bloques

    for (size_t i = 0, n = colliding_items.size(); i < n; ++i)
    {
        //qDebug() <<"Aqui1";
        Bloques* bloques = dynamic_cast<Bloques*>(colliding_items[i]);
        if (bloques)
        {
            //Posiciones de la bola y de los bloques
            bolax = pos().x();
            bolay = pos().y();
            bloquex = bloques->pos().x();
            bloquey = bloques->pos().y();
            cout <<bolax;
            cout <<bolay;


            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;

            }


            if ((bloques ->Comun(bloquex, bloquey)== true))
            { //SEGUN YO UN CONDICIONAL PARA VER SI ES BLOQUE COMUN

                if (bolay> bloquey && velocidadY < 0 )
                 {
                    playSound();
                    juego->setPuntos();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->scene->removeItem(bloques);
                    continue;
                }
                if (bloquey > bolay+15 && velocidadY > 0 )
                {
                    playSound();
                    juego->setPuntos();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->scene->removeItem(bloques);
                    continue;
                }
                if (bolax> bloquex && velocidadX < 0 )
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->scene->removeItem(bloques);
                    continue;
                }
                if (bloquex > bolax+2 && velocidadX > 0 )
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->scene->removeItem(bloques);
                    continue;
                }

            }



        }

    }

    setPos(x()+velocidadX, y()+velocidadY);




    // // // // // // // // // // // // //



    for (size_t i = 0, n = colliding_items.size(); i < n; ++i)
    {
        //qDebug() <<"Aqui1";
        Comun* comun = dynamic_cast<Comun*>(colliding_items[i]);

        if (comun)
        {
            //Posiciones de la bola y de los bloques
            bolax = pos().x();
            bolay = pos().y();
            bloquex = comun->pos().x();
            bloquey = comun->pos().y();



            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;

            }
            if (bolay> bloquey-10 && velocidadY < 0 )
             {
                playSound();
                juego->setPuntos();
                velocidadY = -velocidadY;
                golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(comun);
                continue;

            }
            if (bloquey > bolay+15 && velocidadY > 0 )
            {
                playSound();
                juego->setPuntos();
                velocidadY = -velocidadY;
                golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(comun);
                continue;
            }
            if (bolax> bloquex+150 && velocidadX < 0 )
            {
                playSound();
                juego->setPuntos();
                velocidadX = -velocidadX;
                golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(comun);
                continue;
            }
            if (bloquex > bolax+2 && velocidadX > 0 )
            {
                playSound();
                juego->setPuntos();
                velocidadX = -velocidadX;
                golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(comun);
                continue;
            }


        }

        Dobles* doble = dynamic_cast<Dobles*>(colliding_items[i]);
        if (doble)
        {
            //Posiciones de la bola y de los bloques
            bolax = pos().x();
            bolay = pos().y();
            bloquex = doble->pos().x();
            bloquey = doble->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;

            }
            if (bolay> bloquey-10 && velocidadY < 0 )
             {
                playSound();

                velocidadY = -velocidadY;
                golpe = false;
                juego->puntos+=100;
                juego->scene->removeItem(doble);
                continue;
                bloquesito = new Comun();
                bloquesito->setPos(pos().x(),pos().y());
                juego->Cc(bloquesito);

            }
            if (bloquey > bolay+15 && velocidadY > 0 )
            {
                playSound();
                juego->setPuntos();
                velocidadY = -velocidadY;
                golpe = false;
                juego->puntos+=100;
                juego->scene->removeItem(doble);
                continue;
                bloquesito = new Comun();
                bloquesito->setPos(pos().x(),pos().y());
                juego->Cc(bloquesito);
            }
            if (bolax> bloquex+150 && velocidadX < 0 )
            {
                playSound();
                juego->setPuntos();
                velocidadX = -velocidadX;
                golpe = false;
                juego->puntos+=100;
                juego->scene->removeItem(doble);
                continue;
                bloquesito = new Comun();
                bloquesito->setPos(pos().x(),pos().y());
                juego->Cc(bloquesito);
            }

            if (bloquex > bolax+2 && velocidadX > 0 )
            {
                playSound();
                juego->setPuntos();
                velocidadX = -velocidadX;
                golpe = false;
                juego->puntos+=100;
                juego->scene->removeItem(doble);
                continue;
                bloquesito = new Comun();
                bloquesito->setPos(pos().x(),pos().y());
                juego->Cc(bloquesito);
            }



            }

    }


    setPos(x()+velocidadX, y()+velocidadY);
}



















