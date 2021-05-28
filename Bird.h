#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pipe.h"

using namespace std;
using namespace sf;
class Bird
{
public:
	Pipe* pipe;

	Texture birdTexture;
	Sprite birdSprite;
	float y;
	float vel;
	string path = "images/flappyBird.png";
	bool alive = true;

	Bird() {
		if (!birdTexture.loadFromFile(path)) {
			cout << "Error";
		}
		pipe = new Pipe();


		y = 400;
		vel = 0;
	}

	FloatRect getRect();

	void flap();

	void draw(RenderWindow& window);

	void update();

};

