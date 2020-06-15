#include "Graph.h"




Graph::Graph() : sz(0)
{
    int i,j;

    for(i = 0; i < 30; i++){
        esistenza[i] = false;
    }

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            link_matrix[i][j] = 0;
        }
    }

}

Graph::Graph(const Graph &other)
{
    int i,j;

    for(i = 0; i < 30; i++){
        this->esistenza[i] = other.esistenza[i];
    }

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            this->link_matrix[i][j] = other.link_matrix[i][j];
        }
    }

    this->sz = other.sz;
}

Graph& Graph::operator=(const Graph &other)
{
    int i,j;

    for(i = 0; i < 30; i++){
        this->esistenza[i] = other.esistenza[i];
    }

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            this->link_matrix[i][j] = other.link_matrix[i][j];
        }
    }

    this->sz = other.sz;
    return *this;
}

unsigned int Graph::size() const
{
    return sz;
}

unsigned int Graph::n_archi() const
{
    int i, j;
    unsigned int cont = 0;
    for(i = 0; i < 30 ; i++){
        for(j = 0; j < 30; j++){
            //In questo modo esamino solo la parte alta della matrice
            //Essendo essa simmetrica
            if (i > j || i == j)
                        {
                            ;
                        }
            else{
                if( this->link_matrix[i][j] != 0 )
                    cont++;
            }
        }
    }
    return cont;
}

unsigned int Graph::total_interaction() const
{
    int i, j;
    unsigned int cont = 0;
    for(i = 0; i < 30 ; i++){
        for(j = 0; j < 30; j++){
            //In questo modo esamino solo la parte alta della matrice
            //Essendo essa simmetrica
            if (i > j || i == j)
                        {
                            ;
                        }
            else{
                if( this->link_matrix[i][j] != 0 )
                    cont = cont + this->link_matrix[i][j];
            }
        }
    }
    return cont;
}


void Graph::T0()
{
    srand(time(NULL));
    int i;
    int n_nodi = ( rand()% 10 ) + 2; //Non vorrei far riempire subito il grafo


    for(i = 0; i < n_nodi; i++){
        this->esistenza[i] = true;
    } //In questo modo crea i primi n_nodi(random) Nodi

    this->sz = n_nodi;

}

void Graph::TN()
{   //qDebug() << "TN";

    if( this->size() == 0 ){
        //Il grafo viene inizializzato con un numero casuale di nodi
        //qDebug() << "T0";
        this->T0();
        return;
    }

    if( this->size() >= 30 ){
        //qDebug() << "Nodi 30";
        return; //Abbiamo raggiunto il numero massimo di nodi
        //Stop
    }

   //qDebug() << "Nodi";
    srand(time(NULL));


    //Si aggiunge un numero casuale di nuovi nodi
    //(anche nessun nuovo nodo è contemplato)
    unsigned int nodi_possibili = 30 - this->size();
    int n_nodi = rand()%( nodi_possibili+1 );
    this->sz = this->size() + n_nodi;

    int i;
    for(i = 0 ; i < (int)this->size(); i++){
        esistenza[i] = true;
    } //In questo modo continua a creare nuovi nodi

    //qDebug() << "Archi";

    //Si aggiunge un numero casuale di nuovi archi ponendo a +1 il
    //contatore delle interazioni e modificando il colore dei due nodi
    //a cui l’arco è collegato(anche nessun nuovo arco è contemplato)
    int x,y;
    int n_archi = rand()%( this->size()+1 ); //Totalmente arbitrario

    for( i = 0; i < n_archi; i++){
        x = rand()%( this->size()+1 );
        y = rand()%( this->size()+1 );

        if( ( this->link_matrix[x][y] == 0 ) && ( x != y ) ){
            //Creo l'arco
            //qDebug() << "creo arco x-y  " << x << "-" << y;
            this->link_matrix[x][y] = 1;
            this->link_matrix[y][x] = 1;
            //Incremento il colore
            if( this->link_matrix[x][x] < this->link_matrix[x][y]){
                this->link_matrix[x][x] = this->link_matrix[x][y];
            }
            if( this->link_matrix[y][y] < this->link_matrix[x][y]){
                this->link_matrix[y][y] = this->link_matrix[x][y];
            }
        }
    }



    //qDebug() << "Incremento";

    //Si incrementa di un’unità il contatore delle interazioni tra alcuni nodi
    //del grafo scelti casualmente e si modifica coerentemente il colore dei
    //due nodi che collegano l’arco.

    //int n_iter = this->random( this->size() );
    int n_iter = rand()%( this->size()+1);
    bool zero = true; //Garantisce che almeno una volta qualcosa e' stato modificato
    //Se zero e' true nulla e' stato modificato in questo passaggio

    //do{
        for( i = 0; i < n_iter; i++){
            //x = this->random( this->size() );
            //y = this->random( this->size() - 1 );
            x = rand()%( this->size()+1 );
            y = rand()%( this->size()+1 );

            if( ( link_matrix[x][y] != 0 ) && ( x != y ) ){
                //qDebug() << "incremento arco x-y  " << x << "-" << y;
                link_matrix[x][y]++;
                link_matrix[y][x]++;
                zero = false;
                if( link_matrix[x][x] < link_matrix[x][y]){
                    link_matrix[x][x] = link_matrix[x][y];
                }
                if( link_matrix[y][y] < link_matrix[x][y]){
                    link_matrix[y][y] = link_matrix[x][y];
                }
            }
        }

    if( zero ){
        int j;
        for(i = 0; i < 30 && zero ; i++){
            for(j = 0; j < 30 && zero; j++){
                if( ( link_matrix[i][j] != 0 ) && ( i != j ) ){
                    link_matrix[i][j]++;
                    link_matrix[j][i]++;
                    //qDebug() << "Incremento " << i <<"!"<< j;
                    zero = false; //Cosi si esce dai cicli for
                    if( link_matrix[i][i] < link_matrix[i][j]){
                        link_matrix[i][i] = link_matrix[i][j];
                    }
                    if( link_matrix[j][j] < link_matrix[i][j]){
                        link_matrix[j][j] = link_matrix[i][j];
                    }
                }
            }
        }
    }

   //}while( zero );

    //qDebug() << "Exit TN";

}










