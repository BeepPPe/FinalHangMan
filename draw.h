#ifndef __DRAW_H__
#define __DRAW_H__

#include <string>
#include <windows.h>
std::string getHangPicture(int badGuessCount);
void clearScreen();
void renderGame( int badGuessCount, std::string guessedWord, std::string badGuess = "");
void printGameOverInfo( int badGuessCount, std::string guessedWord, std::string word, int TimePlay);
void ShowHeader();
void ShowMenu();
void HowToPlay();
void set_color (const int& code );

///simple ai
std::string getDrawing(int incorrectGuess);
std::string getNextHangman();
std::string getNextStandingman();

#endif // __DRAW_H__

