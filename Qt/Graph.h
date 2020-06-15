#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
//#include <QDebug>

class Graph: public QObject
{
    bool esistenza[30]; //Se esistenza[i] e' true allora il nodo i esiste
    unsigned int link_matrix[30][30]; //La diagonale e' il colore del nodo
    unsigned int sz; //Numero di nodi inizializzati
    Q_OBJECT

public:
    friend class Controller;

    //Costruttore default
    Graph();

    //Dstruttore
    ~ Graph()
    {
        //Defaultin Qt
    }

    //Costruttore copia
    Graph(const Graph &other);

    //Operatore assegnamento
    Graph& operator=(const Graph &other);

    Graph& operator=(Graph *other);

    void TN();

    unsigned int size() const;

    unsigned int n_archi() const;

    unsigned int total_interaction() const;

private:

    void T0();

};

#endif // GRAPH_H
