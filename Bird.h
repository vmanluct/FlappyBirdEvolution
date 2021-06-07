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
	//Initializers
	void initVariables();
	void initSprite();

	//Vision for the bird
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

	Bird(); //Constructor
	FloatRect getRect(); //Hitbox

	void mutate(float mr); //Mutate the brain of the bird

	void look(); //Calculate all the different things the bird can see

	void think(); //Think about what move to do

	void Collision(); //Check if bird hit pipes, ceiling, or floor

	void updateMovement(); //Move bird up and down

	void flap(); //Apply upward velocity to the bird

	void update(); //Update everything about the bird

	int calcFitness(); //Check how well the bird is doing

	Bird crossover(Bird partner); //Breed two birds to create a child

	Bird clone(); //Return a copy of the bird
	
	void render(RenderTarget& target); //Draw the bird to the screen

};

