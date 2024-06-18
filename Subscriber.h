#pragma once

#include "Timer.h"

class Subscriber {
public:
	virtual void draw(int posX, int posY) = 0;
	virtual void update(Timer* t) = 0;
	void setTime(int time) { currTime = time; }
	bool isJustUpdated() { return justUpdated; }
protected:
	int currTime = 0;
	bool justUpdated = false;
};

