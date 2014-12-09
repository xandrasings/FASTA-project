#ifndef _MATCH_
#define _MATCH_

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
};

#endif // _MATCH_
