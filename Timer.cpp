#define _CRT_RAND_S
#include "Timer.h"
#include "Subscriber.h"
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>

void Timer::passTime() {
	while (!killThread) {
		while (!killThread && modChange) {
			modChange = false;
			if (gaps) gapPassTime();
			else normalPassTime();
		}
		if (killThread) break;
		if (!modChange) {
			timerDone = true;
			//system("powershell -c (New-Object Media.SoundPlayer \"C:\\Users\\rm200196d\\source\\repos\\gtimer\\Debug\\sound\\jede.wav\").PlaySync();");
			system("powershell -c (New-Object Media.SoundPlayer \"D:\\my-scripts\\jede.wav\").PlaySync();");
		}
	}
}

void Timer::normalPassTime() {
	timerDone = false;
	while (!killThread && !gaps && timeLeft > 0) {
		if (!paused) --timeLeft;
		if (!updatePaused) {
			for (int i = 0; i < subscribers.size(); subscribers[i++]->update(this));
		}
		//else std::cout << "update paused" << std::endl;
		Sleep(1000);
	}
}

void Timer::gapPassTime() {
	timerDone = false;
	while (!killThread && gaps && timeLeft > 0) {
		if (gapVecIndex < gapsVec.size() && timeLeft <= gapsVec[gapVecIndex]) gapTime();
		if (!paused) --timeLeft;
		if (!updatePaused) {
			for (int i = 0; i < subscribers.size(); subscribers[i++]->update(this));
		}
		//else std::cout << "update paused" << std::endl;
		Sleep(1000);
		if (timeLeft == 0) if (gapVecIndex < gapsVec.size() && timeLeft <= gapsVec[gapVecIndex]) gapTime();
	}
}

void Timer::gapTime() {
	//system("powershell -c (New-Object Media.SoundPlayer \"C:\\Users\\rm200196d\\source\\repos\\gtimer\\Debug\\sound\\jede.wav\").Play(); Start-Sleep -s 3; Exit;");
	system("powershell -c (New-Object Media.SoundPlayer \"D:\\my-scripts\\jede.wav\").Play(); Start-Sleep -s 3; Exit;");
	++gapVecIndex;
	int timeBeforeGap = timeLeft;
	inGap = true;
	timeLeft = 10;
	while (!killThread && gaps && timeLeft > 0) {
		if (!paused) --timeLeft;
		if (!updatePaused) {
			for (int i = 0; i < subscribers.size(); subscribers[i++]->update(this));
		}
		//else std::cout << "update paused" << std::endl;
		Sleep(1000);
	}
	timeLeft = timeBeforeGap;
	inGap = false;  
	if (killThread) return;
	//system("powershell -c (New-Object Media.SoundPlayer \"C:\\Users\\rm200196d\\source\\repos\\gtimer\\Debug\\sound\\jede.wav\").Play(); Start-Sleep -s 2; Exit;");
	system("powershell -c (New-Object Media.SoundPlayer \"D:\\my-scripts\\jede.wav\").Play(); Start-Sleep -s 2; Exit;");
}

void Timer::addSubscriber(Subscriber* newSub) {
	subscribers.push_back(newSub);
}

void Timer::turnGapOn() {
	gaps = true; modChange = true; gapVecIndex = 0;
	double pOfGap = (double)timeLeft * 30 / 3600;

	int numberOfGaps = (int)pOfGap;

	unsigned randNumber = 0; rand_s(&randNumber);
	if ((double)randNumber / UINT_MAX < pOfGap - numberOfGaps) ++numberOfGaps;

	gapsVec.clear();
	for (int i = 0; i < numberOfGaps; ++i) {
		rand_s(&randNumber);
		gapsVec.push_back(randNumber % timeLeft);
	}
	std::sort(gapsVec.begin(), gapsVec.end(), std::greater <>());
}
