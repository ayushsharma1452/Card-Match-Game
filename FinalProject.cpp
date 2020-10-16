// FinalProjectTemplage.cpp : Defines the entry point for the application.
//

using namespace std;
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameManager.h"

int main()
{
    FinalProject::GameManager Game;
    Game.Run();
   

    return 0;
}