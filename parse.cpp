


#include "parse.h"



using namespace std;


extern Graph<Point> graph;

void parseNodes(const string path_to_nodes,GraphViewer g) {
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
        //g->addNode(id,(int) x,(int) y);
        g.addNode(id,(int)x,(int)y);
    }
}

void parseEdges(const string path_to_edges,GraphViewer g) {
    string temp;
    int id1,id2;
    float x1,x2,y1,y2;
    int weight;
    int edgeid=0;

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
        edgeid++;
        g.addEdge(edgeid,id1,id2,1);
        g.setEdgeWeight(edgeid,weight);
        edgeid++;
        g.addEdge(edgeid,id2,id1,1);
        g.setEdgeWeight(edgeid,weight);
    }
}

void parsePorto( GraphViewer g ) {
    graph = Graph<Point>();
    parseNodes("../PortugalMaps/Porto/nodes_x_y_porto.txt", g);
    parseEdges("../PortugalMaps/Porto/edges_porto.txt",g);
}


