#include <iostream>
#include "Match.h"
using namespace std;

Match::Match(int val, int x, int y){
	matchVal=val;
	xCoor=x;
	yCoor=y;
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