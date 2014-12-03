/* fasta funtimes */

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Match.h"
using namespace std;

string prettify (int entry) {
  if (entry <= -10) {return to_string(entry);}
  else if (entry < 0) {return to_string(entry)+" ";}
  else if (entry >= 10) {return "+"+to_string(entry);}
  else {return "+"+to_string(entry)+" ";}
}

int main()  {
  string str1;
  string str2;
  int num;
  cout << "Please enter the first string: ";
  cin >> str1;
  cout << "Please enter the second string: ";
  cin >> str2;
  cout << "Please enter number of choice: ";
  cin >> num;

  //create necessary matrices
  int width = str1.size()-num+1;
  int height = str2.size()-num+1;
  vector< vector<bool> > boolMatrix(height,vector<bool>(width));
  vector< vector<int> > valMatrix(height,vector<int>(width));
  vector< vector<char> > ntideMatrix(str2.size(),vector<char>(str1.size()));
  vector< vector<Match> > matchMatrix(height, vector<Match>(width));

  //check for matches
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      bool check = true;
      for (int k = 0; k < num; k++) {
        if (str1[j+k] != str2[i+k]) {
          check = false;
        }
      }
      if (check == true) {
        boolMatrix[i][j]=true;
        valMatrix[i][j]=j-i;
        Match tempMatch((j-i),j,i);
        matchMatrix[i][j]=tempMatch;
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

  //everything else
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

  return 0;
}
