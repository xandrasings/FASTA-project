#ifndef _ARGUMENTS_
#define _ARGUMENTS_

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>

map<string, string> parse_arguments(int argc, const char* argv[]) {
	// cout << "parse_arguments" << endl;
	string help_message = "I'm a helpful help message.\n";
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
	possible_flags["-w"] = "wonklessness";
	possible_flags["--number"] = "number";
	possible_flags["--string1"] = "string1";
	possible_flags["--string2"] = "string2";
	possible_flags["--file"] = "input_file";
	possible_flags["--output"] = "output_file";
	possible_flags["--help"] = "show_help";
	possible_flags["--wonklessness"] = "wonklessness";

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

	if (!mapper.count("wonklessness"))
		mapper.insert(make_pair(possible_flags.at("-w"), 0.15));

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

#endif
