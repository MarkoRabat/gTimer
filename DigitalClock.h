#pragma once

#include "Subscriber.h"
#include "Timer.h"
#include <string>

class DigitalClock : public Subscriber {
public:
	void draw(int posX, int posY);
	void update(Timer* t) {
		currTime = t->getTimeLeft();
		justUpdated = true;
	}
private:
	void drawDigit(int posX, int posY, int digit);
	void drawDigit0(int posX, int posY);
	void drawDigit1(int posX, int posY);
	void drawDigit2(int posX, int posY);
	void drawDigit3(int posX, int posY);
	void drawDigit4(int posX, int posY);
	void drawDigit5(int posX, int posY);
	void drawDigit6(int posX, int posY);
	void drawDigit7(int posX, int posY);
	void drawDigit8(int posX, int posY);
	void drawDigit9(int posX, int posY);
	void drawSep(int posX, int posY);
};

