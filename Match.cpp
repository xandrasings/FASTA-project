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

bool operator==(const Match& lhs, const Match& rhs) { return lhs.getXCoor() == rhs.getXCoor(); }
bool operator!=(const Match& lhs, const Match& rhs) { return !operator==(lhs, rhs); }
bool operator< (const Match& lhs, const Match& rhs) { return lhs.getXCoor() < rhs.getXCoor(); }
bool operator> (const Match& lhs, const Match& rhs) { return operator< (rhs, lhs); }
bool operator<=(const Match& lhs, const Match& rhs) { return !operator> (lhs, rhs); }
bool operator>=(const Match& lhs, const Match& rhs) { return !operator< (lhs, rhs); }

Match& Match::operator=(const Match& m){
	matchVal = m.matchVal;
	xCoor = m.xCoor;
	yCoor = m.yCoor;
	return *this;
}

int Match::getMatchVal(){
	return matchVal;
}

int Match::getXCoor() const {
	return xCoor;
}

int Match::getYCoor() const {
	return yCoor;
}

void Match::print(){
	cout << *this << endl;
}

void Match::halfPrint(){
	cout << matchVal << " (" << xCoor << "," << yCoor << ") ";
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

void Combo::printAlignment(string str1, string str2, int num) {

	/*
	string finalStr1 = "";
	string finalStr2 = "";
	//int startIndels = comboVec[0].getXCoor()-comboVec[0].getYCoor();

	add(Match(str2.size()-str1.size(),str1.size(),str2.size()));
	add(Match(0,-1,-1));
	sort();

	for (unsigned int i = 0; i < size() - 1; i++) {
		int X1 = comboVec[i].getXCoor();
		int X2 = comboVec[i+1].getXCoor();
		int Y1 = comboVec[i].getYCoor();
		int Y2 = comboVec[i+1].getYCoor();

		int indelQuant = (X2 - X1) - (Y2 - Y1);

		if (indelQuant < 0) {
			for (unsigned int i = 0; i < -1 * indelQuant; i++) {
				finalStr1 = finalStr1 + "_";
			}
		}
		else if (indelQuant > 0) {
			for (unsigned int i = 0; i < indelQuant; i++) {
				finalStr2 = finalStr2 + "_";
			}
		}

		finalStr1 = finalStr1 + str1.substr(X1 + 1, X2 - X1);
		finalStr2 = finalStr2 + str2.substr(Y1 + 1, Y2 - Y1);
	}

	cout << finalStr1 << endl << endl << finalStr2 << endl;
	*/
}

void Combo::sort() {
	::sort(comboVec.begin(), comboVec.end(), less<Match>());
}

bool Combo::getBadCombo() const{
	return badCombo;
}

void Combo::setBadCombo(){
	badCombo = true;
}

Combo& Combo::operator=(const Combo& c){
	score = c.getScore();
	if (comboVec.size() > c.comboVec.size()){
		comboVec.resize(c.comboVec.size());
	}
	int i;
	for (i = 0; i < comboVec.size() - 1; i++) {
		comboVec[i]=c.comboVec[i];
	}
	for (; i < c.comboVec.size(); i++) {
		comboVec.push_back(c.comboVec[i]);
	}
	return *this;
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


/*
void Catalog::sort() {
	int max = catalogVec.size();
	cout << catalogVec[max-1].getScore();
	for (unsigned int i = 0; i < max; i++) {
		cout << "Looking at #" << i << endl;
		int newRef = 0;
		for (unsigned int j = 0; j < i; j++) {
			cout << j << ", " << catalogVec[j].getScore() << ". ";
			if (catalogVec[j].getScore() > catalogVec[catalogVec.size()-1].getScore()) {
				newRef = j;
				break;
			}
			
			
		}
		
		//cout << newRef << endl;
		catalogVec.pop_back();
		
	}
}
*/

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

void Catalog::finalPrint(string str1, string str2, int num, int results) {
	for (unsigned int i = 0; i < min(size(), results); i++) {
	//for (Combo combo : catalogVec) {
		cout << "COMBO " << i+1 << " with score of " << catalogVec[i].score << ":" << endl;
		catalogVec[i].printWithSequence(str1, num);
		cout << endl;
		catalogVec[i].printAlignment(str1, str2, num);
		cout << endl;
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
