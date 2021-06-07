#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Population.h"

using namespace sf;
class Game
{
private:
	//Game Graphics
	RenderWindow window;
	VideoMode videoMode;
	Event ev;
	Color sky = Color(135, 206, 250);
	Texture birdTexture;
	Texture bgTexture;
	Sprite bgSprite;

	Population* population; //All the birds for evolution

	void initWindow(); //Create window for game
	void initPopulation(); //Add birds to population

	//Neural network stuff
	float prevBestFitness;
	int count;

	//Neural Network Graphics
	RenderWindow netWindow;
	VideoMode netMode;
	Event netEv;

	void initNNWindow(); //Create window to show neural network

public:
	Game(); //Constructor
	~Game(); //Destrucotr

	void updatePopulation(); //Update positions of birds, and pipes
	void update(); //Update everything in the windows
	void renderPopulation(); //Draw all game info to window
	void render(); //Draw the game, and neural network

	//Getter function
	const RenderWindow& getWindow(); 
	const RenderWindow& getNNWindow();
};

