#include <iostream>
#include <sstream>
#include "Queue.h"
using namespace std;

bool flag = false;
Queue::Queue(int qs) {
	queueSize = qs;
	arrayQueue = new string[queueSize];
	queueHead = 0;
	queueTail = 0;
	queueCount = 0;
}
Queue::~Queue() {
	delete [] arrayQueue;
	arrayQueue = nullptr;
}

bool Queue::queueIsEmpty(){
	if(queueTail == -1 and queueHead == -1 or queueCount == 0){
		return true;
	}
	else{
		return false;
	}
}
void Queue::dequeue(){
	string word;
	word = arrayQueue[queueHead];
	if(queueIsEmpty()){
		cout << "Queue is empty" << endl; 
	}
	else{
	    queueCount--;
	    //cout <<queueCount<<endl;
		if(queueHead == queueTail and queueCount == 0){
			queueHead = queueTail = -1;
		}
		else{
			queueHead++;
			if(queueHead == queueSize){
				queueHead = 0;
			}
			cout<<"H: "<<queueHead<<endl;
    		cout<<"T: "<<queueTail<<endl;
    		cout<<"word: "<<word<<endl;
		}
	}
}

bool Queue::queueIsFull(){
	int ex = queueHead;
	if(queueHead==0){
		ex = queueSize;
	}
	if(ex-queueTail==1){
		return true;
	}
	else{
		return false;
	}
}
void Queue::enqueue(string word){
	//prompt the user
	//cout<<"word: ";
    if(flag == true){
        cout<<"Queue is full"<<endl;
        flag = false;
    }
    else if(queueTail == queueSize and queueHead>0){
        queueTail = 0;
        arrayQueue[queueTail] = word;
        queueTail++;
        queueCount++;
        cout<<"E: "<<word<<endl;
		cout<<"H: "<<queueHead<<endl;
		cout<<"T: "<<queueTail<<endl;
        
    }
	else if(!queueIsFull()){
		arrayQueue[queueTail] = word;
		queueTail++;
		queueCount++;
		if(queueTail == queueSize and queueHead>0){
		    queueTail = 0;
		}
		cout<<"E: "<<word<<endl;
		cout<<"H: "<<queueHead<<endl;
		cout<<"T: "<<queueTail<<endl;
	}
	else{
		arrayQueue[queueTail] = word;
		
		queueCount++;
		if(queueHead == 0){
		    queueTail = 0;
		}
		else{
		    queueTail++;
		}
		cout<<"E: "<<word<<endl;
		cout<<"H: "<<queueHead<<endl;
		cout<<"T: "<<queueTail<<endl;
		flag = true;
	}
}

/*void Queue::printQueue(){
    int i = 0;
    int index =queueHead;
    if(queueCount==0){
        cout<<"Empty"<<endl;
    }
	else { while(queueCount!=i){
	    index = (queueHead+i)%queueSize;
		cout << index <<": "<<arrayQueue[index] <<endl;
		i++;
	}}
}*/
void Queue::printQueue(){
    int i = 0;
    int index =queueHead;
    if(queueCount==0){
        cout<<"Empty"<<endl;
    }
    else{
        int count = 0;
        int count1 = queueHead;
        while(queueCount!=count){
            if(count1 != queueSize){
                cout << count1 <<": "<<arrayQueue[count1] <<endl;
            }
            else{
                count1 = 0;
                cout << count1 <<": "<<arrayQueue[count1] <<endl;
            }
            count++;
            count1++;
        }
    }
}

void Queue::enqueueSentence(string input) {
    stringstream ss;
    ss<<input;
    string input1;
    while(getline(ss,input1,' ')){
        Queue::enqueue(input1);
    }
}

int main(){
	Queue ex(10);
	int input;

	string in;
	string sent;
	string set;
	while(input!=5){
	    cout<<"======Main Menu====="<<endl;
    	cout<<"1. Enqueue word"<<endl;
    	cout<<"2. Dequeue word"<<endl;
    	cout<<"3. Print queue"<<endl;
    	cout<<"4. Enqueue sentence"<<endl;
    	cout<<"5. Quit"<<endl;
		cin>>input;
		if(input==1){
		    cout<<"word: ";
			cin>>in;
			ex.enqueue(in);
		}
		else if(input==2){
			ex.dequeue();
		}
		else if(input==3){
			ex.printQueue();
		}
		else if(input==4){
		    cout<<"sentence: ";
            cin.ignore();
			getline(cin,set);
			ex.enqueueSentence(set);
		}
		else if(input==5){
			cout<<"Goodbye!"<<endl;
			break;
		}
	}
	return 0;
}
