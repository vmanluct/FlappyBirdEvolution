#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pipe.h"
#include "NeuralNet.h"

using namespace std;
using namespace sf;
class Bird
{
private:
	void initVariables();
	void initSprite();

	float calcYDistanceToTopPipe();
	float calcYDistanceToBotPipe();
	float calcYDistanceToGround();
	float calcYDistanceToCeiling();
	float calcXDistanceToPipes();

public:

	//Variables for bird's visuals
	Texture birdTexture;
	Sprite birdSprite;
	string path = "images/flappyBird.png";

	//Physical info for the bird
	float y;
	std::pair<int, int> pos;
	float vel;
	bool alive = true;
	Pipe* pipe;

	//Neural Network stuff
	NeuralNet brain;
	float vision[6];
	MatrixXf decision;

	//Variables for how well bird is doing
	int lifeTime;
	int score;
	int fitness;

	Bird();
	FloatRect getRect();

	void mutate(float mr);

	void look();

	void think();

	void Collision();

	void updateMovement();

	void flap();

	void update();

	int calcFitness();

	Bird crossover(Bird partner);

	Bird clone();

	void render(RenderTarget& target);

};

