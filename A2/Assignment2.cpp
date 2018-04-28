/*******************************
* Brandon Lewien
* Assignment 2
* Section 300 - Maciej Zagrodzki
********************************/

#include <iostream>
#include <fstream> //file stream
#include <sstream> //string stream
using namespace std;

struct wordItem{
	int count=0;
	string word="";
};

void resize(wordItem **old, int *capacity){
// Personal made function to resize. Takes in the address of the old array and pointer to the capacity,
// and stores it into an array that is double the size. Changes the value of the size to twice the size
// and gives back the same array but with twice the size.



	int max = *capacity*2;								// Store the value of the capacity, double it into another value;
	wordItem * new1 = new struct wordItem[max];			// New dynamic array

	for(int i = 0; i < *capacity;i++){					// Push all old info to new
		new1[i] = (*old)[i];
	}

	delete [] *old;										// Delete old array

	*old = new1;										// Point to new array

	*capacity = max;									//Point to new capacity value
}
/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into an array
* @param ignoreWordFile - filename (the file storing ignore words)
* @param ignoreWords - store ignore words from the file (pass by
reference) * @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(char *ignoreWordFileName, string ignoreWords[]){
// Simple fileread from an argument. The check for file does not exist throws nothing in return,
// causing an infinite loop in terminal. Use Ctrl+c to exit. Would love to change this function from
// void to int or something to return next time.
	ifstream myfile(ignoreWordFileName);
	int i = 0;
	if(myfile.is_open()){
		string line;
		string item;
		while(getline(myfile, line)){
			ignoreWords[i] = line;
			i++;
		}
	}
	else{
		cout<<"File DNE!"<<endl;
	}
}
/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param ignoreWords - the array of strings storing ignore/stop words *
@return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(string word, string ignoreWords[]){
// Returns true only if word matches a word in the array of ignore words.
	for(int i = 0;i<50;i++){
		if(word == ignoreWords[i]){
			return true;
		}
	}
	return false;
}
/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array
(including repeated words)
* @param list - an array of wordItems containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including
repeated words multiple times)
*/
int getTotalNumberNonStopWords(wordItem list[], int length){
// I technically had a checker in my main called number within the while loop
// but since this was mandatory I made this function too. Basically adds all the counts together.
	int total = 0;
	for(int i = 0;i<length;i++){
		total += list[i].count;
	}
	return total;
}
/*
* Function name: arraySort
* Purpose: sort an array of wordItems, increasing, by their count
fields * @param list - an array of wordItems to be sorted
* @param length - the length of the words array
*/
void arraySort(wordItem list[], int length){
// Using bubblesort, where if the next output is bigger it will swap with the first
	for(int i = 0; i<length-1;i++){
		for(int j = 0; j<length-i-1;j++){
			if(list[j].count < list[j+1].count){
				wordItem temp;
				temp = list[j];
				list[j] = list[j+1];
				list[j+1]=temp;
			}
		}
	}
}
/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of
wordItems * @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN){
	for(int i = 0; i<topN;i++){						// Allows for resizing of output with argv[1]
		cout<<wordItemList[i].count<<" - " << wordItemList[i].word<<endl;		
	}
}

int main(int argc, char * argv[]){
	int size = 100;												// Preset to 100
	string sentence;											// For storing input from file
	int num = 1;												// I should've started with 0. It would mess everything
																// up if changed to 1 because of how I did my functions
	int counter = 1;											// To allow the for loop to read everything if no match	
	int doublecount = 0;										// Counting the number of array doublings
	wordItem * lister = new struct wordItem[size];
	string *ip = new string[size];
	int number = 0;
	getStopWords(argv[3],ip);									// argv[3] = ignorewords.txt
	ifstream myfile(argv[2]);									// argv[2] = HungerGames_edit.txt
	if(myfile.is_open()){
		while(getline(myfile, sentence)){
			stringstream ss1;
			ss1<<sentence;
			while(ss1>>sentence){
				if(isStopWord(sentence,ip)==false){
					number++;
					for(int i = 0;i<num;i++){
						if(num == size){
						    
							doublecount++;
							resize(&lister,&size);
						}
						if(sentence.compare(lister[i].word) != 0 && counter == num){  // If no match and goes through entire array
							lister[num].word = sentence;
							lister[i].count++;
							num++;
                            
							counter = 1;
							break;
						}
						else if(sentence == lister[i].word){
							lister[i].count++;
							counter = 1;
							break;
						}
						counter++;
					}
				}
			}
		}
		arraySort(lister,num);									// Sorting array after reading
		num--;  												// To compensate my mistake by making num = 1 in the beginning
	}

	else{
		cout << "Failed open" << endl;
	}
//OUTPUTS
	printTopN(lister,stoi(argv[1]));
	cout<<"#"<<endl;
	cout<<"Array doubled: "<<doublecount<<endl;
	cout<<"#"<<endl;
	cout<<"Unique non-common words: "<<num<<endl;
	cout<<"#"<<endl;
	cout<<"Total non-common words: "<<getTotalNumberNonStopWords(lister,num)<<endl;
	return 0;
}
