#include <iostream>
#include <fstream> //file stream
#include <sstream> //string stream
using namespace std;

struct city{
    std::string cityName;
    std::string message;
    city *next;
    city(){}; // default constructor
    city(std::string initName, city *initNext, std::string initMessage)
    {
        cityName = initName;
        next = initNext;
        message = initMessage;
    }
};

void menu(){
	cout <<"======Main Menu======"<<endl;
	cout <<"1. Build Network"<<endl;
	cout <<"2. Print Network Path"<<endl;
	cout <<"3. Transmit Message Coast-To-Coast"<<endl;
	cout <<"4. Add City"<<endl;
	cout <<"5. Quit"<<endl;
}

city *buildNetwork(){
	city * root;
	city * temp;
	city * Boston = new city("Boston",NULL,"");
	city * NY = new city("New York",Boston,"");
	city * WDC = new city("Washington, D.C.",NY,"");
	city * Atlanta = new city("Atlanta",WDC,"");
	city * Chicago = new city("Chicago",Atlanta,"");
	city * SL = new city("St. Louis",Chicago,"");
	city * Dallas = new city("Dallas",SL,"");
	city * Denver = new city("Denver",Dallas,"");
	city * Phoenix = new city("Phoenix", Denver,"");
	city * LA = new city("Los Angeles",Phoenix,"");
	root = LA;
	temp = root;
}

city *addCity(city *head, city *previous, string cityName){
	if(previous == NULL){
		head = new city(cityName,head,"");
	}
	else if(head == NULL){
		head = new city(cityName,NULL,"");
	}
	else{
    	city * temp;
    	temp = previous;
    	city * nextnode = new city(cityName,previous->next,"");
    	previous->next = nextnode;
    }
    return head;
}

void transmitMsg(city *head){
	city * temp;
	temp = head;
	string sentence;
	string newsplit;
	ifstream myfile("messageIn.txt");
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
			    temp = head;

			}
		}
	}
}
void printPath(city	*head){
	city * temp;
	temp = head;
	cout << "===CURRENT PATH==="<<endl;
	while(temp != NULL){
		cout << temp -> cityName << " -> ";
		temp = temp -> next;
	}
	cout << " "<<"NULL"<<endl;
	cout <<"=================="<<endl;
}

city *find(city	*head, string name){
	city * temp;
	temp = head;
	while(temp != NULL){
		if(temp->cityName == name){
			return temp;
		}
		temp = temp -> next;
	}
	cout << "Error! Wrong name"<<endl;
}

int inputs(){
	int in = 0;
	city * head;
	cin >> in;
	if(in == 1){
		head = buildNetwork();
		menu();
	}
	else if(in == 2){
		printPath(head);
		menu();
	}
	else if(in == 3){
		transmitMsg(head);
		menu();
	}
	else if(in == 4){
		string pcity;
		string ncity;
		cout<<"Enter a City name:"<<endl;
		cin>>ncity;
		cout<<"Enter a previous City name:"<<endl;
		cin>>pcity;
		city * newcity = find(head,pcity);
		addCity(head,newcity,ncity);
		menu();
	}
	else if(in == 5){
		cout<<"Goodbye!"<<endl;
	}
	return in;
}

int main(){
	int i = 0;
	menu();
	while(i!=5){
		i = inputs();
	}
	return 0;
}
