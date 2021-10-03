#include "bola.h"
#include "ventana.h"
#include "raqueta.h"
#include "bloques.h"
#include "juego.h"
#include "comun.h"
#include "sorpresa.h"
#include "dobles.h"
#include "iostream"
#include <QGraphicsScene>

extern Juego* juego;
extern Sorpresa* sorpresa;
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
    QMediaPlaylist *rebote = new QMediaPlaylist();
    rebote->addMedia(QUrl("qrc:/sonidos/resources_sounds_bounce.wav"));
    golpeBloques = new QMediaPlayer();
    golpeBloques->setPlaylist(rebote);
}

void Bola::seguirRaqueta(){
    setPos(juego->raqueta->x() + (juego->raqueta->ancho - anchoBola)/2, juego->raqueta->y() - largoBola);
}

void Bola::bolaNueva(){
    setPixmap(QPixmap(":/imagenes/bola2 (1)"));
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
    else if(juego->bola2->y() > largoVentana-50){
        qDebug() <<"Bola perdida";
        juego->scene->removeItem(juego->bola2);
    }
    else if(juego->bola3->y() > largoVentana-50){
        qDebug() <<"Bola perdida";
        juego->scene->removeItem(juego->bola3);
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



    // // // // // // // // // // // // //



    for (size_t i = 0, n = colliding_items.size(); i < n; ++i)
    {
        //qDebug() <<"Aqui1";
        Sorpresa* sorpresita = dynamic_cast<Sorpresa*>(colliding_items[i]);
        if (sorpresita)

        {
            bolax = pos().x();
            bolay = pos().y();
            bloquex = sorpresita->pos().x();
            bloquey = sorpresita->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;
            }

            if ((bolay> bloquey-10 && velocidadY < 0) || (bloquey > bolay+15 && velocidadY > 0))
             {
                playSound();
                sorpresita->KSorpresa();
                //juego->setPuntos();
                //juego->puntos+=10;
                velocidadY = -velocidadY;
                golpe = false;
                juego->scene->removeItem(sorpresita);
                continue;
            }
            if ((bolax> bloquex+150 && velocidadX < 0) || (bloquex > bolax+2 && velocidadX > 0 ))
            {
                playSound();
                sorpresita->KSorpresa();
                //juego->setPuntos();
                //juego->puntos+=10;
                velocidadX = -velocidadX;
                golpe = false;
                juego->scene->removeItem(sorpresita);
                continue;
            }
        }
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

            if ((bolay> bloquey-10 && velocidadY < 0) || (bloquey > bolay+15 && velocidadY > 0))
             {
                playSound();
                juego->setPuntos();
                juego->puntos+=10;
                velocidadY = -velocidadY;
                golpe = false;
                juego->scene->removeItem(comun);
                continue;
            }
            if ((bolax> bloquex+150 && velocidadX < 0) || (bloquex > bolax+2 && velocidadX > 0 ))
            {
                playSound();
                juego->setPuntos();
                juego->puntos+=10;
                velocidadX = -velocidadX;
                golpe = false;
                juego->scene->removeItem(comun);
                continue;
            }
        }
        Dobles* doble = dynamic_cast<Dobles*>(colliding_items[i]);
        if(doble)
        {
            bolax = pos().x();
            bolay = pos().y();
            bloquex = doble->pos().x();
            bloquey = doble->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;
            }

            if((doble->Vidas()) == true){
                if ((bolay> bloquey-10 && velocidadY < 0) || (bloquey > bolay+15 && velocidadY > 0))
                {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->puntos+=15;
                    juego->scene->removeItem(doble);
                    continue;
                }
                if ((bolax> bloquex+150 && velocidadX < 0) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->puntos+=15;
                    juego->scene->removeItem(doble);
                    continue;
                }
            }
            else {
                if ((bolay> bloquey-10 && velocidadY < 0) || (bloquey > bolay+15 && velocidadY > 0))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    continue;
                }
                if ((bolax> bloquex+150 && velocidadX < 0) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;                    
                    continue;
                }
            }
        }
        Triples *triple = dynamic_cast<Triples*>(colliding_items[i]);
        if(triple){
            bolax = pos().x();
            bolay = pos().y();
            bloquex = triple->pos().x();
            bloquey = triple->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;
            }
            if((triple->Vidas()) == true){
                if ((bolay> bloquey-10 && velocidadY < 0) || (bloquey > bolay+15 && velocidadY > 0 ))
                {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->puntos+=20;
                    juego->scene->removeItem(triple);                    
                    continue;
                }
                if ((bolax> bloquex+150 && velocidadX < 0) || (bloquex > bolax+2 && velocidadX > 0))
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->puntos+=20;
                    juego->scene->removeItem(triple);                   
                    continue;
                }
            }
            else {
                if ((bolay> bloquey-10 && velocidadY < 0) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    continue;
                }
                if ((bolax> bloquex+150 && velocidadX < 0) || (bloquex > bolax+2 && velocidadX > 0) )
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    continue;
                }
            }
        }
    }
    setPos(x()+velocidadX, y()+velocidadY);
}

void Bola::reducirBola(){
    velocidadX -= 1;
    velocidadY -= 1;
}
void Bola:: aumentarBola(){
    velocidadX += 1;
    velocidadY += 1;

}



















