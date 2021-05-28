#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bird.h"
#include "Pipe.h"

using namespace std; 
using namespace sf;

int main() {
	srand(time(0));

	RenderWindow window(VideoMode(450, 700), "Flappy Bird!");

	Bird bird = Bird();
	Color sky = Color(135, 206, 250);
	Clock clk;

	float timer = 0, delay = 0.1;


	while (window.isOpen()) {
		float time = clk.getElapsedTime().asSeconds();
		clk.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (timer > delay) {

			window.clear(sky);

			if (Keyboard::isKeyPressed(Keyboard::Space)) bird.flap();

			bird.update();

			bird.draw(window);

			window.display();

			timer = 0;
		}
	}
}