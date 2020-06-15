#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
//#include <QDebug>
#include <QTime>
#include <QLabel>
#include <QCoreApplication>
#include <QPainter>
#include <QStaticText>
#include "Graph.h"

class Controller : public QWidget
{
    Graph graph;
    QPoint posizioni[30]; //Salvo le posizioni per evitare sovrapposizioni
    //Se posizioni[i] == QPoint(0,0) Non esiste ancora una posizione
    unsigned int time_counter;

public:


   explicit Controller(QWidget *parent = nullptr) : QWidget{parent}, time_counter(0)
    {
        //qDebug() << "Costruttore";
        int i,j;

        for(i = 0; i < 30; i++){
            graph.esistenza[i] = false;
        }

        for(i = 0; i < 30; i++){
            for(j = 0; j < 30; j++){
                graph.link_matrix[i][j] = 0;
            }
        }
        graph.sz = 0;


        for(i = 0; i < 30; i++){
            posizioni[i] = QPoint(0,0);
        }

   }


    ~ Controller()
    {
        //Default per Qt
    }

private:

    //Controlla che non ci siano già Nodi nella posizione
    //E se la posizione va bene per un nuovo Nodo
    bool check_posizioni(int r1, int r2){
        QPoint p = QPoint(r1, r2);
        int i;
        for(i = 0; i < 30; i++){
            if( posizioni[i] == p )
                return true;
        }
        if( p.x() > 49 && p.y() > 49 ) //Garantisce la visibilita'
            return false;
        else
            return true;
    }

    void delay(int n = 1)
    {
        //qDebug() << "Delay " << this->time_counter;
        QTime dieTime= QTime::currentTime().addSecs(n);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        this->time_counter++;
        update();
    }

    QColor colorize(int v, int d = 100) const
    {
        //d determina il range delle iterazioni
        int vt = v;
        if( vt > d )
            vt = vt%d;
        /*
            In questo modo si riparte da capo con i colori
            Il problema e' che il fattore randomico rende il tutto imprevedibile
            Potrebbe non arrivare mai ad un punto di stop e quindi le interazioni
            potrebbero essere un numero altissimo
        */
        qreal rv = qreal(vt) / d;
        QColor c = QColor::fromHsl(205 - (205 - 42) * rv, 200, 135);
        return c;
    }

    QPoint choosePosition(int r0)
    {
        int r1, r2;

        if( r0 < 6 ){
            r1 = 50+r0*50;
            r2 = 50+( (r0%2) * 50);
        }
        else if ( r0 < 12 ) {
            r1 = 50+( (r0%6) *50);
            r2 = 50*2+( ((r0-6)%2) *50);
        }
        else if ( r0 < 18 ) {
            r1 = 50+( (r0%6) *50);
            r2 = 50*4+( ((r0-12)%2) *50);
        }
        else if ( r0 < 24 ) {
            r1 = 50+( (r0%6) *50);
            r2 = 50*6+( ((r0-18)%2) *50);
        }
        else{
            r1 = 50*8+( ((r0-24)%2) *50);
            r2 = 50+( (r0%6) *50);
        }
        return QPoint(r1, r2);

        /*
        if( i < 6 ){
            r1 = 50+i*50;
            r2 = 50+( (i%2) * 50);
        }
        else if ( i < 12 ) {
            r1 = 50+( (i%6) *50);
            r2 = 50*2+( ((i-6)%2) *50);
        }
        else if ( i < 18 ) {
            r1 = 50*8+( ((i-12)%2) *50);
            r2 = 50+( (i%6) *50);
        }
        else if ( i < 24 ) {
            r1 = 50+( (i%6) *50);
            r2 = 50*6+( ((i-18)%2) *50);
        }
        else{
            r1 = 50+( (i%6) *50);
            r2 = 50*4+( ((i-24)%2) *50);
        }
        */
        //Forma alternativa
        /*
        if( i < 6 ){
            r1 = 50+i*50;
            r2 = 50+( (i%2) * 50);
        }
        else if ( i < 12 ) {
            r1 = 50+( (i%6) *50);
            r2 = 50*2+( ((i-6)%2) *50);
        }
        else if ( i < 18 ) {
            r1 = 50+( (i%6) *50);
            r2 = 50*4+( ((i-12)%2) *50);
        }
        else if ( i < 24 ) {
            r1 = 50+( (i%6) *50);
            r2 = 50*6+( ((i-18)%2) *50);
        }
        else{
            r1 = 50*8+( ((i-24)%2) *50);
            r2 = 50+( (i%6) *50);
        }
        */
    }

public:

    void paintEvent(QPaintEvent *) override{
        //qDebug() << "paintEvent";
        this->graph.TN();
        //qDebug() << "Graph Size: " <<  this->graph->size() ;
        //qDebug() << "Arch Size: " <<  this->graph->n_archi() ;
        //qDebug() << "Interaction Size: " <<  this->graph->total_interaction() ;
        paint_graph();
        if( this->graph.size() >= 30 )
            return;
        delay();
    }

signals:
    void state_graph();

public slots:

    void paint_graph(){

        //qDebug() << "Paint_graph";
        QPainter painter(this); //Disegno gli Archi
        QPainter p(this); //Disegno i Nodi
        QColor colorRed(255, 0, 0);
        QColor colorBlack(0, 0, 0);

        p.setPen(QPen(colorRed)); //SET COLORE NODI RED
        p.setBrush(QBrush(colorRed));
        //Se vedo nodi rossi non sono stati colorati

        QColor colorIteration;

        //Nodi
        int i;
        int r0;
        QPoint q0;
        for(i = 0; i < (int)this->graph.size() ; i++){
            if( posizioni[i] == QPoint(0,0) ){
                do{
                    r0 = rand()%(this->graph.size()+1);
                    q0 = choosePosition(r0);
                }while( check_posizioni(q0.x(), q0.y() ));

                posizioni[i] = q0;
                //qDebug() <<"Draw point " << posizioni[i] ;

                //p.drawEllipse(r1, r2, 5, 5);
                //qDebug() << "Paint_graph end draw";
            }

            //qDebug() <<"Draw point " << posizioni[i] << " , interaction " << graph->link_matrix[i][i];
            colorIteration = colorize(graph.link_matrix[i][i], 10); //Metto d = 10 per risaltare maggiormente i vari colori
            p.setPen( QPen( colorBlack )); //SET COLORE CONTORNI NODI
            p.setBrush(QBrush( colorIteration )); //SET COLORE NODI
            p.drawEllipse( posizioni[i], 5, 5);


        }


        painter.setPen(QPen(colorBlack));
        p.setPen(QPen(colorBlack));

        int j;
        int temp;
        QString temp_str;
        QPoint iter_point;
        QString iter_text;
        for(i = 0; i < 30 ; i++){
            for(j = 0; j < 30; j++){
                //In questo modo esamino solo la parte alta della matrice
                //Essendo essa simmetrica
                if (i > j || i == j)
                            {
                                ;
                            }
                else{
                    //qDebug() << "Matrix " << i <<"," << j << " = " << this->graph->link_matrix[i][j];
                    if( this->graph.link_matrix[i][j] != 0 && i != j ){
                        if( posizioni[i] != QPoint(0,0) && posizioni[j] != QPoint(0,0)){
                            //qDebug() << "Line " << posizioni[i] << posizioni[j] ;
                            painter.drawLine(posizioni[i], posizioni[j]);

                            iter_point = QPoint( (posizioni[i].x() + posizioni[j].x())/2, (posizioni[i].y() + posizioni[j].y())/2 );
                            temp = (int)(graph.link_matrix[i][j]);
                            iter_text = QString('+').append( temp_str.setNum(temp) );
                            painter.drawText(iter_point,iter_text);
                        }
                    }
                }

            }

        }
        update();
    }






};

#endif // CONTROLLER_H
