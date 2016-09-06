#include<iostream>
#include<string.h>
#include<fstream>
#include<algorithm>
using namespace std;
/*
Program for:
1) finding number of paragraphs 
2) dictionary search
in a given text file (.txt)

str- the pattern input by user to be searched
word- each word from the txt file

Authors- Lakshay Juneja, Utkarsh Mittal
06 September, 2016

*/


void computePrefix (string str,int lengthOfStr,int prefix[]) {   //Function computePrefix-Computes the prefix array for str
	prefix[0]=0;
	int j=0;                                 // i, j are pointers for str 
	for (int i=1;i<lengthOfStr;i++) {
		if (str[i]==str[j]) {
			prefix[i]=j+1;
			j++;
		} else if (str[i]!=str[j]&&j==0) {
			prefix[i]=0;
		} else {
		// Debug-		cout<<"entered third condition"<<endl;
				while(j>0) {
					j=prefix[j-1];
					if (str[i]==str[j]) {
						prefix[i]=j+1;
						break;
					}					
				}
				if (str[i]!=str[j]&&j==0) {
					prefix[i]=0;
				}
			}
	}
}
bool KMP_Matcher (string str,int lengthOfStr,string word,int lengthOfWord) {    // function KMP_Matcher- matches pattern str with text file word, returns true or false
	// Debug- cout<<"pattern length "<<lengthOfStr;
	// Debug- cout<<word<<" "<<str<<endl;
	int prefix[lengthOfStr];
	computePrefix (str,lengthOfStr,prefix);
	
	// Debug- cout<<lengthOfStr<<" "<<lengthOfWord<<endl;
	int j=0; //pointer for str
	for (int i =0;i<lengthOfWord;i++) { // i is pointer for word
	// Debug-	cout<<i<<" "<<j<<endl;
		if (str[j]==word[i]) {
			j++;
		} else if (str[j]!=word[i]) {
			while (j>0) {
				j=prefix[j-1];
				if (str[j]==word[i]) {
					j++;
					break;
				}
			}
		}
		if (j==lengthOfStr) {
		// Debug-	cout<<word;
			return true;
		}
	}
	return false;
}
int main() {
	char ans='y'; //re run program from menu
	while (ans=='y'||ans=='Y') {
		int choice;
		string filename;
		cout<<"Enter the name of the file along with its extension: ";
		cin>>filename;
		cout<<endl;
		cout<<"Press 1 to find the Total no of paragraphs in text file"<<endl;
		cout<<"Press 2 to find the words present in the file containing a given string"<<endl;
		cout<<"Enter Your Choice....";
		cin>>choice;  //menu choice
		switch(choice) {
			case 1:
			{
				int para=0;		//number of paragraphs initialised to zero	
				ifstream f1;    //ifstream object
				f1.open(filename.c_str());  //opening file
				if(!f1.is_open()) {
					cout<<"ERROR!!!!"<<endl;              //error when file does not exists or cannot be opened for any reason whatsoever
					break;
				} else {
					para=1;								
					char charInFile;                   //character to be input from file
					f1.get(charInFile);
					while (!f1.eof()) {		
						if(charInFile=='\n')
							para++;                        //incrementing para counter whennewline character is found
						f1.get(charInFile);
					}
					cout<<"The Total no of paragraphs in text file = "<<para<<endl;
					f1.close();            //closing file is necessary
				}				
				break;
			}
			case 2:	
			{
				ifstream f1;
				f1.open(filename.c_str());
				if (!f1.is_open()) {
					cout<<"error"<<endl;
					break;
				}
				char letter;
				string str; 
				cout<<"Enter the string to be searched: ";
				cin>>str;
				int numberOfMatchingWords=0;             
				int totalWords=0;
				string word;
				// Debug- int lengthOfWord=0;
				while (f1>>word) {   // >> operator seperates on whitespace
					totalWords++;  //incrementing totalWords counter
					if (KMP_Matcher(str,str.length(),word,word.length())) {     //calling KMP to check if each word of file matches the pattern input by user 
							replace( word.begin(), word.end(), '.', '\0');
							replace( word.begin(), word.end(), ',', '\0');
							replace( word.begin(), word.end(), '\'', '\0');
							replace( word.begin(), word.end(), '\"', '\0');     //replacing all punctuations by null char
							cout<<word<<endl;
							numberOfMatchingWords++;           //increment matching words counter
						}
				}
				cout<<endl<<"The probability is: "<<(float)numberOfMatchingWords/(float)totalWords<<endl;
				/*
				**********************Debug:*********************
				f1.get(letter);
				while (!f1.eof()) {
					if (letter == ' ' || letter == '\n' || letter == ',' || letter == '.' ) {
						count++;
						cout<<"words is "<<word;						
						if (KMP_Matcher(str,str.length(),word,lengthOfWord)) {
							cout<<word;
							c++;
						}
						
						for (int i=0;word[i]='\0';i++) {
							word[i]='\0';
						}
						lengthOfWord=0;
					} else {
						word[lengthOfWord]=letter;
						lengthOfWord++;
					}
					f1.get(letter);
				}*/
				f1.close();
				break;
			}
			default:cout<<"Wrong Option Entered!!!!"<<endl;
		}
		cout<<"Do You Wish To Continue(Y/N)....";
		cin>>ans;
	}
}
