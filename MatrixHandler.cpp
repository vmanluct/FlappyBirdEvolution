#include "MatrixHandler.h"

MatrixHandler::~MatrixHandler()
{
	//Set all values of the matrix to 0
	matrix(0, 0);
	rows = 0;
	cols = 0;
}

void MatrixHandler::output()
{
	//Display all values of the 
	for (int i = 0; i < rows;i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << std::to_string(matrix.coeff(i, j)) << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void MatrixHandler::multiply(float n)
{
	//Multiply all values of the matrix with the scalar
	matrix *= n;
}

MatrixHandler MatrixHandler::dot(MatrixHandler n)
{
	//Dot product the two matrices
	MatrixHandler result = MatrixHandler(rows, n.cols);
	result.matrix = matrix * n.matrix;
	return result;
}

void MatrixHandler::randomize()
{
	//Randomize all the values in the matrix
	matrix = MatrixXf::Random(rows, cols);
}

void MatrixHandler::Add(float n)
{
	//Add the scalar to all the values in the matrix
	matrix = matrix.array() + n;
}

MatrixHandler MatrixHandler::add(MatrixHandler n)
{
	//Do matrix addition
	MatrixHandler newMatrix = MatrixHandler(rows, cols);
	newMatrix.matrix = matrix + n.matrix;
	return newMatrix;
}

MatrixHandler MatrixHandler::subtract(MatrixHandler n)
{
	//Matrix subtraction
	MatrixHandler newMatrix = MatrixHandler(rows, cols);
	newMatrix.matrix = matrix - n.matrix;
	return newMatrix;
}

MatrixHandler MatrixHandler::transpose()
{
	//Get the transpose of the matrix
	MatrixHandler n = MatrixHandler(cols, rows);
	n.matrix = matrix.transpose();
	return n;
}

MatrixHandler MatrixHandler::singleColumnMatrixFromArray(float* arr)
{
	//Turn the matrix into a column vector
	int size = 6;//sizeof(arr) / sizeof(arr[0]);
	MatrixHandler n = MatrixHandler(size, 1);
	for (int i = 0; i < size; i++) {
		n.matrix(i, 0) = arr[i];
	}
	return n;
}

void MatrixHandler::fromArray(float* arr)
{
	//Take an array and turn it into a matrix
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix(i, j) = arr[j + i * cols];
		}
	}
}

float* MatrixHandler::toArray()
{
	//Take the matrix and turn it into an array
	float* arr = new float[rows * cols]();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols;j++) {
			arr[j + i * cols] = matrix(i, j);
		}
	}

	return arr;
}

MatrixHandler MatrixHandler::addBias()
{
	//Add a bias neuron to the matrix
	MatrixHandler n = MatrixHandler(rows + 1, 1);
	for (int i = 0; i < rows; i++) {
		n.matrix(i, 0) = matrix(i, 0);
	}
	n.matrix(rows, 0) = 1;
	return n;
}

MatrixHandler MatrixHandler::activate()
{
	//Use activation function for all values in the matrix so they are all between 0 and 1
	MatrixHandler n = MatrixHandler(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols;j++) {
			n.matrix(i, j) = relu(matrix(i, j));
		}
	}
	return n;
}

float MatrixHandler::sigmoid(float x)
{
	//Definition of sigmoid
	float y = 1 / (1 + exp(-x));
	return y;
}

float MatrixHandler::relu(float x)
{
	//Definition of Reul
	if (x > 0)
		return x;
	else return 0;
}


MatrixHandler MatrixHandler::sigmoidDerived()
{
	//Derivative of sigmoid on all values in the matrix
	MatrixHandler n = MatrixHandler(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			n.matrix(i, j) = (matrix(i, j) * (1 - matrix(i, j)));
		}
	}
	return n;
}

MatrixHandler MatrixHandler::removeBottomLayer()
{
	//Take the last neuron out from the layer
	MatrixHandler n = MatrixHandler(rows - 1, cols);
	for (int i = 0; i < n.rows;i++) {
		for (int j = 0; j < cols; j++) {
			n.matrix(i, j) = matrix(i, j);
		}
	}
	return n;
}

void MatrixHandler::mutate(float mutationRate)
{
	//Randomly change the weights in the matrix based on mutation rate
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//Get a number between 0 and 100
			float r = (rand() % 100);
			//Only allow mutation rate percent of weights to be altered
			if (r < mutationRate) {
				matrix(i, j) += rand() / 5;

				//Change weights to either a 1 or a -1
				if (matrix(i, j) > 1) {
					matrix(i, j) = 1;
				}
				if (matrix(i, j) < -1) {
					matrix(i, j) = -1;
				}
			}
		}
	}
}

MatrixHandler MatrixHandler::crossover(MatrixHandler partner)
{
	MatrixHandler child = MatrixHandler(rows, cols);

	//Choose weights from both parents with 50 percent chance for child
	int randC = floor(rand() % cols + 1);
	int randR = floor(rand() % rows + 1);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double r = ((double)rand() / (RAND_MAX));
			if (r < 0.5) {
				child.matrix(i, j) = matrix(i, j);
			}
			else {
				child.matrix(i, j) = partner.matrix(i, j);
			}
		}
	}
	return child;
}

MatrixHandler MatrixHandler::clone()
{
	//Deep copy of current matrix
	MatrixHandler clone = MatrixHandler(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			clone.matrix(i, j) = matrix(i, j);
		}
	}
	return clone;
}
