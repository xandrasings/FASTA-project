#include <iostream>
#include "Match.h"
using namespace std;

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
