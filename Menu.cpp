//
// Created by joao on 24/05/2020.
//

#include "Menu.h"


void selecaoCaso() {
    cout << "Escolha o caso de execucao que pretende:" << endl;
    cout << "1 - Uma encomenda com itens de apenas um restaurante" << endl;
    cout << "2 - Uma encomenda com itens de varios restaurantes" << endl;
    cout << "3 - Varias encomendas para clientes diferentes do mesmo restaurante" << endl;
    cout << "0 - Exit" << endl;
}
void selecaoCidade(){
    cout << "Escolha a sua cidade:" << endl;
    cout << "1 - Porto" << endl;
    cout << "2 - Viseu" << endl;
    cout << "0 - Exit" << endl;
}
int opcaoCidade() {

    int menuOption;

    do {
        selecaoCidade();
        cin >> menuOption;

        switch(menuOption) {
            case 0: // Exit

                return 0;
            case 1: // Porto
                parsePorto();
                return 1;
            case 2: // Viseu
                //parseViseu
                return 2;

            default:
                cout << "Invalid input" << endl;
                break;
        }

    } while(true);
}
int opcaoCaso(Company &c,int city) {

    int menuOption;

    do {
        selecaoCaso();
        cin >> menuOption;

        switch(menuOption) {
            case 0: // Exit
                return 0;
            case 1:
                if(city==1) c.readDeliveriesFile("../Deliveries.txt");
                //viseufile
                return 1;
            case 2:
                if(city==1) c.readDeliveriesFile("../Deliveries2.txt");
                //segundo caso
                return 2;
            case 3:
                if(city==1) c.readDeliveriesFile("../Deliveries3.txt");
                return 3;

            default:
                cout << "Invalid input" << endl;
                break;
        }

    } while(true);
}