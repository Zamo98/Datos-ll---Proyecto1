#include "bola.h"
#include "ventana.h"
#include "raqueta.h"
#include "bloques.h"
#include "juego.h"
#include "iostream"
extern Juego* juego;
using namespace std;

Bola::Bola(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/imagenes/bola"));
    anchoBola = pixmap().width();
    largoBola = pixmap().height();
    lanzada = false;
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(movimiento()));
    timer->start(10);


}

void Bola::seguirRaqueta(){
    setPos(juego->raqueta->x() + (juego->raqueta->ancho - anchoBola)/2, juego->raqueta->y() - largoBola);
}

void Bola::setLanzamiento(bool value){
    lanzada = value;
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
        golpe = false;
        cout <<anchoBola;
        cout <<largoBola;
    }
    if(vY < 0 || vY+largoBola > largoVentana){
        velocidadY = -velocidadY;
        golpe = false;
    }


    //Colision con los bloques

    for (size_t i = 0, n = colliding_items.size(); i < n; ++i)
    {
        qDebug() <<"Aqui1";
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

            if (bolay> bloquey+22 && velocidadY < 0 )
             {
                juego->setPuntos();
                velocidadY = -velocidadY;
                golpe = false;
                juego->scene->removeItem(bloques);
                continue;
              }
            if (bloquey > bolay+15 && velocidadY > 0 )
            {
                juego->setPuntos();
                velocidadY = -velocidadY;
                golpe = false;
                juego->scene->removeItem(bloques);
                continue;
            }
            if (bolax> bloquex+50 && velocidadX < 0 )
            {
                juego->setPuntos();
                velocidadX = -velocidadX;
                golpe = false;
                juego->scene->removeItem(bloques);
                continue;
            }
            if (bloquex > bolax+2 && velocidadX > 0 )
            {
                juego->setPuntos();
                velocidadX = -velocidadX;
                golpe = false;
                juego->scene->removeItem(bloques);
                continue;
            }
        }

    }

    setPos(x()+velocidadX, y()+velocidadY);
}




