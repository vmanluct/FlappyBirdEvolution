#include "Population.h"

Population::Population(int size)
{
	srand(time(0));

	//Initialize game objects
	this->pipes = new Pipe();
	this->popSize = size;
	this->birds = new Bird[size];

	//For all the birds have them have a pointer to the same pipe
	for (int i = 0; i < this->popSize; i++) {
		birds[i] = Bird();
		birds[i].pipe = pipes;
	}
}

void Population::updateAlive()
{
	//Update all birds that are not dead
	for (int i = 0; i < this->popSize; i++) {
		if (this->birds[i].alive) {
			this->birds[i].update();
		}
	}

	//Move the pipe
	this->updatePipe();

	//Set the current best bird
	this->setCurrentBest();
}

void Population::updatePipe()
{
	//Move pipe across screen, if it reaches the end of the screen delete it, and create a new pipe
	this->pipes->update();
	if (this->pipes->x + this->pipes->upperPipe.getSize().x <= 0) {
		delete pipes;
		pipes = new Pipe();
	}
}


bool Population::done()
{
	//Check if all birds are dead, if not return false
	for (int i = 0; i < this->popSize; i++) {
		if (birds[i].alive) 
			return false;
	}
	return true;
}

void Population::calculateFitness()
{
	//Get score of all birds
	for (int i = 0; i < this->popSize; i++) {
		fitnessSum += birds[i].calcFitness(); //Get total sum of all birds scores
	}
	std::sort(birds, birds + this->popSize, [](Bird const& a, Bird const& b)->bool
		{return a.fitness > b.fitness;}); //Sort the birds array in descending order
	
	//Reset pipe at far left of the screen
	delete pipes; 
	pipes = new Pipe();
}

void Population::naturalSelection()
{
	Bird* newBirds = new Bird[this->popSize]; //Create a new array of birds
	setBestBird(); //Find the best bird
	newBirds[0] = globalBestBird.clone(); //Make the best bird in the generation be the first in the new gen 


	//For all the new birds do crossover
	for (int i = 0; i < this->popSize; i++) {
		//Elitism, keep top 5 birds the same
		if (i < 5) {
			newBirds[i] = birds[i].clone();
		}

		//Crossover between birds
		else {
			Bird parent1 = selectBird();
			Bird parent2 = selectBird();

			Bird child = parent1.crossover(parent2);
			
			//5 percent of the population will have mutation as well
			if (rand() % 100 < globalMutationRate) {
				child.mutate(5);
			}
			newBirds[i] = child; //add the new bird to the population
		}
		newBirds[i].pipe = this->pipes; //attach the pipe to all the new birds
	}
	//Reset scores, increase generation, assign birds to the new birds created
	fitnessSum = 0;
	birds = newBirds;
	gen += 1;
	currentBest = 1;
}

Bird Population::selectBird()
{
	//Choose a random bird from the top 10 best
	return birds[rand() % 10];
}

void Population::setBestBird()
{
	int max = 0;
	int maxIndex = 0;
	//Go through all birds, and find the index with the highest fitness
	for (int i = 0; i < this->popSize; i++) {
		if (birds[i].fitness > max) {
			max = birds[i].fitness;
			maxIndex = i;
		}
	}

	//If the score of the best bird is better than all previous fitnesses assign this bird as the best
	if (max >= globalBestFitness) {
		globalBestFitness = max;
		globalBestBird = birds[maxIndex].clone();
	}
}

void Population::mutate()
{
	//Mutate all birds in population
	for (int i = 1; i < this->popSize; i++) {
		birds[i].mutate(globalMutationRate);
	}
}

void Population::setCurrentBest()
{
	//While all birds are not dead
	if (!done()) {
		float max = 0;
		int maxIndex = 0;

		//Find the index of the best bird
		for (int i = 0; i < this->popSize; i++) {
			if (birds[i].alive && birds[i].score > max) {
				max = birds[i].score;
				maxIndex = i;
			}
		}

		//If the best bird is better than the global best adjust all global variables
		if (max > currentBest) {
			currentBest = max;
		}

		if (!birds[currentBestBird].alive ||
			max > birds[currentBestBird].score + 5) {
			currentBestBird = maxIndex;
		}

		if (currentBest >= globalBest) {
			globalBest = currentBest;
		}
	}
}

void Population::render(RenderTarget& target)
{
	//Draw the birds, and pipes to the screen
	if (drawAll) {
		for (int i = 0; i < this->popSize; i++) {
			if (birds[i].alive) {
				birds[i].render(target);
			}
		}
	}
	//Only draw the best bird
	else
		birds[0].render(target);

	//Draw the pipe
	this->pipes->render(target);
}
