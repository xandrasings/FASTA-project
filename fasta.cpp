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
	float wonklessness = stof(input.at("wonklessness"));
	int result_count = stoi(input.at("result_count"));

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
	cout << endl;

	// print out matrices
	// match ratings
	cout << "VALUE MATRIX:" <<  endl;
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

	cout << "MATCHED STRINGS MATRIX:" << endl;
	// string comparison
	// string 1 across top
	cout << "    ";
	for (char ch : str1) {
		cout << ch << " ";
	}
	cout << endl;

	// everything else
	for (size_t i = 0; i < str2.size(); i++) {
		cout << " " << str2[i] << " |";
		for (size_t j = 0; j < str1.size(); j++) {
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
	cout << endl;

	//print summary of matches
	cout << "MATCH SUMMARY:" << endl;
	allMatches.printWithSequence(str1, num);
	cout << endl;


	//Create catalog
	Catalog catalog;
	//Fill with appropriate number of empty combos
	//Make this part of constructor later
	for (size_t i = 0; i < pow(2, allMatches.size()); i++) {
		Combo combo;
		catalog.add(combo);
	}

	//Fill in empty combos with all possibilities.
	for (size_t i = 0; i < allMatches.size(); i++) {
		for (size_t j = 0; j < pow(2, i); j++) {
			for (size_t k = 0; k < pow(2, allMatches.size() - i - 1); k++) {
				catalog.catalogVec.at(j * pow(2,allMatches.size() - i) + k).add(allMatches.comboVec.at(i)); //fix this so catalog and combo can have protected
			}
		}
	}

	//Remove non-valid combos

	//Remove final empty combo
	catalog.catalogVec.pop_back();

	//Find all combos that have duplicate X or Y vals
	int removeNum = 0;
	for (unsigned int i = 0; i < catalog.size(); i++) {
		for (unsigned int j = 0; j < catalog.catalogVec[i].size(); j++) {
			for (unsigned int k = j + 1; k < catalog.catalogVec[i].size(); k++) {
				if (catalog.catalogVec[i].comboVec[j].getXCoor() == catalog.catalogVec[i].comboVec[k].getXCoor() || catalog.catalogVec[i].comboVec[j].getYCoor() == catalog.catalogVec[i].comboVec[k].getYCoor()) {
					catalog.catalogVec[i].setBadCombo();
					removeNum++;
				}
			}
		}
	}

	//Add combos to stay into temp vector
	vector<Combo> cleanedUp;
	if (removeNum > 0){
		for (Combo c : catalog.catalogVec){
			if (!c.getBadCombo()){
				cleanedUp.push_back(c);
			}
		}

		//Copy back into catalog vector
		catalog.catalogVec.clear();
		for (Combo c : cleanedUp) {
			catalog.add(c);
		}

		//Clean temp vector for re-use
		cleanedUp.clear();
	}

	//Remove combos that have reverse diagonals
	int removeNum2 = 0;
	for (unsigned int i = 0; i < catalog.size(); i++) {
		for (unsigned int j = 0; j < catalog.catalogVec[i].size()-1; j++){
			if (catalog.catalogVec[i].comboVec[j].getYCoor() > catalog.catalogVec[i].comboVec[j+1].getYCoor()){
				catalog.catalogVec[i].setBadCombo();
				removeNum2++;
			}
		}
	}

	if (removeNum2 > 0) {
		//Add combos to stay into temp vector
		for (Combo c : catalog.catalogVec){
			if (!c.getBadCombo()){
				cleanedUp.push_back(c);
			}
		}

		//Copy back into catalog vector
		catalog.catalogVec.clear();
		for (Combo c : cleanedUp) {
			catalog.add(c);
		}
	}

	//Calculate scores, sort and print
	catalog.calcScores(wonklessness);
	catalog.sort();

	cout << endl << endl;
	cout << "ALL VALID COMBINATIONS:" << endl;
	cout << "-------------------------" << endl;
	catalog.printWithScores();

	cout << endl << endl;
	cout << "TOP 5 ALIGNMENTS:" << endl;
	cout << "-------------------" << endl;
	catalog.finalPrint(str1, str2, num, result_count);

	return 0;
}
