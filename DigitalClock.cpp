#include "DigitalClock.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <windows.h>

void gotoxy(int x, int y);

void DigitalClock::draw(int posX, int posY) {
	gotoxy(posX, posY);
	int min = currTime / 60;
	int hours = min / 60;
	min -= hours * 60;
	int sec = currTime - hours * 3600 - min * 60;
	hours %= 24;
	drawDigit(posX, posY, hours / 10);
	drawDigit(posX + 3, posY, hours % 10);
	drawSep(posX + 6, posY);
	drawDigit(posX + 9, posY, min / 10);
	drawDigit(posX + 12, posY, min % 10);
	drawSep(posX + 15, posY);
	drawDigit(posX + 18, posY, sec / 10);
	drawDigit(posX + 21, posY, sec % 10);
	justUpdated = false;
}

void DigitalClock::drawDigit(int posX, int posY, int digit) {
	switch (digit) {
	case 0: drawDigit0(posX, posY); break;
	case 1: drawDigit1(posX, posY); break;
	case 2: drawDigit2(posX, posY); break;
	case 3: drawDigit3(posX, posY); break;
	case 4: drawDigit4(posX, posY); break;
	case 5: drawDigit5(posX, posY); break;
	case 6: drawDigit6(posX, posY); break;
	case 7: drawDigit7(posX, posY); break;
	case 8: drawDigit8(posX, posY); break;
	case 9: drawDigit9(posX, posY); break;
	default: break;
	}
}

void DigitalClock::drawSep(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << "   " << std::endl;
	gotoxy(posX, posY + 1); std::cout << " . " << std::endl;
	gotoxy(posX, posY + 2); std::cout << " . " << std::endl;

}

void DigitalClock::drawDigit0(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "| |" << std::endl;
	gotoxy(posX, posY + 2); std::cout << "|_|" << std::endl;
}

void DigitalClock::drawDigit1(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << "   " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "  |" << std::endl;
	gotoxy(posX, posY + 2); std::cout << "  |" << std::endl;
}

void DigitalClock::drawDigit2(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << " _|" << std::endl;
	gotoxy(posX, posY + 2); std::cout << "|_ " << std::endl;
}

void DigitalClock::drawDigit3(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << " _|" << std::endl;
	gotoxy(posX, posY + 2); std::cout << " _|" << std::endl;
}

void DigitalClock::drawDigit4(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << "   " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "|_|" << std::endl;
	gotoxy(posX, posY + 2); std::cout << "  |" << std::endl;
}

void DigitalClock::drawDigit5(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "|_ " << std::endl;
	gotoxy(posX, posY + 2); std::cout << " _|" << std::endl;
}

void DigitalClock::drawDigit6(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "|_ " << std::endl;
	gotoxy(posX, posY + 2); std::cout << "|_|" << std::endl;
}

void DigitalClock::drawDigit7(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << "__ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "  |" << std::endl;
	gotoxy(posX, posY + 2); std::cout << "  |" << std::endl;
}

void DigitalClock::drawDigit8(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "|_|" << std::endl;
	gotoxy(posX, posY + 2); std::cout << "|_|" << std::endl;
}

void DigitalClock::drawDigit9(int posX, int posY) {
	gotoxy(posX, posY);     std::cout << " _ " << std::endl;
	gotoxy(posX, posY + 1); std::cout << "|_|" << std::endl;
	gotoxy(posX, posY + 2); std::cout << " _|" << std::endl;
}

