#define COLOR_BLACK 40
#define COLOR_WHITE 47
#define _USE_MATH_DEFINES
#include "CircleTimer.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <windows.h>

void gotoxy(int x, int y);

void CircleTimer::draw(int posX, int posY) {
	justUpdated = false;
	double passedPercent = (double) elapsedTime / startTime;
	double elapsedCircleR = sideLength * passedPercent;
	double centerX = posX + sideLength / 2;
	double centerY = posY + sideLength / 2;
	if (empty) {
		empty = false;
		fillCircle(posX, posY, sideLength, sideLength, charEmpty);
	}
	fillCircle(posX, posY, sideLength, elapsedCircleR, charFill);
}

void CircleTimer::fillCircle(int posX, int posY, int sideLength, int radFill, char pChar) {
	justUpdated = false;
	double centerX = posX + sideLength / 2;
	double centerY = posY + sideLength / 2;
	for (int r = radFill; r >= 0; r -= 1) {
		for (double alpha = 0; alpha <= 2 * M_PI; alpha += 0.1) {
			gotoxy(centerX + 2 * r * cos(alpha), centerY + yMultiple * r * sin(alpha));
			std::cout << pChar;

			gotoxy(centerX + xMultiple * r * cos(alpha) - 1, centerY + yMultiple * r * sin(alpha));
			std::cout << pChar;
			gotoxy(centerX + xMultiple * r * cos(alpha), centerY + yMultiple * r * sin(alpha) - 1);
			std::cout << pChar;

			gotoxy(centerX + xMultiple * r * cos(alpha) + 1, centerY + yMultiple * r * sin(alpha));
			std::cout << pChar;
			gotoxy(centerX + xMultiple * r * cos(alpha), centerY + yMultiple * r * sin(alpha) + 1);
			std::cout << pChar;
		}
	}
}
