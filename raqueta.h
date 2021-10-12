/**
  * @file raqueta.h
  * @version 1.0
  * @date 12/10/2021
  * @authors Yaritza López y Gustavo Zamora
  * @brief Funciones para el funcionamiento de la raqueta
  */

#ifndef RAQUETA_H
#define RAQUETA_H

#include <QGraphicsPathItem>
#include <QObject>


class Raqueta : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Raqueta(QGraphicsItem *parent=nullptr);
    int ancho=0;
    int largo=0;
    int nuevoAncho=90;
    /**
     * @brief movDer Define el movimiento de la raqueta hacia la derecha.
     */
    void movDer();
    /**
     * @brief movIzq Define el movimiento de la raqueta hacia la izquierda.
     */
    void movIzq();
    /**
     * @brief mover Hace que la raqueta se mueva.
     * @param p punto p definido en el plano.
     */
    void mover(QPoint p);
    /**
     * @brief disparo Indica cuando la bola es lanzada.
     */
    void disparo();
    /**
     * @brief reducirRaqueta Hace que la raqueta reduzca su tamaño.
     */
    void reducirRaqueta();
    /**
     * @brief aumentarRaqueta Hace que la raqueta aumente su tamaño.
     */
    void aumentarRaqueta();

private:
    int velocidad=15;
};

#endif // RAQUETA_H
