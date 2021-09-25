#ifndef BLOQUES_H
#define BLOQUES_H
#include <QGraphicsRectItem>

#include <QGraphicsPixmapItem>


#include <list>
#include <iostream>
using namespace std;

class Bloques: public QGraphicsRectItem
{
public:
    Bloques(int color, QGraphicsItem* parent=0);
    //Bloques(void);
    int color;
    int tipo;
    void Clasificacion(int num,double posX, double posY);
    int TipodeBloque(double px, double py);
    bool Comun ( double _px, double _py);
    bool Doble (double px, double py);
    bool Triple (double px, double py);
    bool Profundo (double px, double py);
    bool Sorpresa (double px, double py);



};

#endif // BLOQUES_H
