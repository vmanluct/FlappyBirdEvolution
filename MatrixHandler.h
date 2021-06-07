#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <math.h>

using namespace::Eigen;

class MatrixHandler
{
public:
	//Shape for the matrix
	int rows;
	int cols;

	//Matrix with all the values
	Eigen::MatrixXf matrix;

	MatrixHandler() {
		//Default constructor
	}

	//Constructor
	MatrixHandler(int r, int c) {
		rows = r;
		cols = c;

		//Fill matrix with 0's
		matrix = MatrixXf::Constant(rows, cols, 0);
	}

	//Constructor to create matrix based on another matrix
	MatrixHandler(MatrixXf m) {
		matrix = m;
		rows = m.rows();
		cols = m.cols();
	}

	//Destructor
	~MatrixHandler();

	//Write the values in the matrix
	void output();

	//Scalar multiplication
	void multiply(float n);

	//Dot product
	MatrixHandler dot(MatrixHandler n);

	//Randomize values in matrix
	void randomize();

	//Scalar add
	void Add(float n);

	//Add two matrices
	MatrixHandler add(MatrixHandler n);

	//Subtract two matrices
	MatrixHandler subtract(MatrixHandler n);

	//Get the transpose of the matrix
	MatrixHandler transpose();

	//Turn matrix into a column vector
	MatrixHandler singleColumnMatrixFromArray(float* array);

	//Take an array and turn into a matrix
	void fromArray(float* arr);

	//Turn matrix into an array
	float* toArray();

	//Include bias weight
	MatrixHandler addBias();

	//Use activation function to set value between 0 and 1
	MatrixHandler activate();

	//Activation functions
	float sigmoid(float x);
	float relu(float x);


	MatrixHandler sigmoidDerived();

	//Remove last neuron from each layer
	MatrixHandler removeBottomLayer();

	//Adjust weights randomly based on mutation rate
	void mutate(float mutationRate);

	//Pick weights between matrix and its partner
	MatrixHandler crossover(MatrixHandler partner);

	//Return a deep copy of the matrix
	MatrixHandler clone();
};


