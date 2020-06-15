# Dynamic-Interaction-Graph
Un’interfaccia grafica per la visualizzazione di un Dynamic Interaction Graph.
You can find the full assignment text in Italian [Here](https://github.com/davidepietrasanta/dynamic-interaction-graph/blob/master/Esame-200615.pdf)

The project must be written using Qt library.

The project requires the creation of a Dynamic Interaction Graph. This is a model suitable for
representation of social interactions (e.g. social interactions
Network). 

The application must present a snapshot of the graph Interactions: 

1. The state of the graph is updated iteratively with intervals
timed for one second. The application must be published

2. At iteration T 0, the graph is initialized with a random number of nodes

3. The following actions take place at the T n iterations:

- A random number of new nodes is added (even no new ones
knot is contemplated);

- A random number of new arcs is added to +1
interaction counter and color change of the two nodes of which
the arch is connected (also no new arch is contemplated);

- The counter of the interactions between some nodes is increased by one unit
of the graph chosen randomly and the color of the coherently changes
two knots connecting the arch.

Note 0: In the case of a node with multiple arcs, its color depends on the plus value high among the interaction counters



Note 1: Use version 5.11 or higher of the Qt library.

Note 2: Make the content of the adaptive application window size.
