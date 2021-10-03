#include "profundos.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>
using namespace std ;

Profundos::Profundos(QGraphicsItem* parent): QGraphicsItemGroup(parent)
{

}
QRectF Profundos:: boundingRect() const{
    return QRectF (0,0,95,40);
}

void Profundos:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: black);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);


}
void Profundos::Masprofundidad(int x){
    x += 1;
}
void Profundos::Menosprofundidad(int x){
    x-= 1;
 }

int Profundos::cant_profundidad(){
    return profundida;
}
