#include "simpleai.h"

int getUserWordLength()
{
    int wordLength;
    cout << "Enter your word length: ";
    cin >> wordLength;
    return wordLength;
}

void initialize(int& wordLength, string& secretWord,
                int& incorrectGuess, set<char>& previousGuesses,
                bool& stop)
{
    wordLength = getUserWordLength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}

string getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}

bool isGoodMask(char guess, const string& mask, const string& secretWord)
{
    if (mask.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-') {
            if (mask[i] != guess)
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i])
                return false;
        }
    return true;
}

void updateSecretWord(const string& mask, string& secretWord)
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

void update(char guess, const string& mask,
            int& incorrectGuess, set<char>& previousGuesses,
            string& secretWord, bool& stop)
{
    if (!isGoodMask(guess, mask, secretWord))
        throw invalid_argument("mistake entering answer");

    previousGuesses.insert(guess);
    if (isAllDash(mask)) {
        incorrectGuess ++;
        if (incorrectGuess == MAX_GUESSES) stop = true;
    } else {
        updateSecretWord(mask, secretWord);
        if (isAllNotDash(secretWord)) stop = true;
    }
}

void render(int incorrectGuess, const set<char>& previousGuesses,
            const string& secretWord)
{
    clearScreen();
    cout << "Incorrect guess = " << incorrectGuess
         << "   previous guesses = ";
    for (char c : previousGuesses)
        cout << c;
    cout << "   secretWord = " << secretWord << endl;
    cout << getDrawing(incorrectGuess) << endl;
}

void playAnimation(bool isLosing, const string& word)
{
    clearScreen();
    int cnt = 0;
    while (true) {
        if (isLosing)
            cout << "I lost :(. My best word is: " << word << endl;
        else
            cout << "Haha, I win :D. The word is: " << word << endl;
        cout << (isLosing ? getNextHangman() : getNextStandingman());
        this_thread::sleep_for(chrono::milliseconds(500));
        //break the animation
        cnt++;
        if (cnt == 20)
            break;
        clearScreen();
    }
    return;
}

void GameWithAi()
{
    while (true)
    {
        bool giveup = false;

        clearScreen();

        int wordLength;
        string secretWord;
        int incorrectGuess;
        set<char> previousGuesses;
        bool stop;

        initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);

        render(incorrectGuess, previousGuesses, secretWord);
        do {
            char guess = getNextGuess(previousGuesses, secretWord);
            if (guess == 0) {
                cout << "I give up, hang me" << endl;
                giveup = true;
                break;
            }

            do {
                try {
                    string mask = getUserAnswer(guess);
                    update(guess, mask, incorrectGuess, previousGuesses, secretWord, stop);
                    break;
                } catch (invalid_argument e) {
                    cout << "Invalid mask, try again" << endl;
                }
            } while (true);
            render(incorrectGuess, previousGuesses, secretWord);
        } while (!stop);

        ///! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
        ///ong co the sua cho nay de in ra giong nhu game cu cua ong
        if (!giveup)
            playAnimation(incorrectGuess == MAX_GUESSES, secretWord);

        cout <<"\n";
        cout << "Do you want more (Y/N) ?";
        string answer;
        cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
            break;
    }

    ShowMenu();

    return;
}
