#include "CommunicationNetwork.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

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
