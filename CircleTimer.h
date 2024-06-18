#pragma once
#include "Subscriber.h"
class CircleTimer : public Subscriber {
public:
	void draw(int posX, int posY);
	void update(Timer* t) {
		currTime = t->getTimeLeft();
		startTime = t->getTimeStart();
		elapsedTime = t->getTimeElapsed();
		if (t->isGapSet() && t->isInGap() && !inGap) {
			inGap = true; empty = true;
		}
		if (inGap) {
			startTime = 10;
			elapsedTime = startTime - currTime;
		}
		if (t->isGapSet() && !t->isInGap()) {
			inGap = false; empty = true;
		}
		justUpdated = true;
	}
	void fillCircle(int posX, int posY, int sideLength, int radFill, char pChar);
private:
	// length of the side of a square
	// inside which circle is inscribed
	// it is equal to radius
	int sideLength = 7;
	int startTime = 0;
	int elapsedTime = 0;
	int xMultiple = 2;
	int yMultiple = 1;
	char charFill = '+';
	char charEmpty = '.';
	bool inGap = false;
	bool empty = true;
};

