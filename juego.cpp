#include "juego.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QIcon>
#include "bloques.h"


Juego::Juego(QGraphicsView *parent) : QGraphicsView(parent)
{
    //Dise;o de la ventana

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,anchoVentana, largoVentana);
    scene->setBackgroundBrush(QBrush(QImage(":/imagenes/fondo")));
    window()->setWindowIcon(QIcon(":/imagenes/icono2"));
    window()->setWindowTitle(nombreJuego);
    setFixedSize(anchoVentana, largoVentana);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    gameOver = false;
    gameWin = false;

    //Dise;o y posiscion inicial de la raqueta

    raqueta = new Raqueta();
    raqueta->setPos((anchoVentana - raqueta->ancho)/2, largoVentana-100);
    scene->addItem(raqueta);

    bola = new Bola();
    bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);
    connect(bola, SIGNAL(bolaPerdida()), this, SLOT(jugadorPierde()));
    scene->addItem(bola);

    texto = new QGraphicsTextItem();
    texto->setDefaultTextColor(Qt::white);
    mostrarPuntaje();

    show();
}

void Juego::CrearBloque(double y) //Dibujas los bloques
{
    for (size_t k = 0, j = 5; k < j; ++k) //Creacion de columnas
    {
        for (size_t i = 0, n = 10; i < n; ++i) //Creacion de filas
        {
            Bloques* bloques = new Bloques();
            bloques->setPos(i*107,y); //Posicion en x,y
            scene->addItem(bloques);
        }
        y += 40; //Distancia entre y
    }



}

void Juego::Iniciar() { //Inicializar los bloques

    if (gameOver == true){

        if (gameWin == true){
            QList<QGraphicsItem*> allItems = scene->items();
                    for (size_t i = 0,q = scene->items().size() ; i < q ; ++i){
                        Bloques* bloques = dynamic_cast<Bloques*>(allItems[i]);
                        if (bloques){
                            scene->removeItem(bloques);
                        }
                    }
        gameOver = false;
        gameWin = false;
        }

    }

    CrearBloque(0);

}

//Mover la raqueta con las teclas
void Juego::keyPressEvent(QKeyEvent *evento){
    switch (evento->key()) {

    case Qt::Key_Left:
        if(raqueta){
            raqueta->movIzq();
            if(!bola->lanzada) bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);
        }
        break;

    case Qt::Key_Right:
        if(raqueta){
            raqueta->movDer();
            if(!bola->lanzada) bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);

        }
        break;

    case Qt::Key_Space:
        if(raqueta){
            raqueta->disparo();
            bola->setLanzamiento(true);
        }
        break;
    }
}

void Juego::mousePressEvent(QMouseEvent *evento){
    switch(evento->button()){

    case Qt::LeftButton:
        if(raqueta){
            raqueta->disparo();
            bola->setLanzamiento(true);
        }
        break;

    case Qt::RightButton:
        break;

    default:
        break;
    }
}


//Mover la raqueta con el mouse
void Juego::mouseMoveEvent(QMouseEvent *evento){
    if(raqueta){
        raqueta->mover(evento->pos());

    }
}

void Juego::jugadorPierde(){

    vidas--;

    if(vidas == 0) juegoTerminado();
    if(bola){
        bola->setPos(raqueta->x() + (raqueta->ancho - bola->anchoBola)/2, raqueta->y() - bola->largoBola);

    }
}

void Juego::mostrarPuntaje(){
    if(scene->items().contains(texto)) scene->removeItem(texto);
    texto->setPlainText("Puntos: " + QString::number(puntos));

    texto->setPos((anchoVentana - 1000), largoVentana-70);

    //texto->setPos((anchoVentana - (0.68 * texto->font().pointSize()*texto->toPlainText().length()))/2, largoVentana-70);
    scene->addItem(texto);
}

void Juego::setPuntos(){
    puntos+=1;
    mostrarPuntaje();
}

void Juego::juegoTerminado(){
    scene->removeItem(bola);
    QGraphicsTextItem *texto = new QGraphicsTextItem;
    texto -> setDefaultTextColor(Qt::white);

    qDebug() << texto->font().pointSize();
    QString mensaje = "Has perdido!";
    texto->setPlainText(mensaje);
    texto->setPos(anchoVentana/2,largoVentana/2);
    scene->addItem(texto);
    gameOver = true;
    if(scene->items().size()==2){
        gameWin = true;

    }
}
