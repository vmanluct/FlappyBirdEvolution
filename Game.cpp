#include "Game.h"

void Game::initWindow()
{
	this->videoMode.height = 700;
	this->videoMode.width = 450;
	this->window.create(this->videoMode, "Flappy Bird!");
	this->window.setFramerateLimit(20);
}

void Game::initPopulation()
{
	this->population = new Population(50);
}

Game::Game()
{
	std::ifstream file("BestBirdDNA/BestBirdFitness.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			file >> this->prevBestFitness;
		}
	}
	else
		this->prevBestFitness = 0;

	if (!birdTexture.loadFromFile("images/flappyBird.png")) {
		std::cout << "Could not load file";
	}
	
	this->initWindow();
	this->initPopulation();
	for (int i = 0; i < this->population->popSize; i++) {
		this->population->birds[i].birdTexture = this->birdTexture;
		this->population->birds[i].birdSprite.setTexture(this->birdTexture);
	}
	if (!bgTexture.loadFromFile("images/day.png")) {
		std::cout << "Could not load file";
	}
	bgSprite.setTexture(bgTexture);
}

Game::~Game()
{
}

void Game::updatePopulation()
{
	this->population->updateAlive();
	if (this->population->done()) {
		this->population->calculateFitness();
		if (this->population->globalBestFitness > this->prevBestFitness) {
			this->prevBestFitness = this->population->globalBestFitness;
			std::ofstream file;
			file.open("BestBirdDNA/BestBirdFitness.txt");
			file << this->prevBestFitness;
			file.close();
		}
		std::cout << this->population->gen << " Global best fitness is: ";
		std::cout << this->population->globalBestFitness << " ";
		std::cout << " Global best score is " << this->population->globalBest << '\n';
		this->population->naturalSelection();
		for (int i = 0; i < this->population->popSize; i++) {
			this->population->birds[i].birdTexture = this->birdTexture;
			this->population->birds[i].birdSprite.setTexture(this->birdTexture);
		}
	}
}

void Game::update()
{
	if (Keyboard::isKeyPressed(Keyboard::A)) this->population->drawAll = true;
	if (Keyboard::isKeyPressed(Keyboard::S)) this->population->drawAll = false;
	if (Keyboard::isKeyPressed(Keyboard::Space)) this->population->birds[0].flap();

	if (this->population->globalBestFitness > this->prevBestFitness) {
		this->population->birds[0].brain.writeRecordToFile("BestBirdDNA/DNA.txt");
	}


	if (this->population->gen == 1) {
		for (int i = 0; i < 4; i++) {
			this->population->birds[i].brain.readFiletoNetwork("BestBirdDNA/DNA.txt");
		}
	}

	this->updatePopulation();
}

void Game::renderPopulation()
{
	this->population->render(this->window);
}

void Game::render()
{
	window.clear(this->sky);
	this->window.draw(bgSprite);
	this->renderPopulation();
	this->window.display();
}

const RenderWindow& Game::getWindow()
{
	return this->window;
}
