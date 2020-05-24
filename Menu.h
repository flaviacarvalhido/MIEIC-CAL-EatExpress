//
// Created by joao on 24/05/2020.
//

#ifndef EATEXPRESS_MENU_H
#define EATEXPRESS_MENU_H
#include <iostream>

#include <string>
#include <vector>
#include <GraphViewer/graphviewer.h>
#include "Utils.h"
#include "Point.h"
#include "Graph.h"
#include "parse.h"
#include "Company.h"

void selecaoCaso();
void selecaoCidade();
int opcaoCidade(Company &c);
int opcaoCaso(Company &c,int city);
#endif //EATEXPRESS_MENU_H
