#include <iostream>
#include <vector>
#include "Match.h"
using namespace std;

/***Matches***/
Match::Match(){
	matchVal=0;
	xCoor=-1;
	yCoor=-1;
}

Match::Match(int val, int x, int y){
	matchVal=val;
	xCoor=x;
	yCoor=y;
}

Match& Match::operator=(const Match& m){
	matchVal=m.matchVal;
	xCoor=m.xCoor;
	yCoor=m.yCoor;
	return *this;
}

int Match::getMatchVal(){
	return matchVal;
}

int Match::getXCoor(){
	return xCoor;
}

int Match::getYCoor(){
	return yCoor;
}

void Match::print(){
	cout << matchVal << " (" << xCoor << "," << yCoor << ")" << endl;
}

/***Combinations***/
Combo::Combo(){
	vector<Match> comboVec;
}

void Combo::add(Match newMatch){
	comboVec.push_back(newMatch);
}

void Combo::print(){
  for (unsigned int i = 0; i < comboVec.size(); i++) {
    comboVec.at(i).print();
  }
}

/***Catalogs***/
Catalog::Catalog(){
	vector<Match> comboVec;
}

void Catalog::add(Combo newCombo){
	catalogVec.push_back(newCombo);
}

void Catalog::print(){
  for (unsigned int i = 0; i < catalogVec.size(); i++) {
  	cout << "COMBO " << i+1 << endl;
    catalogVec.at(i).print();
  }
}

