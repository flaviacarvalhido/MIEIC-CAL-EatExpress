//
// Created by joao on 20/05/2020.
//
#include "Parse.h"



using namespace std;


extern Graph<Point> graph;

void parseNodes(const string path_to_nodes) {
    string temp;
    int id;
    double x,y;
    Point point = Point();

    ifstream nodes_file;
    nodes_file.open(path_to_nodes);

    getline(nodes_file,temp); //Discarded number of nodes

    vector<string> temp_vec;

    while (!nodes_file.eof()) {
        getline(nodes_file,temp);
        temp_vec = decompose(temp.substr(1,temp.size() - 2),',');
        trim(temp_vec[0]);
        trim(temp_vec[1]);
        trim(temp_vec[2]);
        id = stoi(temp_vec[0]);
        x = stod(temp_vec[1]);
        y = stod(temp_vec[2]);
        point = Point(id,x,y);
        graph.addVertex(point);

    }
}

void parseEdges(const string path_to_edges) {
    string temp;
    int id1,id2;
    float x1,x2,y1,y2;
    int weight;

    vector<string> temp_vec;

    ifstream edges_file;
    edges_file.open(path_to_edges);

    getline(edges_file, temp); //Discarded number of edges

    while (!edges_file.eof()) {
        getline(edges_file,temp);
        temp_vec = decompose(temp.substr(1, temp.size() - 1), ',');
        trim(temp_vec[0]);
        trim(temp_vec[1]);
        id1 = stoi(temp_vec[0]);
        id2 = stoi(temp_vec[1]);

        Point point1 = Point(id1);
        Point point2 = Point(id2);

        x1 = graph.findVertex(point1)->getInfo().getX();
        x2 = graph.findVertex(point2)->getInfo().getX();
        y1 = graph.findVertex(point1)->getInfo().getY();
        y2 = graph.findVertex(point2)->getInfo().getY();

        weight = sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));

        graph.addEdge(id1,id2,weight);
        graph.addEdge(id2,id1,weight);

    }
}

void parsePorto() {

    parseNodes("../PortugalMaps/Porto/nodes_x_y_porto.txt");
    parseEdges("../PortugalMaps/Porto/edges_porto.txt");
}
void parseViseu() {
    parseNodes("../PortugalMaps/Viseu/nodes_x_y_viseu.txt");
    parseEdges("../PortugalMaps/Viseu/edges_viseu.txt");
}

GraphViewer buildGraphViewer(Graph<Point> & temp_graph) {
    GraphViewer gv = GraphViewer(900, 900, false);
    gv.createWindow(900, 900);
    gv.defineVertexColor("blue");
    gv.defineEdgeColor("black");

    double yPercent, xPercent;

    Vertex<Point>* p = graph.findIdxVertex(0);

    double minX = p->getInfo().getX();
    double minY = p->getInfo().getY();
    double maxX = p->getInfo().getX();
    double maxY = p->getInfo().getY();

    for (int i = 1; i < graph.getNumVertex(); i++) {

        p = graph.findIdxVertex(i);

        if (p->getInfo().getX() > maxX) {
            maxX = p->getInfo().getX();
        } else if (p->getInfo().getX() < minX) {
            minX = p->getInfo().getX();
        }

        if (p->getInfo().getY() > maxY) {
            maxY = p->getInfo().getY();
        } else if (p->getInfo().getY() < minY) {
            minY = p->getInfo().getY();
        }
    }


    double graphHeight = maxY - minY;
    double graphWidth = maxX - minX;

    for (int i = 0; i < graph.getNumVertex(); i++) {
        Vertex<Point>* p = graph.findIdxVertex(i);

        if(p->getVisited()) {                   //only prints reachable vertexes
            xPercent = (p->getInfo().getX() - minX) / graphWidth;
            yPercent = 1.0 - ((p->getInfo().getY() - minY) / graphHeight);

            gv.addNode(p->getInfo().getID(), (int) (xPercent * 4000), (int) (yPercent * 2000));
            gv.setVertexColor(p->getInfo().getID(), "orange");
        }
    }


    vector<Edge<Point>> edges;
    int id =0;
    for (size_t i = 0; i < graph.getNumVertex(); i++) {
        Vertex<Point>* p = graph.findIdxVertex(i);

        if(p->getVisited()) {               //only prints reachable vertexes
            edges = p->getAdj();
            for (Edge<Point> e : edges) {

                id++;
                gv.addEdge(id, p->getInfo().getID(), e.getDest()->getInfo().getID(), EdgeType::DIRECTED);
            }
        }
    }

    gv.rearrange();

    return gv;
}


