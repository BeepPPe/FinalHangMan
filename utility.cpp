#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "utility.h"
#include "draw.h"
#include <ctime>
#include <fstream>
#include "mmsystem.h"

using namespace std;

void readAGuess(int curTime, int Score, int best_score)
{
    char guess;
    cout <<"Your Score: ";
    set_color(0*16 + 2);
    cout << Score << endl;
    set_color(0*16 + 7);

    cout <<"High Score: ";
    set_color(0*16 + 2);
    cout << best_score << endl;
    set_color(0*16 + 7);

    cout << "Please enter your next guess (Time left: ";
    set_color(0*16 + 2);
    cout << 10 - curTime << "): ";
    set_color(0*16 +7);



    return;
}


string normalize(const string& s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

string chooseWord(const string& fileName, const int& index)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return "";

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }

    int n = vocabulary.size();
    cout << "vocabulary size = " << n << endl;
    return n > 0 ? vocabulary[index] : "";
}

bool contains(const string& word,const char& guess)
{
    return (word.find(guess) != string::npos);
}

void update(string& guessedWord, const string& word, char guess)
{
    int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
            guessedWord[i] = guess;
    }
}

string ChooseTopic()
{
    clearScreen();
    cout << "Select Your Topics" << endl;
    cout << "1.";
    set_color(0*16 + 2);
    cout<<"Animal";
    set_color(0*16 + 7);
    cout<<"    2.";
    set_color(0*16 + 2);
    cout<<"Food and drinks\n";
    set_color(0*16 + 7);
    cout<<"    3.";
    set_color(0*16 + 2);
    cout<<"1 Life\n";
    set_color(0*16 + 7);
    cout << "Your choice: ";
    int choice1;
    cin >> choice1;
    if (choice1 == 1)
    {
        clearScreen();
        cout <<"Choose Difficulty\n";
        cout <<"1.";
        set_color(0*16 + 2);
        cout<<"Easy    ";
        set_color(0*16 + 7);
        cout<<"2.";
        set_color(0*16 + 2);
        cout<<"Hard\n";
        set_color(0*16 + 7);
        cout << "Your choice: ";
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
            return "WordList/Animal/EASY.txt";
        else if (choice2 == 2)
            return "WordList/Animal/HARD.txt";
        else
        {
            cout <<"\n Invalid Input! Try Again";
            _getch();
            ChooseTopic();
        }
    }
    else if (choice1 == 2)
    {
        clearScreen();
        cout <<"Choose Difficulty\n";
        cout <<"1.";
        set_color(0*16 + 2);
        cout<<"Easy    ";
        set_color(0*16 + 7);
        cout<<"2.";
        set_color(0*16 + 2);
        cout<<"Hard\n";
        set_color(0*16 + 7);
        cout << "Your choice: ";
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
            return "WordList/FoodAndDrink/EASY.txt";
        else if (choice2 == 2)
            return "WordList/FoodAndDrink/HARD.txt";
        else
        {
            set_color(0*16 + 4);
            cout <<"\n Invalid Input! Try Again";
            set_color(0*16 + 7);
            _getch();
            ChooseTopic();
        }
    }
    else if (choice1 == 3)
    {
        return "WordList/1Life.txt";
    }
    else
    {
        set_color(0*16 + 4);
        cout <<"\n Invalid Input! Try Again";
        set_color(0*16 + 7);
            _getch();
            ChooseTopic();
    }

}

int ChooseIndex(const string& fileName)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return -1;

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    int n = vocabulary.size();
    return rand() % n;
}

//Main game
void Game()
{



    int FPS = 3;
    int timePerFrame = 1000/FPS;

    bool is1Life = false;
    string fileName = ChooseTopic();
    if (fileName == "WordList/1Life.txt") is1Life = true;
    string fileHint;
    if (!is1Life)
        fileHint = FileHint(fileName);
    while (true) {
        int index = ChooseIndex(fileName);
        string word = chooseWord(fileName, index);
        string hint;
        if (!is1Life)
            hint = chooseWord(fileHint, index);


        if (word.empty()) {
            cout << "No word available in " << fileName << endl;
            return;
        }
        string guessedWord = string(word.length(), '-');
        int badGuessCount = 0;
        if (is1Life) badGuessCount = 6;
        const int MAX_BAD_GUESS = 7;
        string badGuess;
        bool UseHint;
        if (!is1Life)
            UseHint = false;

        //Time Play
        clock_t startPlaying = clock();

        //Score
        int Score = 0;
        int best_score;
        ofstream output;
        if (fileName == "WordList/Animal/EASY.txt" || fileName == "WordList/FoodAndDrink/EASY.txt")
        {
            ifstream input("ScoreEZ.txt");
            input >> best_score;
            input.close();
            output.open("ScoreEZ.txt");
        }
        else
        {
            ifstream input("ScoreHD.txt");
            input >> best_score;
            input.close();
            output.open("ScoreHD.txt");
        }
        do {
            //Time Guess
            int start = 0;
            clock_t startGuess = clock();

            char guess;
            int timeGuessed = clock() - startGuess;
            bool keep_running = true;
            readAGuess(timeGuessed/1000, Score, best_score);
            while(keep_running) {

                clock_t startFrame = clock();

                if (!_kbhit())
                {
                    timeGuessed = clock() - startGuess;
                    renderGame( badGuessCount, guessedWord, badGuess);
                    if (UseHint)
                        cout << endl << hint <<endl;
                    readAGuess(timeGuessed/1000, Score, best_score);

                    if(timeGuessed/1000 > 9)
                        break;
                }
                else
                {
                    timeGuessed = clock() - startGuess;

                    if(timeGuessed/1000 > 9)
                        break;

                    char tmp = std::cin.get();
                    if ('a' <= tmp && tmp <= 'z' || tmp == '#')
                    {
                        guess = tmp;
                        keep_running = false;
                    }
                }
                //refresh frame
                int frameTime = clock() - startFrame;
                if (timePerFrame > frameTime)
                    Sleep(timePerFrame - frameTime);

            }
            if(timeGuessed/1000 > 9)
            {
                badGuessCount++;
            }
            else
            {
                if (guess == '#')
                {
                    UseHint = true;
                    badGuessCount++;
                }
                else if (contains(word, guess)) {
                    update(guessedWord, word, guess);
                    Score += 10 - timeGuessed/1000;
                } else {
                    badGuessCount++;
                    badGuess += guess;
                }

            }

        } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word);

        //end game
        if(Score > best_score)
            output << Score;
        else output << best_score;


        int timeGuessed = clock() - startPlaying;

        printGameOverInfo(badGuessCount, guessedWord, word, timeGuessed/1000);
        cout <<"\n";
        cout << "Do you want more (Y/N) ?";
        string answer;
        cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
            break;
    }
    ShowMenu();
}

//Load file hints
string FileHint(const string& fileName)
{
    if(fileName == "WordList/Animal/EASY.txt")
        return "WordList/Animal/EASY_HINT.txt";
    else if(fileName == "WordList/Animal/HARD.txt")
        return "WordList/Animal/HARD_HINT.txt";
    else if(fileName == "WordList/FoodAndDrink/EASY.txt")
        return "WordList/FoodAndDrink/EASY_HINT.txt";
    else if(fileName == "WordList/FoodAndDrink/HARD.txt")
        return "WordList/FoodAndDrink/HARD_HINT.txt";
}
