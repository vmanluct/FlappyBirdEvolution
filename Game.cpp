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
	this->population = new Population(50); //Create population of 50 birds
}

void Game::initNNWindow()
{
	this->netMode.height = 500;
	this->netMode.width = 500;
	this->netWindow.create(this->netMode, "Neural Network");
	this->netWindow.setPosition({ 1150,750 });
}

Game::Game()
{
	//Find what the best fitness was before program was closed to use as base
	std::ifstream file("BestBirdDNA/BestBirdFitness.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			file >> this->prevBestFitness;
		}
	}
	//If program was not run before the previous best fitness is 0
	else
		this->prevBestFitness = 0;

	//Load texture for bird
	if (!birdTexture.loadFromFile("images/flappyBird.png")) {
		std::cout << "Could not load file";
	}
	
	//Create game
	this->initWindow();
	this->initPopulation();

	//Apply texture to all bird sprites
	for (int i = 0; i < this->population->popSize; i++) {
		this->population->birds[i].birdTexture = this->birdTexture;
		this->population->birds[i].birdSprite.setTexture(this->birdTexture);
	}
	if (!bgTexture.loadFromFile("images/day.png")) {
		std::cout << "Could not load file";
	}
	bgSprite.setTexture(bgTexture);
	
	//Create window to show Neural Network
	this->initNNWindow();
}

Game::~Game()
{
}

void Game::updatePopulation()
{
	//Adjust positions of all birds if they are alive
	this->population->updateAlive();

	//If the entire population is dead start evolution
	if (this->population->done()) {
		this->population->calculateFitness();

		//If the best fitness of the population is better than the best fitness in file write fitness to file
		if (this->population->globalBestFitness > this->prevBestFitness) {
			this->prevBestFitness = this->population->globalBestFitness;
			std::ofstream file;
			file.open("BestBirdDNA/BestBirdFitness.txt");
			file << this->prevBestFitness;
			file.close();
		}

		//Output generation, and score to terminal
		std::cout << this->population->gen << " Global best fitness is: ";
		std::cout << this->population->globalBestFitness << " ";
		std::cout << " Global best score is " << this->population->globalBest << '\n';
		this->population->naturalSelection();

		//Set texture to bird sprites
		for (int i = 0; i < this->population->popSize; i++) {
			this->population->birds[i].birdTexture = this->birdTexture;
			this->population->birds[i].birdSprite.setTexture(this->birdTexture);
		}
	}
}

void Game::update()
{
	//if (Keyboard::isKeyPressed(Keyboard::A)) this->population->drawAll = true; //If you want to see all the birds at once
	//if (Keyboard::isKeyPressed(Keyboard::S)) this->population->drawAll = false; //If you only want to see the best bird
	if (Keyboard::isKeyPressed(Keyboard::Space)) this->population->birds[0].flap(); //For human play
	
	//If best score from population is better than in file write best DNA to file
	if (this->population->globalBestFitness > this->prevBestFitness) {
		this->population->birds[0].brain.writeRecordToFile("BestBirdDNA/DNA.txt");
	}

	//For the first generation have the first 4 birds be loaded with the best DNA
	if (this->population->gen == 1) {
		for (int i = 0; i < 4; i++) {
			this->population->birds[i].brain.readFiletoNetwork("BestBirdDNA/DNA.txt");
		}
	}

	this->updatePopulation();
}

void Game::renderPopulation()
{
	this->population->render(this->window); //Draw all birds to game screen
	this->population->birds[0].brain.renderNet(this->netWindow); //Draw Neural Net of best bird
}

void Game::render()
{
	//Create both windows and display them
	window.clear(this->sky);
	netWindow.clear();
	this->window.draw(bgSprite);
	this->renderPopulation();
	this->window.display();
	this->netWindow.display();
}

const RenderWindow& Game::getWindow()
{
	return this->window;
}

const RenderWindow& Game::getNNWindow()
{
	return this->netWindow;
}
