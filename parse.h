//
// Created by ricar on 20/05/2020.
//
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


using namespace std;

void parseNodes(const string path_to_nodes);
void parseEdges(const string path_to_edges);
void parsePorto();

#endif //EATEXPRESS_PARSE_H
