#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.h"
using namespace std;


Graph::Graph(){
    
}

Graph::~Graph(){
    
}

void Graph::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(j+1!=vertices[i].adj.size()){
                cout<<vertices[i].adj[j].v->name<<"***";
            }
            else{
                cout<<vertices[i].adj[j].v->name;
            }
        }
        cout<<endl;
    }
}

void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" already in the graph."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::addEdge(string first, string second, int distance){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == first){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == second && i != j){
                    adjVertex ex;
                    ex.v = &vertices[j];
                    ex.weight = distance;
                    vertices[i].adj.push_back(ex);
                }
            }
        }
    }
}

int Graph::isAdjacent(string first, string second){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == first){
            for(int j = 0; j < vertices[i].adj.size(); j++){
                if(vertices[i].adj[j].v->name == second){
                    return 1;
                }
            }
        }
    }
    return 0;
}


int main(int argc, char const *argv[]){
    
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

    while (inputorder != 3){
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Vertex adjacent" << endl;
        cout << "3. Quit" << endl;
        cin >> inputorder;
        if (inputorder == 1){
            ex.displayEdges();
        }
        else if (inputorder == 2){
            string city1;
            string city2;
            cout << "Enter first city:" << endl;
            cin >> city1;
            cout << "Enter second city:" << endl;
            cin >> city2;
            int adjacency = ex.isAdjacent(city1, city2);
            if (adjacency == 1){
                cout << "True" << endl;
            }
            else if (adjacency == 0){
                cout << "False" << endl;
            }
        }
        else if (inputorder == 3){
            break;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
