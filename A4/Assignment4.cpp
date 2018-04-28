#include "CommunicationNetwork.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

CommunicationNetwork::CommunicationNetwork(){
	
}
CommunicationNetwork::~CommunicationNetwork(){
    head = NULL;
    tail = NULL;
    deleteNetwork();
}

City * createNode(string nodeID, City* nodePrev, City* nodeNext) {
	City* newCity = new City(nodeID,nodeNext,nodePrev,"");
	return newCity;
}

void CommunicationNetwork::addCity(string newCity, string previousCity){
	City * ex = head;
	if(head == NULL){
		head = createNode(newCity,NULL,NULL);
		tail = head;
	}
	else if(previousCity=="First"){
		head = createNode(newCity,NULL,ex);;
		ex->previous = head;
	}
	else if(previousCity==""){
		ex = tail;
		City * city10 = createNode(newCity,ex,NULL);
		tail = city10;
		ex->next = city10;
	}
	else{
		while(ex != nullptr){
			if(ex->cityName==previousCity){
				City * city10 = createNode(newCity,ex,ex->next);
				ex->next = city10;
				ex->next->previous = city10;
				break;
			}
			ex = ex -> next;
		}
	}  
}

void CommunicationNetwork::transmitMsg(char *filename){
/*Open the file and transmit the message between all cities in the network word by word. A word needs to be received at the 
end of the network before sending the next word. Only one City can hold the message at a time; as soon as it is passed to 
the next City, it needs to be deleted from the sender City. 
*/
	City * temp;
	temp = head;
	string sentence;
	string newsplit;
	ifstream myfile(filename);
	if(myfile.is_open()){
		while(getline(myfile, sentence)){
			stringstream ss1;
			ss1<<sentence;
			while(ss1>>sentence){
			    while(temp!=NULL){
			        temp->message = sentence;
			    	cout << temp->cityName << " received " << temp->message << endl;
			    	temp = temp -> next;
			    }
			    temp = tail->previous;

			    while(temp!=NULL){
			        temp->message = sentence;
			    	cout << temp->cityName << " received " << temp->message << endl;
			    	temp = temp -> previous;
			    }
			    temp = head;

			}
		}
	}
}

void CommunicationNetwork::printNetwork(){	
	City * ex = head;
	cout << "===CURRENT PATH===" <<endl;
	cout << "NULL <- ";
	while(ex != nullptr){
		cout << ex->cityName;
		ex = ex -> next;
		if(ex == nullptr){
			cout << " -> NULL"<<endl;
			cout << "==================";
			break;
		}
		else{
		    cout <<" <-> ";
		}
	}
}

City * createNode(string nodeID, City* nodePrev, City* nodeNext) {
	City* newCity = new City(nodeID,nodeNext,nodePrev,"");
	return newCity;
}

void CommunicationNetwork::buildNetwork(){
/*Build the initial network from the cities given in this writeup. The cities can be fixed in the function, 
you do not need to write the function to work with any list of cities. */
	head = createNode("Los Angeles",NULL,NULL);
	tail = head;
	City * city1 = createNode("Phoenix",tail,NULL);
	tail->next = city1;
	tail = city1;
	City * city2 = createNode("Denver",tail,NULL);
	tail->next = city2;
	tail = city2;
	City * city3 = createNode("Dallas",tail,NULL);
	tail->next = city3;
	tail = city3;
	City * city4 = createNode("St. Louis",tail,NULL);
	tail->next = city4;
	tail = city4;
	City * city5 = createNode("Chicago",tail,NULL);
	tail->next = city5;
	tail = city5;
		City * city6 = createNode("Atlanta",tail,NULL);
	tail->next = city6;
	tail = city6;
		City * city7 = createNode("Washington, D.C.",tail,NULL);
	tail->next = city7;
	tail = city7;
		City * city8 = createNode("New York",tail,NULL);
	tail->next = city8;
	tail = city8;
		City * city9 = createNode("Boston",tail,NULL);
	tail->next = city9;
	tail = city9;
}

void CommunicationNetwork::deleteCity(string input){
	City * ex = head;
	int count = 0;
	while(ex != nullptr){
		if(input==head->cityName){
			ex->next->previous = NULL;
			head = ex->next;
			delete ex;
			count =1;
			break;
		}
		else if(input==tail->cityName){
			ex = tail;
			ex->previous->next = NULL;
			tail = ex->previous;
			delete ex;
			count = 1;
			break;
		}
		else if(ex->cityName==input){
			ex->previous->next = ex->next;
			ex->next->previous = ex->previous;
			count = 1;
		}
		ex = ex -> next;
	}
	if(count != 1){
		cout<<input<<" not found"<<endl;
	}
}

void CommunicationNetwork::deleteNetwork(){
	City * ex = head;
	while(ex != nullptr){
		if(ex->cityName==tail->cityName){

			//ex->previous->next = NULL;
			//head = ex->next;
			cout<<"deleting " << ex->cityName<<endl;
			delete ex;
			tail = NULL;
			head = NULL;
			tail = head;
			break;
		}
		ex->next->previous = NULL;
		head = ex->next;
		cout<<"deleting " << ex->cityName<<endl;
		delete ex;
		ex = ex -> next;
	}
}

void menu(){
	cout <<"======Main Menu======"<<endl;
	cout <<"1. Build Network"<<endl;
	cout <<"2. Print Network Path"<<endl;
	cout <<"3. Transmit Message Coast-To-Coast-To-Coast"<<endl;
	cout <<"4. Add City"<<endl;
	cout <<"5. Delete City"<<endl;
	cout <<"6. Clear Network"<<endl;
	cout <<"7. Quit"<<endl;
}

City * createNode(string nodeID, City* nodePrev, City* nodeNext) {
	City* newCity = new City(nodeID,nodeNext,nodePrev,"");
	return newCity;
}

void inputs(char * file){
	CommunicationNetwork lister;
	int in = 0;

	while(in!=7){
	    menu();
		cin >> in;
		if(in == 1){
			lister.buildNetwork();
			lister.printNetwork();
		}
		else if(in == 2){
			lister.printNetwork();
		}
		else if(in == 3){
		    lister.transmitMsg(file);
		}
		else if(in == 4){
			string cityNewName;
			string cityPreviousName;
			cout << "Enter a city name: " << endl;
			cin>>cityNewName;
			cout << "Enter a previous city name: " << endl;
			cin>>cityPreviousName;
			lister.addCity(cityNewName,cityPreviousName);
		}
		else if(in == 5){
			string name;
			cout << "Enter a city name:"<<endl;
			cin>>name;
			lister.deleteCity(name);
		}
		else if(in == 6){
			lister.deleteNetwork();
		}
		else if(in == 7){
			cout << "Goodbye!"<<endl;
			break;
		}
	}
}
int main(int argc, char * argv[]){
	inputs(argv[1]);
	return 0;
}
