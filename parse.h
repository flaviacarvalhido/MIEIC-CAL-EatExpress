
#pragma once

#ifndef EATEXPRESS_PARSE_H
#define EATEXPRESS_PARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include <GraphViewer/graphviewer.h>


using namespace std;

void parseNodes(const string path_to_nodes,GraphViewer g);
void parseEdges(const string path_to_edges,GraphViewer g);
void parsePorto(GraphViewer g);

#endif //EATEXPRESS_PARSE_H
