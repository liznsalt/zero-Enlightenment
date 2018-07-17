#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <time.h>
#include "Game.h"
#include "Power.h"
using namespace sf;
using namespace std;


int main()
{
	srand((int)time(0));

	Game game;
	game.run();
	return 0;
}