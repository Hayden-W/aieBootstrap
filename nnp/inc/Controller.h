#pragma once

#include <vector>

class NeuralNetwork;

/*
Overload this controller to create controllers for differnt applications, such as 
XOR functions and minesweeper players.
*/

class Controller
{
public:
	Controller(int inputs, int hidden, int output);
	virtual ~Controller();

	bool SaveNeuralNetWeightsToFile(const char* filepath);

	bool LoadNeuralNetWeightsFromFile(const char* filepath);

	virtual void LoadTrainingData() = 0;

	virtual void TrainNN(unsigned int trainingIterations) = 0;

	virtual void TrainNNUntilCorrect() = 0;

	virtual void SelfTrainUntilCorrect() {};

	virtual void TestNN() = 0;

protected:
	std::vector<double>	explode(const char* s);

	NeuralNetwork *m_neuralNetwork;

	std::vector<std::vector<double>> *m_trainingData;
	std::vector<std::vector<double>> *m_resultData;

	int iterations = 0;
	int trainingIterationsBeforeReweight = 5000;
	int trainingDataSize = 0;

	double trainingAccuracy = 0.015;
};