#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Pipe
{
private:
	//Initializers
	void initVariables();
	void initTexture();
	void initSprite();

public:
	//Graphics stuff
	Texture lowerPipe;
	Texture upperPipe;

	Sprite lowerPipeSp;
	Sprite upperPipeSp;

	//Variables for location of pipes
	float x;
	float y;

	//Whether the bird passed the pipe
	bool scored;
	string path = "images/pipe.png";

	Pipe(); //Constructor

	//Hitboxes for pipes
	FloatRect getUpperRect() const;
	FloatRect getLowerRect() const;

	//Draw the pipes to the screen
	void draw(RenderWindow &window);

	//Move pipes across the screen
	void update();

	//Draw the pipes to the screen
	void render(RenderTarget& target);
};

