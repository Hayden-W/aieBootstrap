#include "inc/XORController.h"
#include "inc/NeuralNetwork.h"
#include "imgui.h"

#include <iostream>
#include <string>

XORController::XORController(int inputs, int hidden, int output) : Controller(inputs, hidden, output)
{
	InputVec.push_back(0.0);
	InputVec.push_back(0.0);
	OutputVec.push_back(0.0);
}

XORController::~XORController() = default;


void XORController::LoadTrainingData()
{
	std::vector<double> temmTrainingData;
	std::vector<double> temmResultData;
	temmTrainingData.push_back(0.0);
	temmTrainingData.push_back(0.0);
	temmResultData.push_back(0.0);
	
	temmTrainingData[0] = 1.0;
	temmTrainingData[1] = 0.0;
	m_trainingData->push_back(temmTrainingData);

	temmResultData[0] = 1.0;
	m_resultData->push_back(temmResultData);

	temmTrainingData[0] = 1.0;
	temmTrainingData[1] = 1.0;
	m_trainingData->push_back(temmTrainingData);

	temmResultData[0] = 0.0;
	m_resultData->push_back(temmResultData);

	temmTrainingData[0] = 0.0;
	temmTrainingData[1] = 1.0;
	m_trainingData->push_back(temmTrainingData);

	temmResultData[0] = 1.0;
	m_resultData->push_back(temmResultData);

	temmTrainingData[0] = 0.0;
	temmTrainingData[1] = 0.0;
	m_trainingData->push_back(temmTrainingData);

	temmResultData[0] = 0.0;
	m_resultData->push_back(temmResultData);
	
}

void XORController::TrainNN(unsigned int trainingIterations)
{
	for (unsigned int i = 0; i < trainingIterations; i++)
	{
		for (unsigned int x = 0; x < m_trainingData->size(); x++)
		{
			std::cout << "\nExpected: "<< m_resultData->at(x)[0] << std::endl;
			double xyz = m_neuralNetwork->Train(m_trainingData->at(x), m_resultData->at(x))[0];
			std::cout<<"Result: "<< xyz <<std::endl;
		}
	}
}

void XORController::TrainNNUntilCorrect()
{
	double input1 = rand() % 100 / 100.0;
	double input2 = rand() % 100 / 100.0;
	
	InputVec[0] = input1;
	InputVec[1] = input2;

	if (!(InputVec[0] > 0.5) != !(InputVec[1] > 0.5))
	{
		OutputVec[0] = 1.0;
	}
	else
	{
		OutputVec[0] = 0.0;
	}

	result = m_neuralNetwork->Train(InputVec, OutputVec)[0];

	rollingAccuracyAvg[accAvgPos++] = abs(result - OutputVec[0]);

	if (accAvgPos == 100)
		accAvgPos = 0;

	AvgAccuracy = 0.0;
	for (int i = 0; i < 100; i++)
	{
		AvgAccuracy += rollingAccuracyAvg[i];
	}
	AvgAccuracy /= 100;

	output = input1;
	output += " ";
	output += input2;

	ImGui::Begin("XOR Training");

	ImGui::Text((std::to_string(AvgAccuracy) + " Delta (Lower is Better)").c_str());
	ImGui::Text(output.c_str());

	ImGui::End();
}

void XORController::SelfTrain()
{
	bool keepTesting = true;

	std::vector<double> cost;
	for (unsigned int i = 0; i < m_trainingData->size(); i++)
	{
		cost.push_back(0.0);
	}

	do
	{
		if (iterations++ < trainingIterationsBeforeReweight)
		{
			for (unsigned int x = 0; x < m_trainingData->size(); x++)
			{
				double xyz = m_neuralNetwork->Test(m_trainingData->at(x))[0];

				if (abs(xyz - m_resultData->at(x)[0]) < 0.5) //If the answer is leaning towards being correct, reinforce it
				{
					m_neuralNetwork->SelfTrain(m_trainingData->at(x), true);
				}
				else
				{
					m_neuralNetwork->SelfTrain(m_trainingData->at(x), false);
				}

				cost[x] = abs(xyz - m_resultData->at(x)[0]);
			}

			for (unsigned int y = 0; y < cost.size(); y++)
			{
				if (cost[y] > trainingAccuracy)
				{
					keepTesting = true;
					break;
				}
				keepTesting = false;
			}
		}
		else
		{ //Too many iterations, reweight network and try again
			m_neuralNetwork->reweightNN();
			iterations = 0;
		}
	} while (keepTesting);
}

void XORController::TestNN()
{
	ImGui::Begin("XOR Testing");
	ImGui::SliderFloat("Number 1", &input1, 0.f, 1.f);
	ImGui::SliderFloat("Number 2", &input2, 0.f, 1.f);

	std::vector<double> temp;
	temp.push_back(input1);
	temp.push_back(input2);

	temp = m_neuralNetwork->Test(temp);
	
	ImGui::Text(std::to_string(temp[0]).c_str());
	ImGui::End();
}
