#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>
#include "draw.h"
#include "utility.h"

using namespace std;




int main(int argc, char* argv[])
{
    PlaySound(TEXT("bg.wav"), NULL, SND_FILENAME | SND_ASYNC);
    srand(time(0));
    ShowMenu();
    return 0;
}
