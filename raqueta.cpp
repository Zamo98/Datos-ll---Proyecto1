/**
  * @file raqueta.cpp
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora
  */

#include "raqueta.h"
#include "ventana.h"
#include <QDebug>

/**
 * @brief Raqueta::Raqueta
 * @param parent
 */
Raqueta::Raqueta(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/imagenes/raqueta"));
    ancho = pixmap().width();
    largo = pixmap().height();
}

/**
 * @brief Raqueta::movIzq Define el movimiento de la raqueta hacia la izquierda.
 */
void Raqueta::movIzq(){
    int posX = x();
    posX = posX - velocidad;
    mover(QPoint(posX,y()));
}

/**
 * @brief Raqueta::movDer Define el movimiento de la raqueta hacia la derecha.
 */
void Raqueta::movDer(){
    int posX = x();
    posX = posX + velocidad;
    mover(QPoint(posX,y()));
}
/**
 * @brief Raqueta::mover Hace que la raqueta se mueva.
 * @param p Punto p definido en el plano.
 */
void Raqueta::mover(QPoint p){
    int x = p.x();
    if(x < 0) x = 0;
    if(x > anchoVentana-ancho) x = anchoVentana - ancho;
    setPos(x, y());
}

/**
 * @brief Raqueta::disparo Indica cuando la bola es lanzada.
 */
void Raqueta::disparo(){
    qDebug() << "disparo";
}

/**
 * @brief Raqueta::reducirRaqueta Hace que la raqueta reduzca su tamaño.
 */
void Raqueta::reducirRaqueta(){
    nuevoAncho -= 10;
    setPixmap(QPixmap(":/imagenes/raqueta").scaledToWidth(nuevoAncho,Qt::TransformationMode(0)));
}

/**
 * @brief Raqueta::aumentarRaqueta Hace que la raqueta aumente su tamaño.
 */
void Raqueta::aumentarRaqueta(){
    nuevoAncho += 10;
    setPixmap(QPixmap(":/imagenes/raqueta").scaledToWidth(nuevoAncho,Qt::TransformationMode(0)));

}
