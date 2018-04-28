#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree() {
    root = nullptr;
    // Your code here //
}

MovieTree::~MovieTree() {
    DeleteAll(root);
    // Your code here //
}

MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title){
 	MovieNodeLL * temp = head;
 	if(temp != nullptr){
 		while(temp != nullptr){
 			if(temp->title == title){
 				return temp;
 			}
 			temp = temp->next;
 		}
 		return nullptr;
 	}
 	else
 		return nullptr;
 }
void MovieTree::printMovieInventory(MovieNodeBST * node){
    	if (node != nullptr) {
		if (node->leftChild != nullptr) {
			printMovieInventory(node->leftChild);
		}
		MovieNodeLL * temp = node->head;
		while(temp != nullptr)
		{
			cout<<"Movie: "<<temp->title<<" "<<temp->quantity<<endl;
			temp = temp->next;
		}
		if (node->rightChild != nullptr) {
			printMovieInventory(node->rightChild);
		}
	}
}


MovieNodeBST *insertNodeHelper(MovieNodeBST* curNode, char data, MovieNodeLL* trackll){
	MovieNodeBST * newone;
	if(curNode->letter>data){
	    if (curNode->leftChild != nullptr){
	        return insertNodeHelper(curNode->leftChild,data,trackll);
	    }
	    else{
	        newone = new MovieNodeBST;
	        newone->parent = curNode;
	        newone->letter = data;
	        newone->leftChild = nullptr;
	        newone->rightChild = nullptr;
		    curNode->leftChild=newone;
            newone->head = trackll;
		}
    }
    else if(curNode->letter<data){
    	if (curNode->rightChild != nullptr){
	        return insertNodeHelper(curNode->rightChild,data,trackll);
	    }
	    else{
	        newone = new MovieNodeBST;
	        newone->parent = curNode;
	        newone->letter = data;
	        newone->leftChild = nullptr;
	        newone->rightChild = nullptr;
	    	curNode->rightChild = newone;
            newone->head = trackll;
	    }
    }
    else{
        MovieNodeLL * comparer;
        MovieNodeLL holder;
        trackll->next = curNode->head;
        curNode->head = trackll;
        comparer = trackll;
	    while(comparer->next != nullptr){  
	        if(comparer->title.compare(comparer->next->title)>0){
            	holder = *comparer->next;
                comparer->next->ranking = comparer->ranking;
                comparer->next->title = comparer->title;
                comparer->next->year = comparer->year;
                comparer->next->quantity = comparer->quantity;
                comparer->ranking=holder.ranking;
                comparer->title=holder.title;
                comparer->year=holder.year;
                comparer->quantity=holder.quantity;
            }
            else{
                
            }
            comparer=comparer->next;
        }
    }
    return newone;
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
   
   
    MovieNodeBST * track = nullptr;
    MovieNodeLL * trackll;
    trackll = new MovieNodeLL;
    trackll->ranking = ranking;
	trackll->title = title;
	trackll->year = releaseYear;
	trackll->quantity = quantity;
	trackll->next = nullptr;
	char ptr;
    ptr = title.at(0);
    if(root == nullptr){
    	track = new MovieNodeBST;
    	track->letter = ptr;
    	track->parent = nullptr;
    	track->leftChild = nullptr;
    	track->rightChild = nullptr;
    	track->head = trackll;
    	root = track;
    }
    else{
        insertNodeHelper(root,ptr,trackll);
    }
}

void MovieTree::deleteMovieNode(std::string title) {
    MovieNodeBST * treeloc = searchBST(root,title);
    MovieNodeLL * loc = searchLL(treeloc->head,title);
    if(treeloc == NULL || loc == NULL){
        //cout << "Movie not found." <<endl;
    }
    else{
        loc = treeloc->head;
        if(loc->next == NULL){
            delete loc;
            treeMinimum(treeloc);
        }
        else{
            if(loc->title == title){
                treeloc->head = loc->next;
            }
            else{
                while(loc->next->title!=title){
                    loc=loc->next;
                }
                loc->next = loc->next->next;
            }
        }
    }
}

void MovieTree::DeleteAll(MovieNodeBST * node){
	if (node != nullptr) {
		if (node->leftChild != nullptr) {
			DeleteAll(node->leftChild);
		}
		if (node->rightChild != nullptr) {
			DeleteAll(node->rightChild);
		}
		MovieNodeLL * par = node->head;
		while(par != nullptr)
		{
			cout<<"Deleting: "<<par->title<<endl;
			deleteMovieNode(par->title);
			par = par->next;
		}
	}
}

MovieNodeBST * min(MovieNodeBST * nn){
	if(!nn) return nullptr;
	while(nn->leftChild)
		nn = nn->leftChild;
	return nn;
}

MovieNodeBST * MovieTree::treeMinimum(MovieNodeBST * node) {
    bool isRoot = node==root;
	MovieNodeBST * mn;
	bool isleftChild = isRoot ? false : (node->parent->leftChild==node);
	
	if(!node->leftChild and !node->rightChild){
		if(isleftChild and !isRoot) node->parent->leftChild = nullptr;
		else if(!isleftChild and !isRoot) node->parent->rightChild = nullptr;
		delete node;
		node = nullptr;
	}
	else if(node->rightChild){
		mn = min(node->rightChild);
		node->letter = mn->letter;
		node->head = mn->head;
		treeMinimum(mn);
	}
	else if(node->leftChild){
		if(isleftChild and !isRoot) node->parent->leftChild = node->leftChild;
		else if(!isleftChild and !isRoot) node->parent->rightChild = node->leftChild;
		node->leftChild->parent = node->parent;
		delete node;
	}
	return mn;
}

MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, string value) {
    char* ptr;
    ptr = &value.at(0);
    if(node == NULL)
        return node;
    if(node->letter == *ptr)
        return node;
    if(node->letter > *ptr)
        return searchBST(node->leftChild, value);
    return searchBST (node->rightChild,value);
}

void MovieTree::findMovie(string title) {
    MovieNodeBST * tmp =  searchBST(root,title);
    MovieNodeLL * temp1;
    if(tmp != nullptr)
    temp1 = searchLL(tmp->head,title);
    if(tmp != nullptr && temp1 != nullptr){
    	cout<<"Movie Info:"<<endl;
    	cout<<"==========="<<endl;
    	cout<<"Ranking:"<<temp1->ranking<<endl;
    	cout<<"Title:"<<temp1->title<<endl;
    	cout<<"Year:"<<temp1->year <<endl;
    	cout<<"Quantity:"<<temp1->quantity<<endl;
    }
    else//movie not found
    	cout<<"Movie not found."<<endl;
}

void MovieTree::rentMovie(string title) {
    MovieNodeBST * ex = searchBST(root,title);
    MovieNodeLL * node = searchLL(ex->head,title);
    if(node == nullptr){
        cout<<"Movie not found."<<endl;
    }
    else{
        cout<<"Movie has been rented."<<endl;
    	cout<<"Movie Info:"<<endl;
    	cout<<"==========="<<endl;
    	cout<<"Ranking:"<<node->ranking<<endl;
    	cout<<"Title:"<<node->title<<endl;
    	cout<<"Year:"<<node->year<<endl;
    	cout<<"Quantity:"<<--node->quantity<<endl;
        if(!node->quantity){
            deleteMovieNode(node->title);
        }
    }
}

int counterhelper(MovieNodeBST *node){
    int counter = 0;
    if(node == nullptr){
    	return 0;
    }
	MovieNodeLL * temp = node->head;
	while(temp != nullptr){
		counter++;
		temp = temp->next;
	}
	return counter;
}
void MovieTree::countMovieNodes(MovieNodeBST *node, int *c) {
    if(node != NULL){
		*c = *c+ counterhelper(node) ;
		countMovieNodes(node->rightChild,c);
		countMovieNodes(node->leftChild,c);
	}
	else
		*c += 0;
}
void MovieTree::printMovieInventory(){
    printMovieInventory(root);
}
int MovieTree::countMovieNodes(){
    int count = 0;
	countMovieNodes(root,&count);
	return count;
}

int main(){
	MovieTree ex;
	int input;
	string in;
	string sent;
	string set;
	string sentence;
    int i = 0;
    ifstream myfile;
    myfile.open("Assignment6Movies.txt");								
	if(myfile.is_open()){
		while(getline(myfile, sentence)){
		    stringstream ss1(sentence);
		    string ra,re,qu,ti;
			getline(ss1, ra,',');
			getline(ss1, ti,',');
			getline(ss1, re,',');
			getline(ss1, qu);
			ex.addMovieNode(stoi(ra), ti,stoi(re),stoi(qu));
		}
	}
	while(input!=6){
	    cout<<"======Main Menu======"<<endl;
    	cout<<"1. Find a movie"<<endl;
    	cout<<"2. Rent a movie"<<endl;
    	cout<<"3. Print the inventory"<<endl;
    	cout<<"4. Delete a movie"<<endl;
    	cout<<"5. Count the movies"<<endl;
    	cout<<"6. Quit"<<endl;
		cin>>input;
    	if(input==1){
    	    cout << "Enter title:" << endl;
    	    cin.ignore();
    		getline(cin,set);
    		ex.findMovie(set);
    	}
    	else if(input==2){
    	    cout << "Enter title:" << endl;
    	    cin.ignore();
    		getline(cin,set);
    		ex.rentMovie(set);
    		
    	}
    	else if(input==3){
    		ex.printMovieInventory();
    	}
    	else if(input==4){
    	    cout<<"Enter title:"<<endl;
    		string word;
    		cin.ignore();
    		getline(cin,word);
    		ex.deleteMovieNode(word);
    	}
    	else if(input==5){
    	    cout<<"Tree contains: "<<ex.countMovieNodes()<<" movies."<<endl;
    	}
    	else if(input==6){
    		cout<<"Goodbye!"<<endl;
    	}
    }
	return 0;
}
