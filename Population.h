#pragma once
#include "Bird.h"
#include "Pipe.h"


class Population
{

public:

	//Game objects
	Bird* birds; 
	Pipe* pipes;

	bool drawAll = true; //Whether to draw all birds or just one
	int gen = 1;  //Generation number
	int globalBest = 0; //Index of best bird in population
	float globalBestFitness = 0; //Best fitness in population
	float globalMutationRate = 5; //What percent of population will be mutated
	int currentBest = 0; //What the current best score is
	int currentBestBird = 0; //what index the Best bird is at
	int popSize; //How many birds will there be
	float fitnessSum = 0; //Sum of all the fitnesses of all the birds

	Bird globalBestBird; //Copy of the best bird from the generation

	Population(int size); //Constructor

	void updateAlive(); //Update all birds
	void updatePipe(); //Update all pipes
	bool done(); //Check if all birds are dead
	void calculateFitness(); //Get score of each bird
	void naturalSelection(); //Pick birds for parents and reproduction
	Bird selectBird(); //Get a bird to be a parent
	void setBestBird(); //Set which bird is the best and assign to globalBestBird
	void mutate(); //Mutate DNA of bird
	void setCurrentBest(); //Set the best score in the generation
	void render(RenderTarget& target); //Draw all the birds, pipes, and neural network of best bird
};

