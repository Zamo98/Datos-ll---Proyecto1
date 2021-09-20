#include "bola.h"
#include "ventana.h"
#include "raqueta.h"

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

void Bola::setLanzamiento(bool value){
    lanzada = value;
}

void Bola::movimiento(){
    if(y() > largoVentana-50){
        qDebug() <<"Bola perdida";
        lanzada = false;
        emit(bolaPerdida());
    }

    if(lanzada){
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(auto i : colliding_items){
            if(typeid(*i) == typeid (Raqueta) && !golpe){
                velocidadY = -velocidadY;
                setPos(x()+velocidadX, y()+velocidadY);
                golpe = true;
                return;
            }
        }
    }
    int vX = x()+velocidadX;
    int vY = y()+velocidadY;
    if(vX < 0 || vX+anchoBola > anchoVentana){
        velocidadX = -velocidadX;
        golpe = false;
    }
    if(vY < 0 || vY+largoBola > largoVentana){
        velocidadY = -velocidadY;
        golpe = false;
    }
    setPos(x()+velocidadX, y()+velocidadY);
}
