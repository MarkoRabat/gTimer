#define _CRT_RAND_S
#include <iostream>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <string>
#include <windows.h>
#include <cmath>
#include "Timer.h"
#include "DigitalClock.h"
#include "CircleTimer.h"
using std::cout;
using std::endl;
using std::cin;

#define MENUPOSX 80
#define MENUPOSY 0

// set cursor position
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

int inputTime() {
	cin >> std::skipws;
	gotoxy(MENUPOSX, MENUPOSY);
	cout << "|=============================|";
	gotoxy(MENUPOSX, MENUPOSY + 1);
	cout << "|===         Timer:        ===|";
	gotoxy(MENUPOSX, MENUPOSY + 2);
	cout << "|=============================|";
	gotoxy(MENUPOSX, MENUPOSY + 3);
	cout << "|-----------------------------|";
	gotoxy(MENUPOSX + 25, MENUPOSY + 4);
	cout << "-----|";
	gotoxy(MENUPOSX + 25, MENUPOSY + 5);
	cout << "-----|";
	gotoxy(MENUPOSX + 25, MENUPOSY + 6);
	cout << "-----|";
	gotoxy(MENUPOSX, MENUPOSY + 7);
	cout << "|-----------------------------|";
	gotoxy(MENUPOSX, MENUPOSY + 8);
	cout << "|--        Commands:        --|";
	gotoxy(MENUPOSX, MENUPOSY + 9);
	cout << "|-- to pause: p             --|";
	gotoxy(MENUPOSX, MENUPOSY + 10);
	cout << "|-- to continue: c          --|";
	gotoxy(MENUPOSX, MENUPOSY + 11);
	cout << "|-- to restart: r           --|";
	gotoxy(MENUPOSX, MENUPOSY + 12);
	cout << "|-- to toggle gaps: g       --|";
	gotoxy(MENUPOSX, MENUPOSY + 13);
	cout << "|-- to quit: q              --|";
	gotoxy(MENUPOSX, MENUPOSY + 14);
	cout << "| (+/a)/(-/s) to add/sub mins |";
	gotoxy(MENUPOSX, MENUPOSY + 4);
	cout << "|Set hour: "; double hours; cin >> hours;
	gotoxy(MENUPOSX, MENUPOSY + 5);
	cout << "|Set minutes: "; double min; cin >> min;
	gotoxy(MENUPOSX, MENUPOSY + 6);
	cout << "|Set seconds: "; double sec; cin >> sec;
	// (x > 0) - (x < 0) = sng
	int secSign = (sec > 0) - (sec < 0);
	sec = abs(sec);
	gotoxy(MENUPOSX, MENUPOSY + 22);
	cout << "|-----------------------------|";
	gotoxy(MENUPOSX, MENUPOSY + 23);
	cout << "|=============================|";
	gotoxy(MENUPOSX, MENUPOSY + 24);
	cout << "|=========== NOGAP ===========|";
	gotoxy(MENUPOSX, MENUPOSY + 25);
	cout << "|=============================|";
	gotoxy(MENUPOSX, MENUPOSY + 26);
	cout << "|-----------------------------|";
	double secProb = sec - (int)sec; unsigned randNumber = 0;
	rand_s(&randNumber); if ((double)randNumber / UINT_MAX < secProb) ++sec;
	return (int) abs(hours * 3600 + min * 60 + sec * secSign);
}

bool killThread = false;
bool userInputRegistered = false;
char c;

void userInput() {
	cin >> std::noskipws;
	while (true) {
		cin >> c;
		if (killThread) { userInputRegistered = false; killThread = false; return; }
		if (c == 'p' || c == 'c' || c == 'r' || c == 'g' || c == 'q' || c == '+' || c =='a' || c == '-' || c == 's') {
			userInputRegistered = true;
			if (c == 'q' || c == 'r') { return; }
			while (userInputRegistered) {
				if (killThread) { userInputRegistered = false; killThread = false; return; }
				Sleep(300);
			}
		}
	}
}

int main() {
	// get number of columns and number of rows
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	while (true) {

		system("cls");
		int time = inputTime();

		DigitalClock dg;
		CircleTimer ct;
		Timer timer(time);
		timer.addSubscriber(&dg);
		timer.addSubscriber(&ct);
		timer.start();

		std::thread userInputThread(&userInput);
		bool breakedByR = false;
		while (!timer.isDone()) {
			if (dg.isJustUpdated())
				dg.draw(14, 2);
			if (ct.isJustUpdated())
				ct.draw(23, 12);
			if (userInputRegistered) {
				if (c == 'p') {
					timer.pause();
					gotoxy(MENUPOSX, MENUPOSY + 16);
					cout << "|-----------------------------|";
					gotoxy(MENUPOSX, MENUPOSY + 17);
					cout << "|=                           =|";
					gotoxy(MENUPOSX, MENUPOSY + 18);
					cout << "|==          PAUSED         ==|";
					gotoxy(MENUPOSX, MENUPOSY + 19);
					cout << "|=                           =|";
					gotoxy(MENUPOSX, MENUPOSY + 20);
					cout << "|-----------------------------|";

				}
				if (c == 'c') {
					timer.resume();
					gotoxy(MENUPOSX, MENUPOSY + 16);
					cout << "                               ";
					gotoxy(MENUPOSX, MENUPOSY + 17);
					cout << "                               ";
					gotoxy(MENUPOSX, MENUPOSY + 18);
					cout << "                               ";
					gotoxy(MENUPOSX, MENUPOSY + 19);
					cout << "                               ";
					gotoxy(MENUPOSX, MENUPOSY + 20);
					cout << "                               ";
				}
				if (c == '+' || c =='a') {
					cin >> std::skipws;
					timer.pauseUpdate();
					gotoxy(43, 22); cout << "||---------------------------||";
					gotoxy(43, 23); cout << "||===========================||";
					gotoxy(69, 24);							  cout << " ==||";
					gotoxy(43, 25); cout << "||===========================||";
					gotoxy(43, 26); cout << "||---------------------------||";
					gotoxy(43, 24); cout << "||== Add(m): ";
					double timeDiff;  cin >> timeDiff; timer.addTime(abs(timeDiff * 60));
					gotoxy(43, 22); cout << "                               ";
					gotoxy(43, 23); cout << "                               ";
					gotoxy(43, 24); cout << "                               ";
					gotoxy(43, 25); cout << "                               ";
					gotoxy(43, 26); cout << "                               ";
					timer.resumeUpdate(); cin >> std::noskipws;
				}
				if (c == '-' || c =='s') {
					cin >> std::skipws;
					timer.pauseUpdate();
					gotoxy(43, 22); cout << "||---------------------------||";
					gotoxy(43, 23); cout << "||===========================||";
					gotoxy(69, 24);							  cout << " ==||";
					gotoxy(43, 25); cout << "||===========================||";
					gotoxy(43, 26); cout << "||---------------------------||";
					gotoxy(43, 24); cout << "||== Sub(m): ";
					double timeDiff;  cin >> timeDiff; timer.addTime(-abs(timeDiff * 60));
					gotoxy(43, 22); cout << "                               ";
					gotoxy(43, 23); cout << "                               ";
					gotoxy(43, 24); cout << "                               ";
					gotoxy(43, 25); cout << "                               ";
					gotoxy(43, 26); cout << "                               ";
					timer.resumeUpdate(); cin >> std::noskipws;
				}
				if (c == 'g') {
					if (timer.isGapSet()) {
						timer.turnGapOff();
						gotoxy(MENUPOSX, MENUPOSY + 22);
						cout << "|-----------------------------|";
						gotoxy(MENUPOSX, MENUPOSY + 23);
						cout << "|=============================|";
						gotoxy(MENUPOSX, MENUPOSY + 24);
						cout << "|=========== NOGAP ===========|";
						gotoxy(MENUPOSX, MENUPOSY + 25);
						cout << "|=============================|";
						gotoxy(MENUPOSX, MENUPOSY + 26);
						cout << "|-----------------------------|";
					}
					else {
						timer.turnGapOn();
						gotoxy(MENUPOSX, MENUPOSY + 22);
						cout << "|-----------------------------|";
						gotoxy(MENUPOSX, MENUPOSY + 23);
						cout << "|=                           =|";
						gotoxy(MENUPOSX, MENUPOSY + 24);
						cout << "|==           GAP           ==|";
						gotoxy(MENUPOSX, MENUPOSY + 25);
						cout << "|=                           =|";
						gotoxy(MENUPOSX, MENUPOSY + 26);
						cout << "|-----------------------------|";
					}
				}
				if (c == 'r') { userInputRegistered = false; userInputThread.join(); breakedByR = true; break; }
				if (c == 'q') {
					system("cls"); userInputThread.join(); return 0;
				}
				userInputRegistered = false;
			}
		}
		if (!breakedByR) { killThread = true; userInputThread.join(); }
	}
	return 0;
}
