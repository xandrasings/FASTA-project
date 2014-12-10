#ifndef _MATCH_
#define _MATCH_
#include <vector>
using namespace std;

/***Matches***/
class Match {
protected:
	int matchVal;
	int xCoor;
	int yCoor;
public:
	Match();
	Match(int val, int x, int y);
	Match& operator=(const Match& m);
	int getMatchVal();
	int getXCoor();
	int getYCoor();
	void print();

	friend ostream& operator<<(ostream& os, const Match& m);
};


/***Combinations of Matches***/
class Combo {
protected:
	vector<Match> comboVec;
public:
	Combo();
	void add(Match newMatch);
	void print();

	friend ostream& operator<<(ostream& os, const Combo& c);
};


/***Combinations of Combinations of Matches***/
class Catalog {
protected:
	vector<Combo> catalogVec;
public:
	Catalog();
	void add(Combo newCombo);
	void print();

	friend ostream& operator<<(ostream& os, const Catalog& c);
};

#endif // _MATCH_
