#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <conio.h>
#include "utility.h"
#include "draw.h"

using namespace std;


string getHangPicture(int badGuessCount)
{

    string picture[] = {"",
"   ------------\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |          |\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",

};

    return picture[badGuessCount];
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif // _WIN32
}

void renderGame(int badGuessCount, string guessedWord, string badGuess)
{
    clearScreen();
    cout << "Current guess = " << guessedWord << endl;
    cout << "You have made bad " << badGuessCount << " guess(es)"
         << (badGuess.empty() ? "" : ": ") << badGuess << endl;
    set_color(0*16 + 6);
    cout << getHangPicture(badGuessCount) << endl;
    set_color(0*16 + 7);
}

const vector<string> HANGED = {
"   ------------\n"
"   |         /\n"
"   |        O\n"
"   |       /|\\\n"
"   |       / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |           \\\n"
"   |            O\n"
"   |           /|\\\n"
"   |           / \\\n"
"   |             \n"
"   |             \n"
"   |             \n"
"   |             \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        "
};

void printGameOverInfo( int badGuessCount, string guessedWord, string word, int TimePlay )
{
    int CountTime = 0;
    renderGame( badGuessCount, guessedWord);
    if (guessedWord != word) {
        int n = 0;
        while (true) {
            clearScreen();
            cout << "Game Over!!! You are hanged" << endl
                 << "The correct word is ";
            set_color(0*16 + 2);
            cout << word << endl;
            set_color(0*16 + 7);
            cout << "Your play time is ";
            set_color(0*16 + 2);
            cout << TimePlay;

            set_color(0*16 + 7);
            cout << " second." << endl;

            set_color(0*16 + 6);
            cout << HANGED[n];
            n = (n+1) % HANGED.size();
            set_color(0*16 + 7);

            //count down
            cout <<endl <<"Wait for " << 10-CountTime <<" second to restart";

            std::this_thread::sleep_for (std::chrono::milliseconds(500));
            CountTime ++;
            if (CountTime > 10)
                break;
        }
        cout << "";

    } else {
        cout << "Congrats!!! You are free. Your play time is " << TimePlay << " second." << endl;
    }
}

void ShowHeader() //the function which shows the header on each screen
{
	clearScreen();
    set_color(0*16 + 6);
	cout<<endl<<"+-----------------------------------------------------------------------------+";
	set_color(0*16 + 2);
	cout<<endl<<"|                         Hangman Game - Le Tuan Anh                          |";
	set_color(0*16 + 6);
	cout<<endl<<"+-----------------------------------------------------------------------------+";
	set_color(0*16 + 7);
	cout<<endl<<endl;

	return;
}

void HowToPlay() //how to play option
{
	ShowHeader();
	cout<<"What...You've never played hangman! Seriously? Sigh...";
	cout<<"\n\nHere's how to play: ";
	cout<<"\n - Try to solve the riddle before your chances run out.";
	cout<<"\n - Type in the letters you wish to guess. Careful! Wrong letters lose chances.";
	cout<<"\n - Your Score is count by the time remaining each guess";
	cout<<"\n - Type in # to use hint.";
	cout<<"\n\n\t\t\t\t    Press any key to go back to main menu...";
	_getch();
	ShowMenu();
}

void ShowMenu() //this is the main menu of the program
{
	char choice; //to store choice
	ShowHeader();
	set_color(0*16 + 6);
	cout<<HANGED[1]<<endl;
	set_color(0*16 + 7);
	cout<<"Select an Option: ";
	cout<<"\n1.";
	set_color(0*16 + 2);
	cout<<" Start Game";
	set_color(0*16 + 7);
	cout<<"\n2.";
    set_color(0*16 + 2);
	cout<<" How to play";
	set_color(0*16 + 7);
	cout<<"\n3.";
	set_color(0*16 + 2);
	cout<<" Exit";
	set_color(0*16 + 7);
	cout<<endl<<"\t\tChoice: ";
	cin >> choice; //Input function returns input values

	if(choice == '1') Game(); //start game
	else if(choice == '2') HowToPlay(); //how to play option
	else if(choice == '3') //exit program
	{
		cout<<"\t\tExited succesfully!";
		_getch();
		exit(0);
	}
	else
	{
		cout<<"\t\tInvalid Input! Try again.";
		_getch();
		ShowMenu();
	}
}
void set_color (const int& code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}


