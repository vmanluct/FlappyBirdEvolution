#pragma once
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include "MatrixHandler.h"

using namespace Eigen;
using namespace sf;
class NeuralNet
{
public:
	int iNodes; //Number of input nodes
	int hNodes; // Number of hidden nodes
	int oNodes; //Number of outputs nodes

	MatrixHandler whi; //Weight matrix for weights between input and hidden nodes
	MatrixHandler whh; //Weight matrix for weights between hidden nodes and second layer hidden nodes
	MatrixHandler who; //Weight matrix weights between second hidden layer and output nodes;

	//Shapes to draw neural network
	CircleShape inNodes[6]; 
	CircleShape hidNodes[4];
	CircleShape outNodes[2];

	//Points to draw lines between nodes
	sf::Vertex inHidWeights[24][2];
	sf::Vertex hidOutWeights[8][2];
	Color lightBlue = Color(50, 150, 250);


	NeuralNet() {
		//Default Constructor
	}

	/*
		How many input, hidden, and output nodes
	*/
	NeuralNet(int inputs, int hiddenNo, int outputNo) {
		iNodes = inputs;
		oNodes = outputNo;
		hNodes = hiddenNo;

		//Create matrices for each layer of nodes
		whi = MatrixHandler(hNodes, iNodes + 1);

		whh = MatrixHandler(hNodes, hNodes + 1);

		who = MatrixHandler(oNodes, hNodes + 1);

		//Fill all matrices with random values -1 to 1
		whi.randomize();
		whh.randomize();
		who.randomize();
	}
	~NeuralNet(); //Destructor

	void mutate(float mr); //Change weights 

	MatrixXf output(float* inputsArr); //Find the values of the output layer 

	NeuralNet crossover(NeuralNet Partner); //Mix the weights of the two brains

	NeuralNet clone(); //Return a clone of the brain

	//Write and read the brain to a txt file
	bool writeRecordToFile(std::string file_name); 
	bool readFiletoNetwork(std::string file_name);

	//Draw the neuaral network
	void drawInputNodes(); 
	void drawInToHidWeights(RenderTarget& target);
	void drawHiddenNodes();
	void drawHidToOutWeights(RenderTarget& target);
	void drawOutputNodes();
	void renderInNodes(RenderTarget& target);
	void renderHidNodes(RenderTarget& target);
	void renderOutNodes(RenderTarget& target);
	void renderNet(RenderTarget& target);
};

