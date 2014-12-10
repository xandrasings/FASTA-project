/* fasta funtimes */

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "Match.h"
#include "arguments.cpp"
using namespace std;

string prettify(int entry) {
	if (entry <= -10) {return to_string(entry);}
	else if (entry < 0) {return to_string(entry) + " ";}
	else if (entry >= 10) {return "+" + to_string(entry);}
	else {return "+" + to_string(entry)+" ";}
}

int main(int argc, const char* argv[]) {
	map<string, string> args = parse_arguments(argc, argv);
	map<string, string> input = get_input(args);

	string str1 = input.at("string1");
	string str2 = input.at("string2");
	int num = stoi(input.at("number"));

	cout << "Processed args: " << str1 << ' ' << str2 << ' ' << num << endl;

	// create necessary matrices
	int width = str1.size() - num + 1;
	int height = str2.size() - num + 1;
	vector< vector<bool> > boolMatrix(height, vector<bool>(width));
	vector< vector<int> > valMatrix(height, vector<int>(width));
	vector< vector<char> > ntideMatrix(str2.size(), vector<char>(str1.size()));
	Combo allMatches;

	// check for matches
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			bool check = true;
			for (int k = 0; k < num; k++) {
				if (str1[j+k] != str2[i+k]) {
					check = false;
				}
			}
			if (check == true) {
				boolMatrix[i][j] = true;
				valMatrix[i][j] = j-i;
				allMatches.add(Match((j-i),j,i));
				for (int k = 0; k < num; k++) {
					ntideMatrix[i+k][j+k] = str1[j+k];
				}
			}
		}
	}

	// print out matrices
	// match ratings
	cout << endl;
	for (int i = 0; i < height; i++) {
		cout << "|";
		for (int j = 0; j < width; j++) {
			if (boolMatrix[i][j]) {
				cout << prettify(valMatrix[i][j]) << "|";
			}
			else {
				cout << "   |";
			}
		}
		cout << endl;
	}

	cout << endl;
	// string comparison
	// string 1 across top
	cout << "    ";
	for (unsigned int x = 0; x < str1.size(); x++) {
		cout << str1[x] << " ";
	}
	cout << endl;

	// everything else
	for (unsigned int i = 0; i < str2.size(); i++) {
		cout << " " << str2[i] << " |";
		for (unsigned int j = 0; j < str1.size(); j++) {
			if (ntideMatrix[i][j]) {
				cout << ntideMatrix[i][j];
			}
			else {
				cout << " ";
			}
			cout  << "|";
		}
		cout << endl;
	}

	//print summary of matches
	allMatches.print();

	//Create catalog
	Catalog catalog;
	//Fill with appropriate number of empty combos
	//Make this part of constructor later
	for (unsigned int i = 0; i < pow(2,allMatches.size()); i++) {
		Combo combo;
		catalog.add(combo);
	}

	for (unsigned int i = 0; i < allMatches.size(); i++) {
		for (unsigned int j = 0; j < pow(2,i); j++) {
			for (unsigned int k = 0; k < pow(2,allMatches.size()-i-1); k++) {
				catalog.catalogVec.at(j*pow(2,allMatches.size()-i)+k).add(allMatches.comboVec.at(i)); //fix this so catalog and combo can have protected
			}
		}
	}	

	catalog.print();
	return 0;
}
