#pragma once

#include <thread>
#include <vector>


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// proveriti sta rade restart, pause, resume u kombinaciji sa turnGapsOn/Off i start mozda ima bagova
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


class Subscriber;

class Timer {
public:
	Timer(int time = 0) { 
		if (time < 0) time = 0;
		restart(time);
		/*
		startTime = time;
		timeLeft = time;
		timerDone = false;
		turnGapOff();
		*/
	}
	void start() {
		if (threads.size() == 0)
			threads.push_back(std::thread(&Timer::passTime, this));
	}
	void pause() { paused = true; }
	void resume() { paused = false; }
	void restart(int time) {
		startTime = time;
		timeLeft = time;
		timerDone = false;
		killMusic();
		if (gaps) turnGapOn();
		else turnGapOff();
	}
	int getTimeLeft() { return timeLeft; }
	int getTimeElapsed() { return startTime - timeLeft; }
	int getTimeStart() { return startTime; }
	bool isDone() { return timerDone; }
	bool isGapSet() { return gaps; }
	bool isInGap() { return inGap; }
	~Timer() {
		killThread = true;
		for (int i = 0; i < threads.size(); ++i)
			threads[i].join();
	}
	void addSubscriber(Subscriber* newSub);
	void addTime(int timeDiff) {
		startTime += timeDiff;
		timeLeft += timeDiff;
		if (timeLeft <= 0) timeLeft = 1;
		if (startTime <= 0) startTime = 2;
		if (gaps) turnGapOn();
	}
	void turnGapOff() { gaps = false; gapVecIndex = 0; modChange = true; gapsVec.clear(); }
	void turnGapOn();
	void pauseUpdate() { updatePaused = true; }
	void resumeUpdate() { updatePaused = false; }
	void killMusic() { system("powershell -c Exit;"); }
private:
	int startTime = 0;
	int timeLeft = 0;
	int gapVecIndex = 0;
	bool paused = false;
	bool updatePaused = false;
	bool timerDone = false;
	bool killThread = false;
	bool gaps = false;
	bool inGap = false;
	bool modChange = false;
	void passTime();
	void normalPassTime();
	void gapPassTime();
	void gapTime();
	std::vector<Subscriber*> subscribers;
	std::vector<std::thread> threads;
	std::vector<unsigned> gapsVec;
};

