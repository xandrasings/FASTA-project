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
	cout << *this << endl;
}

ostream& operator<<(ostream& os, const Match& m) {
    os << m.matchVal << " (" << m.xCoor << "," << m.yCoor << ")";
    return os;
}


/***Combinations***/
Combo::Combo(){
	vector<Match> comboVec;
}

void Combo::add(Match newMatch){
	comboVec.push_back(newMatch);
}

void Combo::print(){
	cout << *this;
}

ostream& operator<<(ostream& os, const Combo& c) {
	for (auto match : c.comboVec) {
		os << match << endl;
	}
	return os;
}


/***Catalogs***/
Catalog::Catalog(){
	vector<Match> comboVec;
}

void Catalog::add(Combo newCombo){
	catalogVec.push_back(newCombo);
}

void Catalog::print(){
	cout << *this;
}

ostream& operator<<(ostream& os, const Catalog& c) {
	unsigned int i = 0;
	for (auto match : c.catalogVec) {
		os << "COMBO " << i++ << endl;
		os << match << endl;
	}
	return os;
}
