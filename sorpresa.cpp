#include "sorpresa.h"
#include "dobles.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>
#include "raqueta.h"
#include "juego.h"
#include "bola.h"
extern Juego* juego;
using namespace std ;
Sorpresa::Sorpresa(int Ksorpresa, QGraphicsItem* parent): QGraphicsItemGroup(parent)
{


    _Ksorpresa = Ksorpresa;

}

QRectF Sorpresa:: boundingRect() const{
    return QRectF (0,0,95,55);
}

void Sorpresa:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: green);
    painter -> drawRoundedRect(0,0, 95, 55, 10, 10);


}

void Sorpresa::KSorpresa(){
    cout <<"HOLA EN SORPRESA";
    if( _Ksorpresa ==1){
        cout <<" AURAQUETA";
        juego->raqueta->aumentarRaqueta();
    }
    if( _Ksorpresa ==2){
        cout <<" RERAQUETA";
        juego->raqueta->reducirRaqueta();

    }
    if( _Ksorpresa ==3){
        cout<< "REBOLA";
        juego->bola->reducirBola();
    }
    if( _Ksorpresa ==4){
        cout <<"AUBOLA";
        juego->bola->aumentarBola();
    }

}

void Sorpresa::colision(){
    QList<QGraphicsItem *> colliding_items = collidingItems();
    double bolax = pos().x();
    double bolay = pos().y();
    int velocidadX = juego->bola->velocidadX;
    int velocidadY = juego->bola->velocidadY;

    for (size_t i = 0, n = colliding_items.size(); i < n; ++i)
    {
        Sorpresa* sorpresita = dynamic_cast<Sorpresa*>(colliding_items[i]);
        if (sorpresita)
        {
            //Posiciones de la bola y de los bloques

            double bloquex = sorpresita->pos().x();
            double bloquey = sorpresita->pos().y();



            if(juego->scene->items().size()==2)
            {
                juego->bola->velocidadX = 0;
                juego->bola->velocidadY = 0;


            }
            if (bolay> bloquey-10 && velocidadY < 0 )
             {
                juego->bola->playSound();
                juego->setPuntos();
                sorpresita->KSorpresa();
                velocidadY = -velocidadY;
                juego->bola->golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(sorpresita);

                continue;

            }
            if (bloquey > bolay+15 && velocidadY > 0 )
            {
                juego->bola->playSound();
                juego->setPuntos();
                sorpresita->KSorpresa();
                velocidadY = -velocidadY;
                juego->bola->golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(sorpresita);

                continue;
            }
            if (bolax> bloquex+150 && velocidadX < 0 )
            {
                juego->bola->playSound();
                juego->setPuntos();
                sorpresita->KSorpresa();
                velocidadX = -velocidadX;
                juego->bola->golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(sorpresita);

                continue;
            }
            if (bloquex > bolax+2 && velocidadX > 0 )
            {
                juego->bola->playSound();
                juego->setPuntos();
                sorpresita->KSorpresa();
                velocidadX = -velocidadX;
                juego->bola->golpe = false;
                juego->puntos+=30;
                juego->scene->removeItem(sorpresita);

                continue;
            }


        }
    }
    setPos(x()+velocidadX, y()+velocidadY);
}
