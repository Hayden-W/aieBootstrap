#include "inc/PatternRecognitionController.h"
#include "inc/NeuralNetwork.h"
#include "imgui.h"
#include <iostream>

PatternRecognitionController::PatternRecognitionController(int inputs, int hidden, int output) :
	Controller(inputs, hidden, output)
{
	trainingIterationsBeforeReweight = 5000;
	iterations = 0;
	m_inputVec.push_back(0.0);
	m_inputVec.push_back(0.0);
	m_inputVec.push_back(0.0);
	m_inputVec.push_back(0.0);
	m_resultVec.push_back(0.0);
	m_resultVec.push_back(0.0);
	m_resultVec.push_back(0.0);
	m_resultVec.push_back(0.0);
}

PatternRecognitionController::~PatternRecognitionController() = default;

void PatternRecognitionController::LoadTrainingData()
{
	std::vector<double> tempTrainingData;
	std::vector<double> tempResultData;
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 2; z++)
				for (int i = 0; i < 2; i++)
				{
					tempTrainingData.push_back(x);
					tempTrainingData.push_back(y);
					tempTrainingData.push_back(z);
					tempTrainingData.push_back(i);
					tempResultData.push_back(x);
					tempResultData.push_back(y);
					tempResultData.push_back(z);
					tempResultData.push_back(i);

					m_trainingData->push_back(tempTrainingData);
					m_resultData->push_back(tempResultData);
					tempTrainingData.clear();
					tempResultData.clear();
				}
}

void PatternRecognitionController::TrainNN(unsigned int trainingIterations)
{
	std::vector<double> resultVec;
	for (unsigned int i = 0; i < trainingIterations; i++)
	{
		for (unsigned int x = 0; x < m_trainingData->size(); x++)
		{
			std::cout << "\nExpected: ";
			for (unsigned int i = 0; i < m_resultData->at(x).size(); i++)
			{
				std::cout << m_resultData->at(x)[i];
				if(i != m_resultData->at(x).size())
				{
					std::cout << ", ";
				}
				else
				{
					std::cout << "."<<std::endl;
				}
			}
			
			resultVec = m_neuralNetwork->Train(m_trainingData->at(x), m_resultData->at(x));
			std::cout << "Result: ";
			for (unsigned int i = 0; i < resultVec.size(); i++)
			{
				std::cout << resultVec[i];
				if (i == resultVec.size() - 1)
				{
					std::cout << "." << std::endl;
				}
				else
				{
					std::cout << ", ";
				}
			}
		}
	}
}

void PatternRecognitionController::TrainNNUntilCorrect()
{
	m_inputVec[0] = (rand() % 100) / 100.f;
	m_inputVec[1] = (rand() % 100) / 100.f;
	m_inputVec[2] = (rand() % 100) / 100.f;
	m_inputVec[3] = (rand() % 100) / 100.f;

	m_resultVec[0] = 1.0f - m_inputVec[0];
	m_resultVec[1] = 1.0f - m_inputVec[1];
	m_resultVec[2] = 1.0f - m_inputVec[2];
	m_resultVec[3] = 1.0f - m_inputVec[3];

	NNResult = m_neuralNetwork->Train(m_inputVec, m_resultVec);

	rollingAccurcacyAvg[rollAvgPos++] = (abs(m_resultVec[0] - NNResult[0]) + abs(m_resultVec[1] - NNResult[1]) 
		+ abs(m_resultVec[2] - NNResult[2]) + abs(m_resultVec[3] - NNResult[3])) / 4; //This is super dirty, but quick!
	
	if (rollAvgPos == 100)
		rollAvgPos = 0;

	trainingAccuracy = 0.0;
	for (int i = 0; i < 100; i++)
	{
		trainingAccuracy += rollingAccurcacyAvg[i];
	}
	trainingAccuracy /= 100;

	#pragma region construct outputStrings
	m_avg = "Average Delta: ";
	m_avg += std::to_string(trainingAccuracy);

	m_outputInput  = std::to_string(m_inputVec[0]);
	m_outputInput += " ";
	m_outputInput += std::to_string(m_inputVec[1]);
	m_outputInput += " ";
	m_outputInput += std::to_string(m_inputVec[2]);
	m_outputInput += " ";
	m_outputInput += std::to_string(m_inputVec[3]);

	m_outputOutput  = std::to_string(m_resultVec[0]);
	m_outputOutput += " ";
	m_outputOutput += std::to_string(m_resultVec[1]);
	m_outputOutput += " ";
	m_outputOutput += std::to_string(m_resultVec[2]);
	m_outputOutput += " ";
	m_outputOutput += std::to_string(m_resultVec[3]);

	m_outputResult  = std::to_string(NNResult[0]);
	m_outputResult += " ";
	m_outputResult += std::to_string(NNResult[1]);
	m_outputResult += " ";
	m_outputResult += std::to_string(NNResult[2]);
	m_outputResult += " ";
	m_outputResult += std::to_string(NNResult[3]);

#pragma endregion

	

	ImGui::Begin("Pattern Training Data");
	ImGui::Text((m_avg + " Avg Delta (Lower is Better)").c_str());
	ImGui::Text(m_outputInput.c_str());
	ImGui::Text(m_outputOutput.c_str());
	ImGui::Text(m_outputResult.c_str());

	ImGui::End();
}

void PatternRecognitionController::TestNN()
{
	ImGui::Begin("Pattern NN Testing");
	ImGui::SliderFloat("1", &i1, 0.0f, 1.0f);
	ImGui::SliderFloat("2", &i2, 0.0f, 1.0f);
	ImGui::SliderFloat("3", &i3, 0.0f, 1.0f);
	ImGui::SliderFloat("4", &i4, 0.0f, 1.0f);

	m_resultVec[0] = (double)i1;
	m_resultVec[1] = (double)i2;
	m_resultVec[2] = (double)i3;
	m_resultVec[3] = (double)i4;

	NNResult = m_neuralNetwork->Test(m_resultVec);

	m_outputResult = std::to_string(NNResult[0]);
	m_outputResult += " ";
	m_outputResult += std::to_string(NNResult[1]);
	m_outputResult += " ";
	m_outputResult += std::to_string(NNResult[2]);
	m_outputResult += " ";
	m_outputResult += std::to_string(NNResult[3]);
	
	ImGui::Text(m_outputResult.c_str());

	ImGui::End();	
}
