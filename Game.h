#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Population.h"

using namespace sf;
class Game
{
private:
	//Window
	RenderWindow window;
	VideoMode videoMode;
	Event ev;
	Color sky = Color(135, 206, 250);
	Texture birdTexture;
	Texture bgTexture;
	Sprite bgSprite;

	Population* population;

	void initWindow();

	void initPopulation();

	float prevBestFitness;
	int count;

public:
	Game();
	~Game();

	void updatePopulation();
	void update();
	void renderPopulation();
	void render();
	const RenderWindow& getWindow();
};

