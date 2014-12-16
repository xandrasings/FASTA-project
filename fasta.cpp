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
	/*map<string, string> args = parse_arguments(argc, argv);
	map<string, string> input = get_input(args);

	string str1 = input.at("string1");
	string str2 = input.at("string2");
	int num = stoi(input.at("number"));
	float wonklessness = stof(input.at("wonklessness"));
	int result_count = stoi(input.at("result_count"));
*/

	string str1 = "atballgames";
	string str2 = "billgates";
	int num = 2;
	float wonklessness = .15;
	int result_count = 5;

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
	catalog.erase(catalog.size()-1);

	//Find all combos that have duplicate X or Y vals
	vector<unsigned int> dupIndices; //store them here, because we can't delete during loop
	for (unsigned int i = 0; i < catalog.size(); i++) {
		bool dupCheck = false;
		for (unsigned int j = 0; j < catalog.catalogVec[i].size(); j++) {
			for (unsigned int k = j + 1; k < catalog.catalogVec[i].size(); k++) {
				if (catalog.catalogVec[i].comboVec[j].getXCoor() == catalog.catalogVec[i].comboVec[k].getXCoor() || catalog.catalogVec[i].comboVec[j].getYCoor() == catalog.catalogVec[i].comboVec[k].getYCoor()) {
					dupCheck = true;
				}
			}
		}

		if (dupCheck) {
			dupIndices.push_back(i);
		}
	}

	if(dupIndices.size() > 0){
	for (unsigned int i = dupIndices.size()-1; i >= 0; i--) {
		cout << i << endl;
		catalog.erase(dupIndices.at(i));
		}
	}

	//Order remaining combos of matches by match x-coordinate
	for (unsigned int i = 0; i < catalog.size(); i++) {
		catalog.catalogVec[i].sort();
	}

	/*//Remove combos that have reverse diagonals
	for (unsigned int i = 0; i < catalog.size(); i++) {
		for (unsigned int j = 0; j < catalog.catalogVec[i].size(); j++){
			if ()
		}

	}*/

	catalog.calcScores(wonklessness);
	cout << "1" << endl;
	//catalog.sort();
		cout << "2" << endl;
	catalog.printWithScores();
		cout << "3" << endl;
	//catalog.printWithScores();
	catalog.finalPrint(str1, num, result_count);

	//catalog.printWithScores();

	/*
		kjashdfkah
		00012345678
		--BILLGATES
		    |||: |:
		ATBALLGAMES
		01234567890
		 5 (5,0)
		-2 (2,4)
		-2 (3,5)
		-2 (4,6)
		-2 (7,9)
	*/

	// string top_string = str1;
	// string bottom_string = str2;
	// size_t longest_string_size = max(top_string.size(), bottom_string.size());
	// size_t shortest_string_size = min(top_string.size(), bottom_string.size());
	// int size_diff = longest_string_size - shortest_string_size;

	// cout << "Pretty Matches" << endl;
	// top_string.insert(top_string.begin(), longest_string_size - top_string.size(), '-');
	// bottom_string.insert(bottom_string.begin(), longest_string_size - bottom_string.size(), '-');
	// cout << top_string << endl;

	// vector<string> matchLines;
	// // = { ,  ,  ,  , |, |, |, :,  , |, :}
	// for (size_t i = 0; i < bottom_string.size(); i++) {
	// 	string ch = " ";
	// 	int num_idx = 0;
	// 	bool iterate_num = false;
	// 	for (size_t j = 0; j < catalog.catalogVec.size(); j++) {
	// 		int big = max(catalog.catalogVec.at(j).getXCoor(), catalog.catalogVec.at(j).getYCoor());
	// 		int small = min(catalog.catalogVec.at(j).getXCoor(), catalog.catalogVec.at(j).getYCoor());
	// 		int gap = big - small;

	// 		if (catalog.catalogVec.at(j).getYCoor() == i && gap <= size_diff) {
	// 			ch = "|";
	// 			iterate_num = true;
	// 		}
	// 	}
	// 	matchLines.push_back(ch);
	// }
	// for (auto thing : matchLines)
	// 	cout << thing;
	// cout << endl;

	// cout << bottom_string << endl;

	//use this to print all combos in the catalog!
	return 0;
}
