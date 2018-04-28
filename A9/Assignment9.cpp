#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.hpp"
using namespace std;

Graph::Graph() {
    
}

Graph::~Graph() {
    
}

void Graph::assignDistricts(){
        int numID = 1;
        for(int i = 0;i<vertices.size();i++){
                if(vertices[i].districtID == -1){
                        DFSLabel(vertices[i].name, numID);
                        numID++;
                }

        }
}

vertex* Graph::findVertex(string name) {
        int i = 0;
        while (i<vertices.size()) {
                if (vertices[i].name == name) {
                        return &vertices[i];
                }
                i++;
        }
        return nullptr;
}


void Graph::DFSLabel(string startCity, int distID){
        stack<vertex*> q;
        q.push(findVertex(startCity));
        vertex * node = q.top();
        while(!q.empty()){
                node = q.top();
                node->visited = true;
                q.pop();
                if(node->adj.size() == 0){
                        node -> districtID = distID;
                }for(int i = 0; i < node->adj.size(); i++){
                        if(node -> adj[i].v->visited == false){
                                q.push(node->adj[i].v);
                                node -> adj[i].v -> visited = true;
                                node -> districtID = distID;
                                node -> adj[i].v -> districtID = distID;
                        }
                }
        }
}

void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == name){
            found = true;
        }
    }
    if(found == false){
        vertex v;
        v.name = name;
        v.districtID = -1;
        vertices.push_back(v);

    }
}

void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i].districtID << ":"<<vertices[i].name << "-->"; 
        for(int j=0;j<vertices[i].adj.size();j++){
            cout << vertices[i].adj[j].v->name;             
            if (j != vertices[i].adj.size()-1)cout<<"***"; 
        }
        cout << endl;
    }
}

void Graph::shortestPath(string startCity, string endCity)
{
    vertex *start = findVertex(startCity);
    vertex *end = findVertex(endCity);
    if(start == NULL || end == NULL){
        cout << "One or more cities doesn't exist" << endl;
    }else if(start -> districtID != end -> districtID){
        cout << "No safe path between cities" << endl;
    }else{
        for(int i = 0; i < vertices.size(); i++){
            vertices[i].visited = false;
            vertices[i].parent = NULL;
            if(vertices[i].districtID == start -> districtID){
                vertices[i].unweightedDistance = 0;
            }else{
                vertices[i].unweightedDistance = INT_MAX;
            }
        }
        queue <vertex*> q;
        vertex * node;
        q.push(start);

        while(!q.empty()){
            node = q.front();
            q.pop();
            node->visited = true;
            for(int i = 0; i < node -> adj.size(); i++){
                if(node->adj[i].v->visited == false){
                    if(node->adj[i].v -> name == endCity){
                        node -> adj[i].v -> visited = true;
                        node -> adj[i].v -> unweightedDistance = node -> unweightedDistance + 1;
                        q.push(node -> adj[i].v);
                        node -> adj[i].v -> parent = node;
                        end = node -> adj[i].v;
                    }else{
                        node->adj[i].v->visited = true;
                        node->adj[i].v->unweightedDistance = node->unweightedDistance + 1;
                        q.push(node->adj[i].v);
                        node->adj[i].v->parent = node;
                    }
                }
            }
        }
        node = end;
        vector <vertex*> path;
        while(node->name != startCity){
            path.push_back(node);
            node = node->parent;
        }
        path.push_back(node);

        cout << end->unweightedDistance << ", ";
        for(int i = path.size()-1; i > 0; i--){
            cout << path[i] -> name << ", ";
        }
        cout << path[0]->name << endl;
    }
}

void Graph::shortestWeightedPath(string startCity, string endCity){
    vertex *start = findVertex(startCity);
    vertex *end = findVertex(endCity);
    if(start == NULL || end == NULL){
        cout << "One or more cities doesn't exist" << endl;
    }
    else if(start -> districtID == -1 || end -> districtID == -1){
        cout << "Please identify the districts before checking distances" << endl;
    }
    else if(start -> districtID != end -> districtID){
        cout << "No safe path between cities" << endl;
    }
    else{
        for(int i = 0; i < vertices.size(); i++){
            vertices[i].parent = NULL;
            vertices[i].visited = false;
            if(vertices[i].districtID == start->districtID){
                vertices[i].weightedDistance = 0;
            }
            else{
                vertices[i].weightedDistance = INT_MAX;
            }
        }
        start->visited = true;
        vector <vertex*> found = {start};
        int minDistance;
        vertex * first;
        vertex * second;
        while(!end->visited){
            minDistance = INT_MAX;
            vertex * node = NULL;
            for(int i=0;i<found.size();i++){
                vertex *first = found[i];
                for(int j=0;j<first->adj.size();j++){
                    if(first->adj[j].v->visited == false){
                        int dist = first->weightedDistance + first->adj[j].weight;
                        //resetting when needed
                        if(dist<minDistance){
                            node = first->adj[j].v;
                            minDistance = dist;
                            second = first;
                        }
                    }
                }
            }
            node->weightedDistance = minDistance;
            node->parent = second;
            node -> visited = true;
            found.push_back(node);
        }
        vertex * node = end;
        vector <vertex*> path;
        while(node->name != startCity){
            path.push_back(node);
            node = node->parent;
        }
        path.push_back(node);
        cout << end->weightedDistance << ", ";
        for(int i=path.size()-1; i>0; i--){
            cout << path[i]->name << ", ";
        }
        cout << path[0]->name << endl;
    }
}

void printmenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Find districts" << endl;
    cout << "3. Find shortest path" << endl;
    cout << "4. Find shortest weighted path" << endl;
    cout << "5. Quit" << endl; 

}

int main(int argc, char const *argv[]){
    string startCity, endCity, wstartCity, wendCity;
    Graph ex;
    int inputorder = 0;
    
    ifstream myfile;
    myfile.open(argv[1]);
    
    string line;
    vector<string> cityname;
    getline(myfile, line);
    stringstream ss(line);  
    string ignore;
    getline(ss, ignore, ',');
    string name;
    while (getline(ss, name, ',')){
        cityname.push_back(name);
        ex.addVertex(name);
    }
    while(getline(myfile, line)){
        stringstream ss(line);
        string word; 
        getline(ss, word, ','); 
        string word1;
        int counter = 0;   
        while(getline(ss, word1, ',')){
            string comp = cityname[counter];    
            int w = stoi(word1); 
            if ((w != 0) && (w != -1)){
                ex.addEdge(word, comp, w);
            }
            counter ++;
        }
    }
    myfile.close();

    while (inputorder != 5){
        cin >> inputorder;
        printmenu();
        if (inputorder == 1){
            ex.displayEdges();
        }
        else if (inputorder == 2){
            ex.assignDistricts();
        }
        else if (inputorder == 3){
            cout << "Enter a starting city:" << endl;
            cin.ignore();
    		getline(cin,startCity);
            cout << "Enter an ending city:" << endl;
    		getline(cin,endCity);
            ex.shortestPath(startCity, endCity);
        }
        else if (inputorder == 4){
            cout << "Enter a starting city:" << endl;
            cin.ignore();
    		getline(cin,wstartCity);
            cout << "Enter an ending city:" << endl;
    		getline(cin,wendCity);
            ex.shortestWeightedPath(wstartCity, wendCity);
        }
        else if (inputorder == 5){
            break;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
