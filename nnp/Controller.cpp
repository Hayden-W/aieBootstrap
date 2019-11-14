#include "inc/Controller.h"
#include "inc/NeuralNetwork.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <sstream>
#include <utility>

Controller::Controller(int inputs, int hidden, int output)
{
	m_neuralNetwork = new NeuralNetwork(inputs, hidden, output);
	m_trainingData = new std::vector<std::vector<double>>();
	m_resultData = new std::vector<std::vector<double>>();
}

Controller::~Controller()
{
	delete m_neuralNetwork;
	delete m_trainingData;
	delete m_resultData;
}

bool Controller::SaveNeuralNetWeightsToFile(const char * filepath)
{
	std::vector<double> tempWeights;
	std::ofstream weightDataFile;
	weightDataFile.open(filepath, std::ios::trunc);
	if (weightDataFile.good())
	{
		tempWeights = m_neuralNetwork->GetWeights();
		for (unsigned int i = 0; i < tempWeights.size(); i++)
		{
			weightDataFile << tempWeights[i] << " ";
		}
		weightDataFile << "\n";
	}
	else
	{
		printf(filepath);
		printf("^ Failed to open");
		assert(false);
		weightDataFile.close();
		return false;
	}
	weightDataFile.close();
	return true;
}

bool Controller::LoadNeuralNetWeightsFromFile(const char * filepath)
{
	std::string tempLine;
	std::ifstream weightDataFile;
	weightDataFile.open(filepath);
	if (weightDataFile.good())
	{
		if (std::getline(weightDataFile, tempLine))
		{
			m_neuralNetwork->setWeights(explode(tempLine.c_str()));
			weightDataFile.close();
			return true;
		}
	}
	else
	{
		printf(filepath);
		printf("^ Failed to open");
		assert(false);
		return false;
	}
	weightDataFile.close();
	return true;
}

std::vector<double> Controller::explode(const char* s)
{
	std::vector<double> result;

	std::istringstream stringStream(s);

	char space = ' ';

	for (std::string token; std::getline(stringStream, token, space); )
	{
		result.push_back(std::stod(std::move(token)));
	}

	return result;
}
