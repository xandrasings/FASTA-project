/* fasta funtimes */

#include <vector>
#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Match.h"
using namespace std;

string prettify(int entry) {
	if (entry <= -10) {return to_string(entry);}
	else if (entry < 0) {return to_string(entry) + " ";}
	else if (entry >= 10) {return "+" + to_string(entry);}
	else {return "+" + to_string(entry)+" ";}
}

map<string, string> parse_arguments(int argc, const char* argv[]) {
	// cout << "parse_arguments" << endl;
	string help_message = "I'm a helpful help message.";
	if (argc < 2) {
		cout << help_message;
		exit(0);
	}

	vector<string> args;
	for (int i = 1; i < argc; i++)
		args.push_back(argv[i]);

	map<string, string> mapper;
	argc = args.size();

	map<string, string> possible_flags;
	possible_flags["-n"] = "number";
	possible_flags["-s1"] = "string1";
	possible_flags["-s2"] = "string2";
	possible_flags["-f"] = "input_file";
	possible_flags["-o"] = "output_file";
	possible_flags["-h"] = "show_help";
	possible_flags["--number"] = "number";
	possible_flags["--string1"] = "string1";
	possible_flags["--string2"] = "string2";
	possible_flags["--file"] = "input_file";
	possible_flags["--output"] = "output_file";
	possible_flags["--help"] = "show_help";

	if ((argc) % 2 == 0) {
		// we have an even number of arguments.
		for (int i = 0; i < argc; i+=2) {
			mapper.insert(make_pair(possible_flags.at(args.at(i)), args.at(i+1)));
		}
	}
	else if (args.at(0)[0] == '-') {
		// we will assume that the last argument is an input filename
		mapper.insert(make_pair(possible_flags.at("-f"), args.at(argc-1)));
		for (int i = 0; i < argc; i+=2) {
			cout << i+1 << ' ';
			mapper.insert(make_pair(possible_flags.at(args.at(i)), args.at(i+1)));
		}
		cout << endl;
	}
	else if (args.at(argc-1)[0] == '-') {
		// we will assume that the first argument is an input filename
		cout << "path 3" << endl;
		mapper.insert(make_pair(possible_flags.at("-f"), args.at(1)));
		for (int i = 1; i < argc; i+=2) {
			mapper.insert(make_pair(possible_flags.at(args.at(i)), args.at(i+1)));
		}
	}

	// cout << endl;
	// for (auto v : mapper)
	//   cout << v.first << ": " << v.second << endl;

	return mapper;
}

string read_line_from_file(string start_with, string filename) {
	// cout << "read_line_from_file(\"" << start_with << "\", \"" << filename << "\")" << endl;
	ifstream input_file(filename);
	string line = "";
	if (input_file.is_open()) {
		string maybe_line;
		while (getline(input_file, maybe_line)) {
			string substr = maybe_line.substr(0, start_with.size());
			if (substr == start_with) {
				line = maybe_line.substr(substr.size());
			}
		}
	}
	return line;
}

map<string, string> get_input(map<string, string> args) {
	// cout << "get_input" << endl;
	map<string, string> values;

	vector<string> to_look_for = {"string1", "string2", "number"};
	for (string thing : to_look_for) {
		if (args.count(thing)) {
			values.insert(make_pair(thing, args.at(thing)));
		}
		else if (args.count("input_file")) {
			values.insert(make_pair(thing, read_line_from_file(thing + ':', args.at("input_file"))));
		}
	}

	cout << endl << "Input Values:" << endl;
	for (auto v : values)
		cout << v.first << ": " << v.second << endl;

	return values;
}

int main(int argc, const char* argv[]) {
	map<string, string> args = parse_arguments(argc, argv);
	map<string, string> input = get_input(args);

	string str1 = input.at("string1");
	string str2 = input.at("string2");
	int alignmentCount = stoi(input.at("number"));

	cout << "Processed args: " << str1 << ' ' << str2 << ' ' << alignmentCount << endl;

	// create necessary matrices
	int width = str1.size() - alignmentCount + 1;
	int height = str2.size() - alignmentCount + 1;
	vector< vector<bool> > boolMatrix(height, vector<bool>(width));
	vector< vector<int> > valMatrix(height, vector<int>(width));
	vector< vector<char> > ntideMatrix(str2.size(), vector<char>(str1.size()));
	Combo allMatches;

	// check for matches
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			bool check = true;
			for (int k = 0; k < alignmentCount; k++) {
				if (str1[j+k] != str2[i+k]) {
					check = false;
				}
			}
			if (check == true) {
				boolMatrix[i][j] = true;
				valMatrix[i][j] = j-i;
				allMatches.add(Match((j-i),j,i));
				for (int k = 0; k < alignmentCount; k++) {
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

	// print summary of matches
	allMatches.print();

	return 0;
}
