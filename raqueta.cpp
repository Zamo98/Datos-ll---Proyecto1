#include "raqueta.h"
#include "ventana.h"
#include <QDebug>

Raqueta::Raqueta(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/imagenes/raqueta"));
    ancho = pixmap().width();
    largo = pixmap().height();
}

void Raqueta::movIzq(){
    int posX = x();
    posX = posX - velocidad;
    mover(QPoint(posX,y()));
}

void Raqueta::movDer(){
    int posX = x();
    posX = posX + velocidad;
    mover(QPoint(posX,y()));
}

void Raqueta::mover(QPoint p){
    int x = p.x();
    if(x < 0) x = 0;
    if(x > anchoVentana-ancho) x = anchoVentana - ancho;
    setPos(x, y());
}

void Raqueta::disparo(){
    qDebug() << "disparo";
}

void Raqueta::reducirRaqueta(){
    nuevoAncho -= 10;
    setPixmap(QPixmap(":/imagenes/raqueta").scaledToWidth(nuevoAncho,Qt::TransformationMode(0)));
}

void Raqueta::aumentarRaqueta(){
    nuevoAncho += 10;
    setPixmap(QPixmap(":/imagenes/raqueta").scaledToWidth(nuevoAncho,Qt::TransformationMode(0)));

}
