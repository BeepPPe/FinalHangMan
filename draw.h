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

#endif // __DRAW_H__

