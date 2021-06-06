#pragma once
#include "Bird.h"
#include "Pipe.h"


class Population
{

public:
	Bird* birds;
	Pipe* pipes;
	bool drawAll = true;
	int gen = 1;
	int globalBest = 0;
	float globalBestFitness = 0;
	float globalMutationRate = 5;
	int currentBest = 0;
	int currentBestBird = 0;
	int popSize;
	float fitnessSum = 0;

	Bird globalBestBird;

	Population(int size);

	void updateAlive();
	void updatePipe();
	bool done();
	void calculateFitness();
	void naturalSelection();
	Bird selectBird();
	void setBestBird();
	void mutate();
	void setCurrentBest();
	void render(RenderTarget& target);
};

