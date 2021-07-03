/*
This C++ program read in a txt file called "source code.txt" and extract characters in it one by one. After finish reading the file, the program will produce a brief report of the content inside the .txt file.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int main()
{
	string filename = "source code.txt";
	fstream in(filename);
	char token,temp;
	queue<char> word, charnum;
	vector<string> wordvector, numvector, specialvector;
	string tempstring="";
	vector<char> allchar;
	int identifier = 0, number = 0, special = 0, key = 0,character=0;
	//read the file
	while (in.get(token)) {
		if (isalpha(token)) {
			character++;
			if (charnum.empty() != true) {
				while (charnum.empty() != true) {
					temp = charnum.front();
					charnum.pop();
					tempstring.push_back(temp);
				}
				numvector.push_back(tempstring);
				tempstring = "";
			}
			word.push(token);
			allchar.push_back(token);
			continue;
		}
		if (isdigit(token)) {
			if (word.empty() != true) {
				while (word.empty() != true) {
					temp = word.front();
					word.pop();
					tempstring.push_back(temp);
				}
				wordvector.push_back(tempstring);
				tempstring = "";
			}
			charnum.push(token);
			allchar.push_back(token);
			continue;
		}
		if (token == ';' || token == '"' || token == '(' || token == ')' || token == '<' || token == '>' || token == '#') {
			special++;
			if (word.empty() != true) {
				while (word.empty() != true) {
					temp = word.front();
					word.pop();
					tempstring.push_back(temp);
				}
				wordvector.push_back(tempstring);
				tempstring = "";
			}
			if (charnum.empty() != true) {
				while (charnum.empty() != true) {
					temp = charnum.front();
					charnum.pop();
					tempstring.push_back(temp);
				}
				numvector.push_back(tempstring);
				tempstring = "";
			}
			tempstring.push_back(token);
			specialvector.push_back(tempstring);
			tempstring = "";
			allchar.push_back(token);
			continue;
		}
		if (charnum.empty() != true) {
			while (charnum.empty() != true) {
				temp = charnum.front();
				charnum.pop();
				tempstring.push_back(temp);
			}
			numvector.push_back(tempstring);
			tempstring = "";
		}
	
		if (word.empty() != true) {
			while (word.empty() != true) {
				temp = word.front();
				word.pop();
				tempstring.push_back(temp);
			}
			wordvector.push_back(tempstring);
			tempstring = "";
		}
	}
	in.close();
	
	//count how many copies each word, number, and special character are contained
	int count = 1;
	vector<int> wordcount, specialcount, numbercount;
	//for number
	for (auto i = numvector.begin(); i != numvector.end() - 1; i++) {
		for (auto j = i + 1; j != numvector.end(); j++) {
			if (*i == *j) {
				count++;
			}
		}
		numbercount.push_back(count);
		count = 1;
		if(i == numvector.end()-2) numbercount.push_back(1); //for last element
	}


	//for special
	for (auto i = specialvector.begin(); i != specialvector.end() - 1; i++) {
		for (auto j = i + 1; j != specialvector.end(); j++) {
			if (*i == *j) {
				count++;
			}
		}
		specialcount.push_back(count);
		count = 1;
		if (i == specialvector.end() - 2) specialcount.push_back(1);
	}

	//for word
	for (auto i = wordvector.begin(); i != wordvector.end()-1; i++) {
		for (auto j = i + 1; j != wordvector.end(); j++) {
			if (*i == *j) {
				count++;
			}
		}
		wordcount.push_back(count);
		count = 1;
		if (i == wordvector.end() - 2) wordcount.push_back(1);
	}


	//check duplicates and extract unique characters
	vector<string> checkedword, checkednum, checkedspecial;

	bool dup=false;
	//for number
	for (auto i = numvector.begin(); i != numvector.end(); i++) {
		for (auto j = checkednum.begin(); j != checkednum.end(); j++) {
			if (*i == *j) {
				dup = true;
			}
		}
		if (dup == false) {
			checkednum.push_back(*i);
		}
		dup = false;
	}

	//for special
	for (auto i = specialvector.begin(); i != specialvector.end(); i++) {
		for (auto j = checkedspecial.begin(); j != checkedspecial.end(); j++) {
			if (*i == *j) {
				dup = true;
			}
		}
		if (dup == false) {
			checkedspecial.push_back(*i);
		}
		dup = false;
	}


	//for word
	for (auto i = wordvector.begin(); i != wordvector.end(); i++) {
		for (auto j = checkedword.begin(); j != checkedword.end(); j++) {
			if (*i == *j) {
				dup = true;
			}
		}
		if (dup == false) {
			checkedword.push_back(*i);
		}
		dup = false;
	}

	//count how many unique characters are in each categories
	vector<int> checkedwordnum, checkednumnum, checkedspecialnum;
	int totalword=0, totalnum=0, totalspecial=0;
	//for number
	for (unsigned int i = 0; i < checkednum.size(); i++) {
		for (unsigned int j = 0; j < numvector.size(); j++) {
			if (checkednum[i] == numvector[j]) {
				checkednumnum.push_back(numbercount[j]);
				break;
			}
		}
	}
	//for total numbers
	for (auto i = checkednumnum.begin(); i < checkednumnum.end(); i++) {
		totalnum += *i;
	}

	//for special
	for (unsigned int i = 0; i < checkedspecial.size(); i++) {
		for (unsigned int j = 0; j < specialvector.size(); j++) {
			if (checkedspecial[i] == specialvector[j]) {
				checkedspecialnum.push_back(specialcount[j]);
				break;
			}
		}
	}
	//for total special
	for (auto i = checkedspecialnum.begin(); i < checkedspecialnum.end(); i++) {
		totalspecial += *i;
	}


	//for word
	for (unsigned int i = 0; i <checkedword.size(); i++) {
		for (unsigned int j = 0; j <wordvector.size(); j++) {
			if (checkedword[i]==wordvector[j]) {
				checkedwordnum.push_back(wordcount[j]);
				break;
			}
		}
	}

	//for total words
	for (auto i = checkedwordnum.begin(); i < checkedwordnum.end(); i++) {
		totalword += *i;
	}
	
	//split keywords and identifier from words
	vector<string> keylist, idlist;
	vector<int> keynum, idnum;
	int totalkey=0, totalid=0;
	for (unsigned int i = 0; i < checkedword.size(); i++) {
		if (checkedword[i] == "for"||checkedword[i] == "include" || checkedword[i] == "iostream" || checkedword[i] == "int" || checkedword[i] == "main" || checkedword[i] == "cout" || checkedword[i] == "using" || checkedword[i] == "namespace") {
			keylist.push_back(checkedword[i]);
			keynum.push_back(checkedwordnum[i]);
		}
		else {
			idlist.push_back(checkedword[i]);
			idnum.push_back(checkedwordnum[i]);
		}
	}
	
	for (auto i = keynum.begin(); i < keynum.end(); i++) {
		totalkey += *i;
	}
	for (auto i = idnum.begin(); i < idnum.end(); i++) {
		totalid += *i;
	}


	//Report
	cout << "Summary of the content inside file: \""<<filename<<"\""<<endl<<endl;

	cout << "All tokens appeared in this document are: ";
	for (auto i = allchar.begin(); i != allchar.end(); i++) {
		cout << *i << " ";
	}
	cout << endl<<endl;

	cout << "Words included: ";
	for (auto i = checkedword.begin(); i != checkedword.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	cout << "Appeared times(in-order): ";
	for (auto i = checkedwordnum.begin(); i != checkedwordnum.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Total number of words is: " << totalword << endl << endl;

	cout << "Keywords included: ";
	for (auto i = keylist.begin(); i != keylist.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	cout << "Appeared times(in-order): ";
	for (auto i = keynum.begin(); i != keynum.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Toal number of keywords is: " <<totalkey<<endl<<endl;

	cout << "Identifiers included: ";
	for (auto i = idlist.begin(); i != idlist.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	cout << "Appeared times(in-order): ";
	for (auto i = idnum.begin(); i != idnum.end(); i++) {
		cout << *i << " ";
	}

	cout << endl;
	cout << "Toal number of identifiers is: " << totalid << endl << endl;

	cout << "Numbers included: ";
	for (auto i = checkednum.begin(); i != checkednum.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	cout << "Appeared times(in-order): ";
	for (auto i = checkednumnum.begin(); i != checkednumnum.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Total number of numbers is: "<< totalnum<<endl<<endl;
	
	cout << "Special characters included: ";
	for (auto i = checkedspecial.begin(); i != checkedspecial.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	cout << "Appeared times(in-order): ";
	for (auto i = checkedspecialnum.begin(); i != checkedspecialnum.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Total number of special characters is: " << totalspecial << endl << endl;

}

