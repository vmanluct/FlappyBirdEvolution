#include "Population.h"

Population::Population(int size)
{
	srand(time(0));

	this->pipes = new Pipe();
	this->popSize = size;
	this->birds = new Bird[size];

	for (int i = 0; i < this->popSize; i++) {
		birds[i] = Bird();
		birds[i].pipe = pipes;
	}
}

void Population::updateAlive()
{
	for (int i = 0; i < this->popSize; i++) {
		if (this->birds[i].alive) {
			this->birds[i].update();
		}
	}
	this->updatePipe();
	this->setCurrentBest();
}

void Population::updatePipe()
{
	this->pipes->update();
	if (this->pipes->x + this->pipes->upperPipe.getSize().x <= 0) {
		delete pipes;
		pipes = new Pipe();
	}
}

bool Population::done()
{
	for (int i = 0; i < this->popSize; i++) {
		if (birds[i].alive) 
			return false;
	}
	return true;
}

void Population::calculateFitness()
{
	for (int i = 0; i < this->popSize; i++) {
		fitnessSum += birds[i].calcFitness();
	}
	std::sort(birds, birds + this->popSize, [](Bird const& a, Bird const& b)->bool
		{return a.fitness > b.fitness;});
	delete pipes;
	pipes = new Pipe();
}

void Population::naturalSelection()
{
	Bird* newBirds = new Bird[this->popSize];
	setBestBird();
	newBirds[0] = globalBestBird.clone();


	for (int i = 0; i < this->popSize; i++) {
		if (i < 5) {
			newBirds[i] = birds[i].clone();
		}
		else {
			Bird parent1 = selectBird();
			Bird parent2 = selectBird();

			Bird child = parent1.crossover(parent2);
			if (rand() % 100 < globalMutationRate) {
				child.mutate(5);
			}
			newBirds[i] = child;
		}
		newBirds[i].pipe = this->pipes;
	}
	fitnessSum = 0;
	birds = newBirds;
	gen += 1;
	currentBest = 1;
}

Bird Population::selectBird()
{
	return birds[rand() % 10];
}

void Population::setBestBird()
{
	int max = 0;
	int maxIndex = 0;
	for (int i = 0; i < this->popSize; i++) {
		if (birds[i].fitness > max) {
			max = birds[i].fitness;
			maxIndex = i;
		}
	}

	if (max >= globalBestFitness) {
		globalBestFitness = max;
		globalBestBird = birds[maxIndex].clone();
	}
}

void Population::mutate()
{
	for (int i = 1; i < this->popSize; i++) {
		birds[i].mutate(globalMutationRate);
	}
}

void Population::setCurrentBest()
{
	if (!done()) {
		float max = 0;
		int maxIndex = 0;
		for (int i = 0; i < this->popSize; i++) {
			if (birds[i].alive && birds[i].score > max) {
				max = birds[i].score;
				maxIndex = i;
			}
		}

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
	if (drawAll) {
		for (int i = 0; i < this->popSize; i++) {
			if (birds[i].alive) {
				birds[i].render(target);
			}
		}
	}
	else
		birds[0].render(target);

	this->pipes->render(target);
}
