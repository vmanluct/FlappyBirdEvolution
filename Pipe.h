#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Pipe
{
public:
	Texture lowerPipe;
	Texture upperPipe;

	Sprite lowerPipeSp;
	Sprite upperPipeSp;

	float x;
	float y;
	bool scored;
	string path = "images/pipe.png";

	Pipe() {
		Image pipeImage;
		if (!pipeImage.loadFromFile(path)) {
			cout << "Error";
		}
		upperPipe.loadFromImage(pipeImage);
		pipeImage.flipVertically();
		lowerPipe.loadFromImage(pipeImage);

		x = (float)(450 + upperPipe.getSize().x);
		y = 100.0f + (float)(rand() % 5 - 3) * 50;
		scored = false;
	}

	FloatRect getUpperRect() const;

	FloatRect getLowerRect() const;

	void draw(RenderWindow &window);

	void update();
};

