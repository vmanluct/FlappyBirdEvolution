#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
class Pipe
{
private:
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Texture lowerPipe;
	Texture upperPipe;

	Sprite lowerPipeSp;
	Sprite upperPipeSp;

	float x;
	float y;
	bool scored;
	string path = "images/pipe.png";

	Pipe();

	FloatRect getUpperRect() const;

	FloatRect getLowerRect() const;

	void draw(RenderWindow &window);

	void update();

	void render(RenderTarget& target);
};

