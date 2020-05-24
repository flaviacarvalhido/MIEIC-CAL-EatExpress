/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <math.h>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // outgoing edges
    bool visited;          // auxiliary field
    double dist = 0;
    Vertex<T> *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    void addEdge(Vertex<T> *dest, double w);


public:
    Vertex(T in);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    T getInfo() const;
    vector <Edge<T>> getAdj();
    double getDist() const;
    Vertex *getPath() const;
    bool getVisited();

    void setDist(int i);
    void setPath(Vertex<T> *v);

    bool removeEdgeTo(Vertex<T> *d);
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(this, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
vector <Edge<T>> Vertex<T>::getAdj() {
    return adj;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
bool Vertex<T>::getVisited() {
    return visited;
}

template <class T>
void Vertex<T>::setDist(int i){
    this->dist=i;
}

template <class T>
void Vertex<T>::setPath(Vertex<T> *v){
    this->path=v;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> *orig; 	// Fp07
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight

    bool selected; // Fp07

public:
    Edge(Vertex<T> *o, Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;

    Vertex<T> * getOrig(){
        return orig;
    };
    Vertex<T> * getDest(){
        return dest;
    };

    // Fp07
    double getWeight() const;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}


/*************************** Graph  **************************/

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set
    // Fp05
    Vertex<T> * initSingleSource(const T &orig);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
    double ** W = nullptr;   // dist
    int **P = nullptr;   // path
    int findVertexIdx(const T &in) const;


public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    vector<Vertex<T> *> getVertexSet() const;


    vector<T> dfs() const;
    void dfsVisit(Vertex<T> *v, vector<T> & res) const;
    vector<T> bfs(const T & source) const;

    bool removeEdge();


    // Fp05 - single source
    void dijkstraShortestPath(const T &s);
    void unweightedShortestPath(const T &s);
    void bellmanFordShortestPath(const T &s);
    vector<T> getPath(const T &origin, const T &dest) const;

    Vertex<T>* findIdxVertex(int i);

    bool removeEdge(const T &sourc, const T &dest);

    // Fp05 - all pairs
    void floydWarshallShortestPath();
    vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
    ~Graph();

    // Fp07 - minimum spanning tree
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);
    vector<Vertex<T>*> calculatePrim();
    vector<Vertex<T>*> calculateKruskal();




    void Astar(const T &origin, const T &dest);

    bool aStarRelax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight);
};


template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++){
        if (it->dest->info == d->info) {
            adj.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T>* s = findVertex(sourc);
    Vertex<T>* d = findVertex(dest);
    if (s == NULL || d == NULL) return false;
    return s->removeEdgeTo(d);
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}


/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return nullptr;
}

template <class T>
Vertex<T> * Graph<T>::findIdxVertex(int i) {
    return vertexSet.at(i);
}

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

/**************** Single Source Shortest Path algorithms ************/

/**
 * Initializes single source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
    for(auto v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    auto s = findVertex(origin);
    s->dist = 0;
    return s;
}

/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template<class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
                    auto s = initSingleSource(origin);
                    MutablePriorityQueue<Vertex<T>> q;
                    q.insert(s);
                    while( ! q.empty() ) {
                        auto v = q.extractMin();
                        for(auto e : v->adj) {
                            auto oldDist = e.dest->dist;
                            if (relax(v, e.dest, e.weight)) {
                                if (oldDist == INF)
                                    q.insert(e.dest);
                                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    vector<T> res;
    auto v = findVertex(dest);
    if (v == nullptr || v->dist == INF) // missing or disconnected
        return res;
    for ( ; v != nullptr; v = v->path)
        res.push_back(v->info);
    reverse(res.begin(), res.end());
    return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    auto s = initSingleSource(orig);
    queue< Vertex<T>* > q;
    q.push(s);
    while( ! q.empty() ) {
        auto v = q.front();
        q.pop();
        for(auto e: v->adj)
            if (relax(v, e.dest, 1))
                q.push(e.dest);
    }
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    initSingleSource(orig);
    for (unsigned i = 1; i < vertexSet.size(); i++)
        for (auto v: vertexSet)
            for (auto e: v->adj)
                relax(v, e.dest, e.weight);
    for (auto v: vertexSet)
        for (auto e: v->adj)
            if (relax(v, e.dest, e.weight))
                cout << "Negative cycle!" << endl;
}


/**************** All Pairs Shortest Path  ***************/

template <class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}



template <class T>
Graph<T>::~Graph() {
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    unsigned n = vertexSet.size();
    deleteMatrix(W, n);
    deleteMatrix(P, n);
    W = new double *[n];
    P = new int *[n];
    for (unsigned i = 0; i < n; i++) {
        W[i] = new double[n];
        P[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            W[i][j] = i == j? 0 : INF;
            P[i][j] = -1;
        }
        for (auto e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->info);
            W[i][j]  = e.weight;
            P[i][j]  = i;
        }
    }

    for(unsigned k = 0; k < n; k++)
        for(unsigned i = 0; i < n; i++)
            for(unsigned j = 0; j < n; j++) {
                if(W[i][k] == INF || W[k][j] == INF)
                    continue; // avoid overflow
                int val = W[i][k] + W[k][j];
                if (val < W[i][j]) {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }
}

/*
template<class T>
template <class T>
std::vector<Vertex<T> *> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional)
{
    startTime();

    vector<Vertex<T> *> final_path, path;

    thread t1(dijkstraShortestPath<T>, graph, origin, delivery);

    if(bidirectional){
        //	thread t2(dijkstraShortestPath<T>, graph, delivery, dest);
        Graph<T> newGraph = graph->duplicate();
        dijkstraShortestPath<T>(&newGraph, delivery, dest);

        t1.join();

        final_path = graph->getPath(origin, delivery);
        path = newGraph.getPath(delivery, dest);

        final_path.insert(final_path.end(), path.begin(), path.end());
    }
    else{
        Graph<T> invertedGraph = graph->invert();
        dijkstraShortestPath<T>(&invertedGraph, dest, delivery);

        t1.join();

        final_path = graph->getPath(origin, delivery);
        path = invertedGraph.getPath(dest, delivery);

        // TODO: verify
        final_path.insert(final_path.end(), path.rbegin(), path.rend());
    }
//	cout << final_path.size() << " <- final_path\n";


    writeTime(BIDIJKSTRA, graph, bidirectional);

    return final_path;
}*/
template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
        return res;
    for ( ; j != -1; j = P[i][j])
        res.push_back(vertexSet[j]->info);
    reverse(res.begin(), res.end());
    return res;
}
template <class T>
void Graph<T>::Astar( const T &origin, const T &dest){

    auto org = initSingleSource(origin);
    auto d = findVertex(dest);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(org);

    while( ! q.empty() ) {
        auto v = q.extractMin();

        if(v == d)
            break;

        for(auto e : v->getAdj()) {

            auto oldDist = e.getDest()->getDist();
            if (aStarRelax(v, e.getDest(), d, e.getWeight())) {
                if (oldDist == INF)
                    q.insert(e.getDest());
                else
                    q.decreaseKey(e.getDest());
            }
        }
    }

}
template <class T>
bool Graph<T>::aStarRelax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight) {

    if (v->dist + weight < w->dist){
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else{
        return false;
    }
}


/**************** Minimum Spanning Tree  ***************/
template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    // TODO
    return false;
}



template <class T>
vector<Vertex<T>* > Graph<T>::calculatePrim() {
    // TODO
    return vertexSet;
}



template <class T>
vector<Vertex<T>*> Graph<T>::calculateKruskal() {
    // TODO
    return vertexSet;
}



#endif /* GRAPH_H_ */
