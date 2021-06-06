#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

using namespace std; 
using namespace sf;

int main() {
	Game game;

	while (game.getWindow().isOpen()) {
		game.update();
		game.render();
	}

	return 0;
}