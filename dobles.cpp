#include "dobles.h"
#include <iostream>
#include <QGraphicsItemGroup>
#include<QtGui>

using namespace std;

Dobles::Dobles(int _Vida, QGraphicsItem* parent): QGraphicsItemGroup(parent)
{
    Vida = _Vida;
}

QRectF Dobles:: boundingRect() const{
    return QRectF (0,0,95,40);
}

void Dobles:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush (Qt:: red);
    painter -> drawRoundedRect(0,0, 95, 40, 10, 10);
}

bool Dobles::Vidas(){
    Vida = (Vida - 1);
    //cout<<"La vida es"<<" "<<Vida<<" "<<":D";
    if(Vida <= 0){
        return true;
    }
    else{
        return false;
    }
}


