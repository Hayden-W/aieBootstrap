#pragma once

#include <vector>


class NeuralNetwork
{
public:
	NeuralNetwork(int I_N, int H_N, int O_N);

	/*
	Train is used when you have input AND expected output data, the network will test with
	the input data, and then using the expected result it will check its result against the
	expected result, and step towards the expected result using gradient decent
	*/
	std::vector<double> Train(std::vector<double>inputData, std::vector<double> resultData);

	/*
	SelfTrain is used when you don't have result data, basically, you test the network using 
	input data, then you check if the result was correct or not, then you pass that input data 
	into self train with a boolean value representing whether it got a correct answer or not,
	if it did, the neural will step towards that answer, if not, it will step away.
	This method is not as fast as supervised learning, but it does work.
	*/
	void SelfTrain(std::vector<double>inputData, bool correct);

	std::vector<double> Test(std::vector<double>inputData);

	double TrainAndReturnAvgOutputDelta(std::vector<double>inputData, std::vector<double> resultData);

	std::vector<double> GetWeights();

	void setWeights(std::vector<double> newWeights);

	void reweightNN();

private:
	double Sigmoid(double input);

	void AssignWeights();
private:

	std::vector<double> m_hiddenLayerResult;
	std::vector<double> m_outputLayerResult;
	std::vector<double> m_weights;

	std::vector<double> m_hiddenLayerSum;
	std::vector<double> m_outputLayerSum;
	std::vector<double> m_outputNodeError;

	std::vector<double> m_hiddenLayerDerivative;
	std::vector<double> m_outputLayerDerivative;
	std::vector<double> m_gradients;

	std::vector<double> m_weightUpdate;
	std::vector<double> m_previousWeightUpdate;

	int m_inputNodeCount;
	int m_hiddenNodeCount;
	int m_outputNodeCount;

	int m_weightCount = 0;
	int m_currentGradient = 0;
	int m_currentWeight = 0;

	double m_learningRate = 1.414213562;
	double m_momentum = 0.25;
	double m_bias = 1.0;
	double m_errorPercent = 0.0;
};