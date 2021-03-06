/**
  * @file bola.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora.
  */

#include "bola.h"
#include "ventana.h"
#include "raqueta.h"
#include "juego.h"
#include "comun.h"
#include "sorpresa.h"
#include "dobles.h"
#include "iostream"
#include "profundos.h"

#include <QGraphicsScene>

extern Juego* juego;
extern Sorpresa* sorpresa;
using namespace std;
extern Profundos* profundos;

/**
 * @brief Bola::Bola Constructor.
 * @param parent Parametro por defecto.
 */
Bola::Bola(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/imagenes/bola"));
    anchoBola = pixmap().width();
    largoBola = pixmap().height();
    lanzada = false;
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(movimientoYColisiones()));
    timer->start(10);
    QMediaPlaylist *rebote = new QMediaPlaylist();
    rebote->addMedia(QUrl("qrc:/sonidos/resources_sounds_bounce.wav"));
    golpeBloques = new QMediaPlayer();
    golpeBloques->setPlaylist(rebote);
}

/**
 * @brief Bola::seguirRaqueta Su funcion es que la bola permanezca sobre la raqueta mientras no haya sido lanzada.
 */
void Bola::seguirRaqueta(){
    setPos(juego->raqueta->x() + (juego->raqueta->ancho - anchoBola)/2, juego->raqueta->y() - largoBola);
}

/**
 * @brief Bola::setLanzamiento Define el estado de la bola.
 * @param value Bool que indica si la bola fue lanzada o no.
 */
void Bola::setLanzamiento(bool value){
    lanzada = value;
}

/**
 * @brief Bola::playSound Ayuda a reproducir sonidos.
 */
void Bola::playSound(){
    if(golpeBloques->state() == QMediaPlayer::PlayingState) golpeBloques->setPosition(0);
    else if(golpeBloques->state() == QMediaPlayer::StoppedState) golpeBloques->play();
}

/**
 * @brief Bola::movimiento Define el movimiento de la bola y las colisiones con los bloques, bordes y raqueta.
 */
void Bola::movimientoYColisiones(){

    QList<QGraphicsItem *> colliding_items = collidingItems();

    double bolax;
    double bolay;
    double bloquex;
    double bloquey;

    if(y() > largoVentana-50){
        qDebug() <<"Bola perdida";
        lanzada = false;
        emit(bolaPerdida());
        velocidadX=3;
        velocidadY=3;
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
        Profundos* profundo = dynamic_cast<Profundos*>(colliding_items[i]);
        Sorpresa* sorpresa = dynamic_cast<Sorpresa*>(colliding_items[i]);
        Comun* comun = dynamic_cast<Comun*>(colliding_items[i]);
        Dobles* doble = dynamic_cast<Dobles*>(colliding_items[i]);
        Triples* triple = dynamic_cast<Triples*>(colliding_items[i]);
        Internos* interno = dynamic_cast<Internos*>(colliding_items[i]);


        if (sorpresa)
        {
            bolax = pos().x();
            bolay = pos().y();
            bloquex = sorpresa->pos().x();
            bloquey = sorpresa->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;
            }
            if (profundidad >= 1){
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    sorpresa->KSorpresa();
                    velocidadY = -velocidadY;
                    golpe = false;
                    profundidad -= 1;
                    continue;
                }
                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    sorpresa->KSorpresa();
                    velocidadX = -velocidadX;
                    golpe = false;
                    profundidad -=1;
                    continue;
                }
            }
            if (profundidad <= 0 && Eprofundo == true){

                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    sorpresa->KSorpresa();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->scene->removeItem(sorpresa);
                    profundidad = 0;
                    Eprofundo = false;
                    continue;
                }
                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    sorpresa->KSorpresa();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->scene->removeItem(sorpresa);
                    profundidad = 0;
                    Eprofundo = false;
                    continue;
                }
            }
            if (profundidad <= 0 && Eprofundo == false){

                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    sorpresa->KSorpresa();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->scene->removeItem(sorpresa);
                    continue;

                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    sorpresa->KSorpresa();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->scene->removeItem(sorpresa);
                    continue;
                }
            }
        }

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
           if (profundidad >= 1){
               if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    profundidad -=1;
                    continue;

                }

               if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    velocidadX = -velocidadX;
                    golpe = false;
                    profundidad -=1;
                    continue;
                }
           }


           if (profundidad <= 0 && Eprofundo == true){
               if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    juego->setPuntos();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->puntos+=10;
                    juego->scene->removeItem(comun);
                    profundidad = 0;
                    Eprofundo = false;
                    continue;

                }

               if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->puntos+=10;
                    juego->scene->removeItem(comun);
                    Eprofundo = false;
                    profundidad =0;
                    continue;
                }
           }

           if (profundidad <= 0 && Eprofundo == false){
               if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    juego->setPuntos();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->puntos+=10;
                    juego->scene->removeItem(comun);
                    continue;

                }

               if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    juego->setPuntos();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->puntos+=10;
                    juego->scene->removeItem(comun);
                    continue;
                }
           }
        }

        if (profundo)
        {
            //Posiciones de la bola y de los bloques
            bolax = pos().x();
            bolay = pos().y();
            bloquex = profundo->pos().x();
            bloquey = profundo->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;

            }
            if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
             {

                playSound();

                velocidadY = -velocidadY;
                golpe = false;
                (profundidad)+=1;
                Eprofundo = true;
                continue;

            }

            if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
            {
                playSound();

                velocidadX = -velocidadX;
                golpe = false;
                (profundidad)+=1;
                Eprofundo = true;

                continue;
            }
        }

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
            if (profundidad >= 1){ //SI existe profundidad pero no le toca
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    (profundidad)-= 1;
                    continue;
                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    velocidadX = -velocidadX;
                    golpe = false;
                    (profundidad)-= 1;
                    continue;
                }
            }
            if (profundidad <= 0 && Eprofundo == true){ //Existe profundidad y le toca destruirse
                cout<< "Me toca " << " " << profundidad << " " << Eprofundo;
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->setPuntos();
                    juego->puntos+=15;
                    juego->scene->removeItem(doble);
                    (profundidad) = 0;
                    Eprofundo = false;
                    continue;
                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->setPuntos();
                    juego->puntos+=15;
                    juego->scene->removeItem(doble);
                    Eprofundo = false;
                    (profundidad) = 0;
                    continue;
                }
            }

            if (profundidad <= 0 && Eprofundo == false){ // No hay profundidad, actua normal
                cout<< "NO hay profundidad " << " " << profundidad << " " << Eprofundo;

                if ((doble->Vidas()) == true){

                    if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                    {
                        playSound();
                        velocidadY = -velocidadY;
                        golpe = false;
                        juego->setPuntos();
                        juego->puntos+=15;
                        juego->scene->removeItem(doble);
                        continue;
                    }

                    if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
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
                    if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                    {
                        playSound();
                        velocidadY = -velocidadY;
                        golpe = false;
                        continue;
                    }

                    if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                    {
                        playSound();
                        velocidadX = -velocidadX;
                        golpe = false;
                        continue;

                    }
                }
            }
        }
        if(triple)
        {
            bolax = pos().x();
            bolay = pos().y();
            bloquex = triple->pos().x();
            bloquey = triple->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;
            }
            if (profundidad >= 1){ //SI existe profundidad pero no le toca
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    (profundidad)-= 1;
                    continue;
                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    velocidadX = -velocidadX;
                    golpe = false;
                    (profundidad)-= 1;
                    continue;
                }
            }
            if (profundidad <= 0 && Eprofundo == true){ //Existe profundidad y le toca destruirse
                cout<< "Me toca " << " " << profundidad << " " << Eprofundo;
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    juego->setPuntos();
                    juego->puntos+=20;
                    juego->scene->removeItem(triple);
                    (profundidad) = 0;
                    Eprofundo = false;
                    continue;
                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    velocidadX = -velocidadX;
                    golpe = false;
                    juego->setPuntos();
                    juego->puntos+=20;
                    juego->scene->removeItem(triple);
                    Eprofundo = false;
                    (profundidad) = 0;
                    continue;
                }
            }

            if (profundidad <= 0 && Eprofundo == false){ // No hay profundidad, actua normal
                cout<< "NO hay profundidad " << " " << profundidad << " " << Eprofundo;
                if ((triple->Vidas()) == true){
                    if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                    {
                        playSound();
                        juego->setPuntos();
                        juego->puntos+=20;
                        velocidadY = -velocidadY;
                        golpe = false;
                        juego->scene->removeItem(triple);
                        continue;
                    }

                    if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                    {
                        playSound();
                        juego->setPuntos();
                        juego->puntos+=20;
                        velocidadX = -velocidadX;
                        golpe = false;
                        juego->scene->removeItem(triple);
                        continue;
                    }
                }
                else {
                    if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                    {
                        playSound();
                        velocidadY = -velocidadY;
                        golpe = false;
                        continue;
                    }

                    if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                    {
                        playSound();
                        velocidadX = -velocidadX;
                        golpe = false;
                        continue;

                    }
                }
            }
        }
        if(interno){
            bolax = pos().x();
            bolay = pos().y();
            bloquex = interno->pos().x();
            bloquey = interno->pos().y();

            if(juego->scene->items().size()==2)
            {
                velocidadY = 0;
                velocidadX = 0;
            }
            if (profundidad >= 1){ //SI existe profundidad pero no le toca
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    juego->setPuntos();
                    juego->puntos+=30;
                    velocidadY = -velocidadY;
                    golpe = false;
                    (profundidad)-= 1;
                    juego->scene->removeItem(interno);
                    continue;
                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    juego->setPuntos();
                    juego->puntos+=30;
                    velocidadX = -velocidadX;
                    golpe = false;
                    (profundidad)-= 1;
                    juego->scene->removeItem(interno);
                    continue;
                }
            }
            else{
                if ((bolay> bloquey-10 && velocidadY < 0 ) || (bloquey > bolay+15 && velocidadY > 0 ))
                 {
                    playSound();
                    velocidadY = -velocidadY;
                    golpe = false;
                    continue;
                }

                if ((bolax> bloquex+150 && velocidadX < 0 ) || (bloquex > bolax+2 && velocidadX > 0 ))
                {
                    playSound();
                    velocidadX = -velocidadX;
                    golpe = false;
                    continue;
                }
            }
        }
    }
    setPos(x()+velocidadX, y()+velocidadY);
}

/**
 * @brief Bola::reducirBola Funcion que reduce la velocidad de la bola.
 */
void Bola::reducirBola(){
    velocidadX -= 0.5;
    velocidadY -= 0.5;
}

/**
 * @brief Bola::aumentarBola Funcion que aumenta la velocidad de la bola.
 */
void Bola:: aumentarBola(){
    velocidadX += 0.5;
    velocidadY += 0.5;

}
