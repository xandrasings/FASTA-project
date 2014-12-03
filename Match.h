#ifndef _MATCH_
#define _MATCH_

class Match {
protected:
	int matchVal;
	int xCoor;
	int yCoor;
public:
	Match(int val, int x, int y);
	int getMatchVal();
	int getXCoor();
	int getYCoor();
};

#endif // _DVD_