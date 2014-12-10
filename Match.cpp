#include <iostream>
#include <vector>
#include <cmath>
#include "Match.h"
using namespace std;

/***Matches***/
Match::Match() {
	matchVal = 0;
	xCoor = -1;
	yCoor = -1;
}

Match::Match(int val, int x, int y){
	matchVal = val;
	xCoor = x;
	yCoor = y;
}

Match& Match::operator=(const Match& m){
	matchVal = m.matchVal;
	xCoor = m.xCoor;
	yCoor = m.yCoor;
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
Combo::Combo() {
	vector<Match> comboVec;
	float score;
}

int Combo::size(){
	return comboVec.size();
}

float Combo::getScore() {
	return score;
}

void Combo::setScore(float newScore){
	score = newScore;
}

void Combo::calcScore(int str1Size, int str2Size) {
	float matches = (float)(size()); //number of matches (pos)
	float stringSize = (float)(str1Size+str2Size); //size of both strings 
	float sum = 0; //unimportant
	for (unsigned int i = 0; i < size(); i++) {
		sum = sum + (float)(comboVec.at(i).getMatchVal());
	}
	float mean = sum / matches; //average match value
	float error = 0; //aggregate error from mean
	for (unsigned int i = 0; i < size(); i++) {
		error = error + std::abs((float)(comboVec.at(i).getMatchVal())-mean);
	}

	setScore(matches - 3 * error / (stringSize));
}

void Combo::add(Match newMatch) {
	comboVec.push_back(newMatch);
}

void Combo::print() {
	cout << *this;
}

void Combo::printWithScore() {
	print();
	cout << score << endl;
}

ostream& operator<<(ostream& os, const Combo& c) {
	for (auto match : c.comboVec) {
		os << match << endl;
	}
	return os;
}


/***Catalogs***/
Catalog::Catalog(){
	vector<Combo> catalogVec;
}

int Catalog::size(){
	return catalogVec.size();
}

void Catalog::calcScores(int str1Size, int str2Size) {
	for(unsigned int i = 0; i < size(); i++) {
		catalogVec.at(i).calcScore(str1Size, str2Size);
	}
}

void Catalog::add(Combo newCombo){
	catalogVec.push_back(newCombo);
}

void Catalog::print(){
	cout << *this;
}

void Catalog::printWithScores() {
	for(unsigned int i = 0; i < size(); i++) {
		cout << "COMBO " << i << " with SCORE " << catalogVec.at(i).score << endl;
		catalogVec.at(i).print();
	}
}

ostream& operator<<(ostream& os, const Catalog& c) {
	unsigned int i = 0;
	for (auto match : c.catalogVec) {
		os << "COMBO " << i++ << endl;
		os << match << endl;
	}
	return os;
}
