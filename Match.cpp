#include <iostream>
#include <vector>
#include <cmath>
#include "Match.h"
#include <algorithm>
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

void Match::halfPrint(){
	cout << matchVal << "(" << xCoor << "," << yCoor << ") ";
}

ostream& operator<<(ostream& os, const Match& m) {
    os << m.matchVal << " (" << m.xCoor << "," << m.yCoor << ")";
    return os;
}


/***Combinations***/
Combo::Combo() {}

bool operator==(const Combo& lhs, const Combo& rhs) { return lhs.getScore() == rhs.getScore(); }
bool operator!=(const Combo& lhs, const Combo& rhs) { return !operator==(lhs, rhs); }
bool operator< (const Combo& lhs, const Combo& rhs) { return lhs.getScore() < rhs.getScore(); }
bool operator> (const Combo& lhs, const Combo& rhs) { return operator< (rhs, lhs); }
bool operator<=(const Combo& lhs, const Combo& rhs) { return !operator> (lhs, rhs); }
bool operator>=(const Combo& lhs, const Combo& rhs) { return !operator< (lhs, rhs); }

int Combo::size(){
	return comboVec.size();
}

float Combo::getScore() const {
	return score;
}

void Combo::setScore(float newScore){
	score = newScore;
}

void Combo::calcScore(float multiplier) {
	float matches = (float)(size()); //number of matches (pos)
	float sum = 0; //unimportant
	for (Match match : comboVec) {
		sum += (float)(match.getMatchVal());
	}
	float mean = sum / matches; //average match value
	float error = 0; //aggregate error from mean
	for (Match match : comboVec) {
		error += std::abs((float)(match.getMatchVal()) - mean);
	}

	setScore(matches - multiplier * error);
}

void Combo::add(Match newMatch) {
	comboVec.push_back(newMatch);
}

Match Combo::at(size_t index) {
	return comboVec.at(index);
}

void Combo::print() {
	cout << *this;
}

void Combo::printWithScore() {
	cout << *this << endl;
	cout << score << endl;
}


void Combo::printWithSequence(string str1, int num) {
	for(unsigned int i = 0; i < size(); i++) {
		comboVec.at(i).halfPrint();
		for(unsigned int j = 0; j < num; j++) {
			cout << str1[comboVec.at(i).getXCoor()+j];
		}
	cout << endl;
	}
}

Combo& Combo::operator=(const Combo& c){
	score = c.getScore();
	if (comboVec.size() > c.size()){
		comboVec.erase(comboVec.begin()+c.size(), comboVec.size();
	}
	for (int i = 0; i < c.size(); i++){
		while (i < comboVec.size()-1){
			comboVec[i]=c.comboVec[i];
		}
		comboVec.push_back(c.comboVec[i]);
	}
}

ostream& operator<<(ostream& os, const Combo& c) {
	for (Match match : c.comboVec) {
		os << match << endl;
	}
	return os;
}


/***Catalogs***/
Catalog::Catalog() {}

int Catalog::size(){
	return catalogVec.size();
}

void Catalog::calcScores(float multiplier) {
	for(unsigned int i = 0; i < size(); i++) {
		catalogVec.at(i).calcScore(multiplier);
	}
}

void Catalog::add(Combo newCombo) {
	catalogVec.push_back(newCombo);
}

void Catalog::erase(int i) {
	catalogVec.erase(catalogVec.begin()+i);
}

void Catalog::sort() {
	::sort(catalogVec.begin(), catalogVec.end(), greater<Combo>());
}

Combo Catalog::at(size_t index) {
	return catalogVec.at(index);
}

void Catalog::print(){
	cout << *this;
}

void Catalog::printWithScores() {
	size_t i = 0;
	for (Combo combo : catalogVec) {
		cout << "COMBO " << i++ << " with SCORE " << combo.score << endl;
		cout << combo << endl;
	}
}

ostream& operator<<(ostream& os, const Catalog& c) {
	size_t i = 0;
	for (Combo combo : c.catalogVec) {
		os << "COMBO " << i++ << endl;
		os << combo << endl;
	}
	return os;
}
