//
// Created by joao on 20/05/2020.
//

#ifndef EATEXPRESS_PARSE_H
#define EATEXPRESS_PARSE_H
#pragma once


#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include <GraphViewer/graphviewer.h>


using namespace std;

void parseNodes(const string path_to_nodes);
void parseEdges(const string path_to_edges);
void parsePorto();
GraphViewer buildGraphViewer(Graph<Point> & temp_graph);

#endif //EATEXPRESS_PARSE_H

