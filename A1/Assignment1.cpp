/*******************************
* Brandon Lewien
* Assignment 1 - Garage Sale
* Section 300 - Maciej Zagrodzki
********************************/

#include <iostream>
#include <fstream> //file stream
#include <sstream> //string stream
using namespace std;

struct ForSale{
                                    //price, name, sale
    int price;
    string name;
    string sale;
    ForSale(){}                     //destructor
    ForSale(string n, string s, int p){
        price = p;
        name = n;
        sale = s;
    }
};

int main(int argc, char*argv[]){
    float scores[10], total;
    string filename = argv[1];
    int a[100];                     //array of 100 integers called a
    int b[100];
                                    //array of ForSales
                                    //this will be populated with file data
    ForSale allForSales[100];
                                    //streams
    ifstream myfile(argv[1]);       //argv[1] for the first input argv
                                    //Build compile first then pwrshell
    int counter = 0;
    int match = 0;
    if(myfile.is_open()){           //read the file
        string line;
        while(getline(myfile, line)){
                                    //string stream - include sstream
            stringstream ss;
                                    //write line string into string stream
            ss<<line;   
            string item;
            string newname;
            string newsale;
            bool nope = false;      //if nope==false allow for storage
            int newprice;
            getline(ss, item, ',');
            newname = item;         //reads line for name
            getline(ss, item, ',');
            newsale = item;         //reads line for sale or wanted
            getline(ss, item);
            newprice = stoi(item);  //reads line for price of item
            for(int i = 0; i<counter; i++){
                nope = false;
                if(newname == allForSales[i].name & newprice >= allForSales[i].price & newsale == " wanted" & allForSales[i].sale == " for sale"){
                    cout<<allForSales[i].name<<" "<<allForSales[i].price<<endl;
                    match++;        //not really necessary, it's mainly for debugging purposes
                    for(int m = i; m < counter - 1 ; m++){
                        allForSales[m] = allForSales[m+1];
                    }
                    counter--;      //decrement counter since removal of item
                    nope = true;    //don't allow for storage
                    break;          //stop for loop
                }
                else if(newname == allForSales[i].name & newprice <= allForSales[i].price & newsale == " for sale" & allForSales[i].sale == " wanted"){
                    cout<<allForSales[i].name<<" "<<newprice<<endl;
                    match++;
                    for(int m = i; m < counter-1; m++){
                        allForSales[m] = allForSales[m+1];
                    }
                    counter--;      //same as above
                    nope = true;
                    break;
                }
            }
            if(nope == false){      //add no match to struct array
                allForSales[counter].name  = newname;
                allForSales[counter].price = newprice;
                allForSales[counter].sale  = newsale;
                counter++;          //increase struct array size
            }
        }
    }
    else{
        cout<<"Filename DNE"<<endl;
    }
    cout<<"Items remaining in the message board after reading all lines in the file."<<endl;
    for(int i = 0; i<counter;i++){ //cout full array with proper sizing
        cout<<allForSales[i].name<<","<<allForSales[i].sale<<", "<<allForSales[i].price<< endl;
    }
}
