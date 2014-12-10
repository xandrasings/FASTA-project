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
public: //change to protected when you fix the thing
	vector<Match> comboVec;
	float score;
public:
	Combo();
	int size();
	float getScore();
	void setScore(float newScore);
	void calcScore();
	void add(Match newMatch);
	void print();
	void printWithScore();

	friend ostream& operator<<(ostream& os, const Combo& c);
};


/***Combinations of Combinations of Matches***/
class Catalog {
public: //change to protected when you fix the thing
	vector<Combo> catalogVec;
public:
	Catalog();
	int size();
	void calcScores();
	void add(Combo newCombo);
	void print();
	void printWithScores();

	friend ostream& operator<<(ostream& os, const Catalog& c);
};

#endif // _MATCH_
