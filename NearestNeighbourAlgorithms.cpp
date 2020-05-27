
#include "NearestNeighbourAlgorithms.h"

int case1(Company c, Graph<Point> graph, GraphViewer gv){

    if(!graph.findVertex(c.getDeliveries()[0].getClient().getId())->getVisited()){
        cout << "Cliente com ID " << c.getDeliveries()[0].getClient().getId() << " não e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
        return -3;
    }

    if(!graph.findVertex(c.getDeliveries()[0].getRestaurant()[0].getId())->getVisited()){
        cout << "Restaurante com ID " << c.getDeliveries()[0].getRestaurant()[0].getId() << " não e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
        return -3;
    }


    cout << "A calcular rota, um momento por favor..." << endl;


    vector<Point> perfectPath;


    graph.dijkstraShortestPath(c.getDeliveries()[0].getRestaurant()[0].getId());
    perfectPath = graph.getPath(c.getDeliveries()[0].getRestaurant()[0].getId(),c.getDeliveries()[0].getClient().getId());
    for(int i=0;i<perfectPath.size();i++){
        gv.setVertexColor(perfectPath[i].getID(), "green");
    }

    gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(), "red");

    gv.setVertexColor(perfectPath[0].getID(),"black");
    gv.setVertexLabel(perfectPath[0].getID(),"origin");

    double dist=graph.findVertex(perfectPath[perfectPath.size()-1].getID())->getDist();
    int espaco=c.getDeliveries()[0].calculateOccupiedSpace();
    Deliverer d=c.decideDeliverer(dist,c.getDeliveries()[0].calculateOccupiedSpace());
    cout<<"O estafeta encarregado da sua entrega e: "<<d.getID()<<endl;
    cout<<"O tempo estimado para a sua entrega e "<<int(((dist/1000)/d.getvMed())*60)+1<<" minutos"<<endl;

    system("pause");

    return 0;
}

int case2(Company c, Graph<Point> graph, GraphViewer gv){
    vector<Point> temp_result, result;

    vector<Restaurant> deliveryRestaurants = c.getDeliveries()[0].getRestaurant();
    double dist= 0;
    int min_distance = 999999999;
    int smallest_distance_index = 0;

    for(unsigned int i=0;i<deliveryRestaurants.size();i++){
        if(!graph.findVertex(deliveryRestaurants[i].getId())->getVisited()){
            cout << "Restaurante com ID " << deliveryRestaurants[i].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
            return -3;
        }
    }
    if(!graph.findVertex(c.getClients()[0].getId())->getVisited()){
        cout << "Cliente com ID " << c.getClients()[0].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
        return -3;
    }


    cout << "A calcular rota, um momento por favor..." << endl;


    for (int i = 0; i < c.getDeliveries()[0].getRestaurant().size(); i++) {
        graph.Astar(c.getClients()[0].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());

        if (graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist() < min_distance) {
            temp_result = graph.getPath(c.getClients()[0].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());
            smallest_distance_index = i;
            min_distance = graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist();
        }
    }

    result.insert(result.end(),temp_result.begin(),temp_result.end());     //caminho mais rápido da casa do cliente ao primeiro restaurante


    dist+=min_distance;
    min_distance = 999999999;   //reset min_distance

    int smallest_restaurant_distance = 0;
    //percorrer restantes restaurantes e ver caminho mais rápido entre cada um deles; adicionar ao resultado final até terem sido visitados todos os restaurantes
    while (c.getDeliveries()[0].getRestaurant().size() != 1){

        min_distance = 999999999;


        for (int i = 0; i < c.getDeliveries()[0].getRestaurant().size(); i++) {
            if(i==smallest_distance_index) continue;

            graph.Astar(c.getDeliveries()[0].getRestaurant()[smallest_distance_index].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());

            if (graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist() < min_distance) {
                temp_result = graph.getPath(c.getDeliveries()[0].getRestaurant()[smallest_distance_index].getId(), c.getDeliveries()[0].getRestaurant()[i].getId());
                smallest_restaurant_distance = i;
                min_distance = graph.findVertex(c.getDeliveries()[0].getRestaurant()[i].getId())->getDist();
            }
        }

        if(smallest_restaurant_distance > smallest_distance_index){
            smallest_restaurant_distance--;
        }

        dist+=min_distance;
        result.insert(result.end(),temp_result.begin(),temp_result.end());
        vector <Restaurant> r = c.getDeliveries()[0].getRestaurant();
        r.erase(r.begin()+smallest_distance_index);
        vector<Delivery> d = c.getDeliveries();
        d[0].setRestaurant(r);
        c.setDeliveries(d);
        smallest_distance_index = smallest_restaurant_distance;

    }
    Deliverer d=c.decideDeliverer(dist,c.getDeliveries()[0].calculateOccupiedSpace());
    cout<<"O estafeta encarregado da sua entrega e: "<<d.getID()<<endl;
    cout<<"O tempo estimado para a sua entrega e "<<int(((dist/1000)/d.getvMed())*60)+1<<" minutos"<<endl;
    for(int i=0;i<result.size();i++){
        gv.setVertexColor(result[i].getID(), "green");
    }
    gv.setVertexColor(result[0].getID(), "red");

    for(unsigned int i = 0;i<deliveryRestaurants.size();i++){
        gv.setVertexColor(deliveryRestaurants[i].getId(), "red");
    }

    gv.setVertexColor(result[result.size()-1].getID(),"black");
    gv.setVertexLabel(result[result.size()-1].getID(),"origin");

    system("pause");

    return 0;
}

int case3(Company c, Graph<Point> graph, GraphViewer gv){

    vector<Point> temp_result, result;

    vector<Client> deliveryClients = c.getClients();
    double dist= 0;
    int min_distance = 999999999;
    int smallest_distance_index = 0;

    for(unsigned int i=0;i<deliveryClients.size();i++){
        if(!graph.findVertex(deliveryClients[i].getId())->getVisited()){
            cout << "Cliente com ID " << deliveryClients[i].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
            return -3;
        }
    }
    if(!graph.findVertex(c.getDeliveries()[0].getRestaurant()[0].getId())->getVisited()){
        cout << "Restaurante com ID " << c.getDeliveries()[0].getRestaurant()[0].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
        return -3;
    }


    cout << "A calcular rota, um momento por favor..." << endl;


    for (int i = 0; i < c.getClients().size(); i++) {
        graph.Astar(c.getDeliveries()[0].getRestaurant()[0].getId(), c.getClients()[i].getId());
        if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance) {
            temp_result = graph.getPath(c.getDeliveries()[0].getRestaurant()[0].getId(),c.getClients()[i].getId());
            smallest_distance_index = i;
            min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
        }
    }
    dist+=min_distance;
    result.insert(result.end(),temp_result.begin(),temp_result.end());


    min_distance = 999999999;   //reset min_distance

    int smallest_client_distance = 0;

    while (c.getClients().size() != 1){

        min_distance = 999999999;


        for (int i = 0; i < c.getClients().size(); i++) {
            if(i==smallest_distance_index) continue;

            graph.Astar(c.getClients()[smallest_distance_index].getId(), c.getClients()[i].getId());

            if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance) {
                temp_result = graph.getPath(c.getClients()[smallest_distance_index].getId(), c.getClients()[i].getId());
                smallest_client_distance = i;
                min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
            }
        }

        if(smallest_client_distance > smallest_distance_index){
            smallest_client_distance--;
        }

        dist+=min_distance;
        result.insert(result.end(),temp_result.begin(),temp_result.end());
        vector <Client> cli = c.getClients();
        cli.erase(cli.begin()+smallest_distance_index);
        c.setClients(cli);
        smallest_distance_index = smallest_client_distance;

    }
    int esp=c.getDeliveries()[0].calculateOccupiedSpace()+c.getDeliveries()[1].calculateOccupiedSpace()+c.getDeliveries()[2].calculateOccupiedSpace();
    Deliverer d=c.decideDeliverer(dist,esp);
    cout<<"O estafeta encarregado da sua entrega e: "<<d.getID()<<endl;
    cout<<"O tempo estimado para a sua entrega e "<<int(((dist/1000)/d.getvMed())*60)+1<<" minutos"<<endl;
    for(int i=0;i<result.size();i++){
        gv.setVertexColor(result[i].getID(), "green");
    }
    gv.setVertexColor(result[0].getID(), "red");

    for(unsigned int i = 0;i<deliveryClients.size();i++){
        gv.setVertexColor(deliveryClients[i].getId(), "red");
    }

    gv.setVertexColor(result[0].getID(),"black");
    gv.setVertexLabel(result[0].getID(),"origin");

    system("pause");

    return 0;
}

int case4(Company c, Graph<Point> graph, GraphViewer gv){
    //make restaurant vector and client vector only have unique values
    vector<Restaurant> r = c.getTotalDeliveryRestaurants();
    sort(r.begin(),r.end());
    for(unsigned int i=0; i< r.size()-1;i++){
        if(r[i+1].getId() == r[i].getId()){
            r.erase(r.begin()+i);
            i--;
        }
    }
    for(unsigned int i=0;i<r.size();i++){
        if(!graph.findVertex(r[i].getId())->getVisited()){
            cout << "Restaurante com ID " << r[i].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
            return -3;
        }
    }
    c.setTotalDeliveryRestaurants(r);

    vector<Client> cli = c.getClients();
    sort(cli.begin(),cli.end());
    for(unsigned int j=0;j<cli.size()-1;j++){
        if(cli[j+1].getId() == cli[j].getId()){
            cli.erase(cli.begin()+j);
            j--;
        }
    }
    for(unsigned int i=0;i<cli.size();i++){
        if(!graph.findVertex(cli[i].getId())->getVisited()){
            cout << "Cliente com ID " << cli[i].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
            return -3;
        }
    }
    c.setClients(cli);


    cout << "A calcular rota, um momento por favor..." << endl;

    vector<Point> temp_result, result;
    double dist= 0;
    int min_distance = 999999999;
    int smallest_distance_index = 0, temp_distance_index=0;


    //goes to all restaurants first
    while(c.getTotalDeliveryRestaurants().size() != 1) {


        for (unsigned int i = 0; i < c.getTotalDeliveryRestaurants().size(); i++) {
            if(smallest_distance_index == i) continue;

            graph.Astar(c.getTotalDeliveryRestaurants()[smallest_distance_index].getId(),c.getTotalDeliveryRestaurants()[i].getId());

            if (graph.findVertex(c.getTotalDeliveryRestaurants()[i].getId())->getDist() < min_distance && graph.findVertex(c.getTotalDeliveryRestaurants()[i].getId())->getVisited()) {
                temp_result = graph.getPath(c.getTotalDeliveryRestaurants()[smallest_distance_index].getId(),
                                            c.getTotalDeliveryRestaurants()[i].getId());
                temp_distance_index = i;
                min_distance = graph.findVertex(c.getTotalDeliveryRestaurants()[i].getId())->getDist();

            }

        }
        if(smallest_distance_index<temp_distance_index){
            temp_distance_index--;
        }
        vector<Restaurant> r = c.getTotalDeliveryRestaurants();
        r.erase(r.begin()+smallest_distance_index);
        c.setTotalDeliveryRestaurants(r);

        smallest_distance_index = temp_distance_index;
        dist += min_distance;
        min_distance=999999999;

        result.insert(result.end(),temp_result.begin(),temp_result.end());

    }

    //then goes to all clients ( first to nearest client, then to the others)
    min_distance=999999999;
    int last_restaurant_index = 0;


    for(unsigned int i=0;i<c.getClients().size();i++){
        graph.Astar(c.getTotalDeliveryRestaurants()[last_restaurant_index].getId(),c.getClients()[i].getId());

        if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance) {
            temp_result = graph.getPath(c.getTotalDeliveryRestaurants()[last_restaurant_index].getId(),
                                        c.getClients()[i].getId());
            smallest_distance_index = i;
            min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
        }
    }

    dist += min_distance;
    result.insert(result.end(),temp_result.begin(),temp_result.end());

    min_distance = 99999999;

    //percorrer restantes clientes
    while(c.getClients().size()!=1) {

        for (unsigned int i = 0; i < c.getClients().size(); i++) {
            if(smallest_distance_index == i)continue;

            graph.Astar(c.getClients()[smallest_distance_index].getId(),c.getTotalDeliveryRestaurants()[i].getId());

            if (graph.findVertex(c.getClients()[i].getId())->getDist() < min_distance && graph.findVertex(c.getClients()[i].getId())->getVisited()) {
                temp_result = graph.getPath(c.getClients()[smallest_distance_index].getId(),
                                            c.getClients()[i].getId());
                temp_distance_index = i;
                min_distance = graph.findVertex(c.getClients()[i].getId())->getDist();
            }

        }


        if(smallest_distance_index<temp_distance_index){
            temp_distance_index--;
        }

        vector<Client> cli = c.getClients();
        cli.erase(cli.begin()+smallest_distance_index);
        c.setClients(cli);

        smallest_distance_index = temp_distance_index;

        dist += min_distance;
        min_distance=999999999;

        result.insert(result.end(),temp_result.begin(),temp_result.end());

    }

    int esp=0;
    for(int i=0;i<c.getDeliveries().size();i++){
        esp+=c.getDeliveries()[i].calculateOccupiedSpace();
    }

    Deliverer d=c.decideDeliverer(dist,esp);
    cout<<"O estafeta encarregado da sua entrega e: "<<d.getID()<<endl;
    cout<<"O tempo estimado para a sua entrega e "<<int(((dist/1000)/d.getvMed())*60)+1<<" minutos"<<endl;


    for(int i=0;i<result.size();i++){
        gv.setVertexColor(result[i].getID(), "green");
    }

    for(unsigned int i=0;i<r.size();i++){
        gv.setVertexColor(r[i].getId(), "red");
    }

    for(unsigned int i=0;i<cli.size();i++){
        gv.setVertexColor(cli[i].getId(), "red");
    }

    gv.setVertexColor(result[0].getID(),"black");
    gv.setVertexLabel(result[0].getID(),"origin");

    system("pause");

    return 0;
}

int case5(Company c, Graph<Point> graph, GraphViewer gv){

    for(int i = 0; i<c.getClients().size();i++) {
        if (!graph.findVertex(c.getClients()[i].getId())->getVisited()) {
            cout << "Cliente com ID " << c.getClients()[i].getId()
                 << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID." << endl;
            return -3;
        }
    }

    for(int i =0; i<c.getTotalDeliveryRestaurants().size();i++) {
        if (!graph.findVertex(c.getTotalDeliveryRestaurants()[i].getId())->getVisited()) {
            cout << "Restaurante com ID " << c.getTotalDeliveryRestaurants()[i].getId()
                 << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID." << endl;
            return -3;
        }
    }



    cout << "A calcular rota, um momento por favor..." << endl;


    for(int j = 0; j< c.getDeliveries().size();j++) {
        vector<Point> perfectPath;

        cout << "Rota da entrega numero " << j+1 << " para o cliente " << c.getDeliveries()[j].getClient().getId() << endl;

        graph.dijkstraShortestPath(c.getDeliveries()[j].getRestaurant()[0].getId());
        perfectPath = graph.getPath(c.getDeliveries()[j].getRestaurant()[0].getId(),
                                    c.getDeliveries()[j].getClient().getId());

        for (int i = 0; i < perfectPath.size(); i++) {
            gv.setVertexColor(perfectPath[i].getID(), "green");
        }

        gv.setVertexColor(perfectPath[perfectPath.size() - 1].getID(), "red");

        gv.setVertexColor(perfectPath[0].getID(), "black");
        gv.setVertexLabel(perfectPath[0].getID(), "origin");

        while(!c.getDeliverers().empty()) {
            double dist = graph.findVertex(perfectPath[perfectPath.size() - 1].getID())->getDist();
            Deliverer d = c.decideDeliverer(dist, c.getDeliveries()[j].calculateOccupiedSpace());
            cout << "O estafeta encarregado da sua entrega e: " << d.getID() << endl;
            cout << "O tempo estimado para a sua entrega e " << int(((dist / 1000) / d.getvMed()) * 60) + 1
                 << " minutos"
                 << endl;

            //eliminar estafeta do vetor
            vector <Deliverer> copy = c.getDeliverers();
            for(unsigned int k = 0;k<copy.size();k++){
                if(d.getID() == copy[k].getID()){
                    copy.erase(copy.begin()+k);
                    break;
                }
            }
            c.setDeliverers(copy);
            break;
        }
        if(c.getDeliverers().empty()){
            cout << "Nao ha nenhum estafeta livre para a sua entrega mas assim que houver um livre ele ira percorrer o seguinte caminho: " << endl;
        }

        system("pause"); //wait for input to display next path

        //clear gv
        for (int i = 0; i < perfectPath.size(); i++) {
            gv.setVertexColor(perfectPath[i].getID(), "orange");
        }
        gv.setVertexLabel(perfectPath[0].getID(),"");
        gv.setVertexColor(perfectPath[perfectPath.size()-1].getID(),"cyan");

    }
    return 0;
}

int case6(Company c, Graph<Point> graph, GraphViewer gv){

    for(int j = 0; j< c.getDeliveries().size();j++) {
        vector<Point> temp_result, result;

        vector<Restaurant> deliveryRestaurants = c.getDeliveries()[j].getRestaurant();
        double dist= 0;
        int min_distance = 999999999;
        int smallest_distance_index = 0;

        for(unsigned int i=0;i<deliveryRestaurants.size();i++){
            if(!graph.findVertex(deliveryRestaurants[i].getId())->getVisited()){
                cout << "Restaurante com ID " << deliveryRestaurants[i].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
                return -3;
            }
        }
        if(!graph.findVertex(c.getClients()[j].getId())->getVisited()){
            cout << "Cliente com ID " << c.getClients()[j].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
            return -3;
        }

        cout << "A calcular rota, um momento por favor..." << endl;


        cout << "Rota da entrega numero " << j+1 << " para o cliente " << c.getDeliveries()[j].getClient().getId() << endl;

        for (int i = 0; i < c.getDeliveries()[j].getRestaurant().size(); i++) {
            graph.Astar(c.getClients()[j].getId(), c.getDeliveries()[j].getRestaurant()[i].getId());

            if (graph.findVertex(c.getDeliveries()[j].getRestaurant()[i].getId())->getDist() < min_distance) {
                temp_result = graph.getPath(c.getClients()[j].getId(), c.getDeliveries()[j].getRestaurant()[i].getId());
                smallest_distance_index = i;
                min_distance = graph.findVertex(c.getDeliveries()[j].getRestaurant()[i].getId())->getDist();
            }
        }

        result.insert(result.end(), temp_result.begin(),
                      temp_result.end());     //caminho mais rápido da casa do cliente ao primeiro restaurante


        dist += min_distance;
        min_distance = 999999999;   //reset min_distance

        int smallest_restaurant_distance = 0;
        //percorrer restantes restaurantes e ver caminho mais rápido entre cada um deles; adicionar ao resultado final até terem sido visitados todos os restaurantes
        while (c.getDeliveries()[j].getRestaurant().size() != 1) {

            min_distance = 999999999;


            for (int i = 0; i < c.getDeliveries()[j].getRestaurant().size(); i++) {
                if (i == smallest_distance_index) continue;

                graph.Astar(c.getDeliveries()[j].getRestaurant()[smallest_distance_index].getId(),
                            c.getDeliveries()[j].getRestaurant()[i].getId());

                if (graph.findVertex(c.getDeliveries()[j].getRestaurant()[i].getId())->getDist() < min_distance) {
                    temp_result = graph.getPath(c.getDeliveries()[j].getRestaurant()[smallest_distance_index].getId(),
                                                c.getDeliveries()[j].getRestaurant()[i].getId());
                    smallest_restaurant_distance = i;
                    min_distance = graph.findVertex(c.getDeliveries()[j].getRestaurant()[i].getId())->getDist();
                }
            }

            if (smallest_restaurant_distance > smallest_distance_index) {
                smallest_restaurant_distance--;
            }

            dist += min_distance;
            result.insert(result.end(), temp_result.begin(), temp_result.end());
            vector<Restaurant> r = c.getDeliveries()[j].getRestaurant();
            r.erase(r.begin() + smallest_distance_index);
            vector<Delivery> d = c.getDeliveries();
            d[j].setRestaurant(r);
            c.setDeliveries(d);
            smallest_distance_index = smallest_restaurant_distance;

        }

        while(!c.getDeliverers().empty()) {
            Deliverer d = c.decideDeliverer(dist, c.getDeliveries()[j].calculateOccupiedSpace());
            cout << "O estafeta encarregado da sua entrega e: " << d.getID() << endl;
            cout << "O tempo estimado para a sua entrega e " << int(((dist / 1000) / d.getvMed()) * 60) + 1
                 << " minutos"
                 << endl;

            //eliminar estafeta do vetor
            vector <Deliverer> copy = c.getDeliverers();
            for(unsigned int k = 0;k<copy.size();k++){
                if(d.getID() == copy[k].getID()){
                    copy.erase(copy.begin()+k);
                    break;
                }
            }
            c.setDeliverers(copy);
            break;
        }
        if(c.getDeliverers().empty()){
            cout << "Nao ha nenhum estafeta livre para a sua entrega mas assim que houver um livre ele ira percorrer o seguinte caminho: " << endl;
        }

        for (int i = 0; i < result.size(); i++) {
            gv.setVertexColor(result[i].getID(), "green");
        }
        gv.setVertexColor(result[0].getID(), "red");

        for (unsigned int i = 0; i < deliveryRestaurants.size(); i++) {
            gv.setVertexColor(deliveryRestaurants[i].getId(), "red");
        }

        gv.setVertexColor(result[result.size() - 1].getID(), "black");
        gv.setVertexLabel(result[result.size() - 1].getID(), "origin");

        system("pause");

        //reset gv
        for (int i = 0; i < result.size(); i++) {
            gv.setVertexColor(result[i].getID(), "orange");
        }
        gv.setVertexLabel(result[result.size()-1].getID(),"");

        for (unsigned int i = 0; i < deliveryRestaurants.size(); i++) {
            gv.setVertexColor(deliveryRestaurants[i].getId(), "cyan");
        }

        result.clear();

    }
    return 0;
}

int case7(Company c, Graph<Point> graph, GraphViewer gv){

    vector<Client> deliveryClients = c.getClients();
    double dist = 0;
    int min_distance = 999999999;
    int smallest_distance_index = 0;

    for (unsigned int i = 0; i < deliveryClients.size(); i++) {
        if (!graph.findVertex(deliveryClients[i].getId())->getVisited()) {
            cout << "Cliente com ID " << deliveryClients[i].getId()
                 << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID." << endl;
            return -3;
        }
    }

    //make restaurants only have unique values
    vector<Restaurant> r = c.getTotalDeliveryRestaurants();
    sort(r.begin(),r.end());
    for(unsigned int i=0; i< r.size()-1;i++){
        if(r[i+1].getId() == r[i].getId()){
            r.erase(r.begin()+i);
            i--;
        }
    }
    for(unsigned int i=0;i<r.size();i++){
        if(!graph.findVertex(r[i].getId())->getVisited()){
            cout << "Restaurante com ID " << r[i].getId() << " nao e alcancavel. Nao pode chegar ao destino, tente outro ID."<<endl;
            return -3;
        }
    }
    c.setTotalDeliveryRestaurants(r);


    for(int j = 0; j< c.getTotalDeliveryRestaurants().size();j++) {

        vector<Point> temp_result, result;

        cout << "A calcular rota, um momento por favor..." << endl;

        cout << "Rota da entrega numero " << j+1 << " com origem no restaurante " << c.getTotalDeliveryRestaurants()[j].getId() << endl;

        //find all clients that ordered from that restaurant
        vector<Client> pathClients;
        for(unsigned int k=0;k<c.getDeliveries().size();k++){
            if(c.getTotalDeliveryRestaurants()[j].getId() == c.getDeliveries()[k].getRestaurant()[0].getId()){
                pathClients.push_back(c.getDeliveries()[k].getClient());
            }
        }

        deliveryClients = pathClients;

        for (int i = 0; i < pathClients.size(); i++) {
            graph.Astar(c.getTotalDeliveryRestaurants()[j].getId(), pathClients[i].getId());
            if (graph.findVertex(pathClients[i].getId())->getDist() < min_distance) {
                temp_result = graph.getPath(c.getTotalDeliveryRestaurants()[j].getId(), pathClients[i].getId());
                smallest_distance_index = i;
                min_distance = graph.findVertex(pathClients[i].getId())->getDist();
            }
        }
        dist += min_distance;
        result.insert(result.end(), temp_result.begin(), temp_result.end());


        min_distance = 999999999;   //reset min_distance

        int smallest_client_distance = 0;

        while (pathClients.size() != 1) {

            min_distance = 999999999;


            for (int i = 0; i < pathClients.size(); i++) {
                if (i == smallest_distance_index) continue;

                graph.Astar(pathClients[smallest_distance_index].getId(), pathClients[i].getId());

                if (graph.findVertex(pathClients[i].getId())->getDist() < min_distance) {
                    temp_result = graph.getPath(pathClients[smallest_distance_index].getId(),
                                                pathClients[i].getId());
                    smallest_client_distance = i;
                    min_distance = graph.findVertex(pathClients[i].getId())->getDist();
                }
            }

            if (smallest_client_distance > smallest_distance_index) {
                smallest_client_distance--;
            }

            dist += min_distance;
            result.insert(result.end(), temp_result.begin(), temp_result.end());

            pathClients.erase(pathClients.begin() + smallest_distance_index);

            smallest_distance_index = smallest_client_distance;

        }

        while(!c.getDeliverers().empty()) {
            int esp=0;

            for(unsigned int n; n<c.getDeliveries().size();n++){
                if(c.getDeliveries()[n].getRestaurant()[0].getId() == c.getTotalDeliveryRestaurants()[j].getId()){
                    esp+=c.getDeliveries()[n].calculateOccupiedSpace();
                }
            }

            Deliverer d = c.decideDeliverer(dist, esp);
            cout << "O estafeta encarregado da sua entrega e: " << d.getID() << endl;
            cout << "O tempo estimado para a sua entrega e " << int(((dist / 1000) / d.getvMed()) * 60) + 1
                 << " minutos"
                 << endl;

            //eliminar estafeta do vetor
            vector <Deliverer> copy = c.getDeliverers();
            for(unsigned int k = 0;k<copy.size();k++){
                if(d.getID() == copy[k].getID()){
                    copy.erase(copy.begin()+k);
                    break;
                }
            }
            c.setDeliverers(copy);
            break;
        }
        if(c.getDeliverers().empty()){
            cout << "Nao ha nenhum estafeta livre para a sua entrega mas assim que houver um livre ele ira percorrer o seguinte caminho: " << endl;
        }



        for (int i = 0; i < result.size(); i++) {
            gv.setVertexColor(result[i].getID(), "green");
        }
        gv.setVertexColor(result[0].getID(), "red");

        for (unsigned int i = 0; i < deliveryClients.size(); i++) {
            gv.setVertexColor(deliveryClients[i].getId(), "red");
        }

        gv.setVertexColor(result[0].getID(), "black");
        gv.setVertexLabel(result[0].getID(), "origin");


        system("pause");


        //reset gv
        for (int i = 0; i < result.size(); i++) {
            gv.setVertexColor(result[i].getID(), "orange");
        }
        gv.setVertexLabel(c.getTotalDeliveryRestaurants()[j].getId(),"");
        gv.setVertexColor(c.getTotalDeliveryRestaurants()[j].getId(), "cyan");

    }

    return 0;
}