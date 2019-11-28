#include "../inc/MinesweeperController.h"
#include "../inc/NeuralNetwork.h"
#include "../inc/Minesweeper.h"

#include "imgui.h"
#include "Renderer2D.h"
#include "glm/vec2.hpp"

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

MinesweeperController::MinesweeperController(int gridSize, int mineCount) :
	Controller(((gridSize * gridSize) * 2), ((gridSize * gridSize) * 2),
	(gridSize * gridSize)), 
	m_minesweeperGameSize(gridSize),
	m_numberOfMines(mineCount)
{
	//This game instance will never actually draw to the screen
	MSGameTest = new MinesweeperGame(gridSize, m_numberOfMines, glm::vec2(0,0)); 
	int amountOfNodesInGrid = gridSize * gridSize;

	LoadTrainingDataFromFile();
	for (int i = 0; i < amountOfNodesInGrid; i++)
	{
		tempResultData.push_back(0.0);
	}
}

MinesweeperController::~MinesweeperController()
{
	delete MSGameTest;
}

bool MinesweeperController::LoadTrainingDataFromFile()
{
	std::string tempLine;
	std::vector<double> tempInput;
	std::vector<double> tempResult;
	std::ifstream inputDataFile;

	inputDataFile.open("./bin/NeuralNet/trainingData.txt");
	if (inputDataFile.good())
	{
		while (std::getline(inputDataFile, tempLine))
		{
			tempInput = explode(tempLine.c_str());

			if (std::getline(inputDataFile, tempLine))
			{
				/*
				There should always be a matching set of result data for every bit of input data,
				so this if should always fire, but just in case it doesn't, we wont use the last bit of input data, as it won't have
				any result data, and is therefore useless
				*/
				tempResult = explode(tempLine.c_str());

				m_trainingData->push_back(tempInput);
				m_resultData->push_back(tempResult);

				tempInput.clear();
				tempResult.clear();
			}
		}
	}
	else
	{
		printf("Minesweeper training data file failed to open");
		assert(false); //The file failed to open correctly
		return false;
	}

	return true;
}

void MinesweeperController::LoadTrainingData()
{
}

void MinesweeperController::TrainNNUntilCorrect()
{	
	/*
	May be better to get result data with Train and then check if the data would return a correct square
	*/
	results[currentResultPos] = m_neuralNetwork->TrainAndReturnAvgOutputDelta(m_trainingData->at(currentData), m_resultData->at(currentData));
	result = m_neuralNetwork->Train(m_trainingData->at(currentData), m_resultData->at(currentData));

	Highest = 0.f;
	for (unsigned int i = 0; i < result.size(); i++)
	{
		if (result[i] > Highest)
		{
			HighestPos = i;
			Highest = result[i];
		}
	}

	for (unsigned int i = 0; i < result.size(); i++)
	{
		if (m_resultData->at(currentData)[i] >= 0.9)
		{
			if (HighestPos == i)
			{
				slidingAverage[slidingAveragePos] = 1.f;
				break;
			}
			else
			{
				slidingAverage[slidingAveragePos] = 0.f;
				break;
			}
		}
	}

	if (slidingAveragePos++ == 100)
		slidingAveragePos = 0;

	if (currentResultPos++ == 100)
		currentResultPos = 0;

	if (currentData++ == m_trainingData->size() - 1)
		currentData = 0;

	avgCorrectness = 0;
	resultAvg = 0;
	for (int i = 0; i < 100; i++)
	{
		resultAvg += results[i];
		avgCorrectness += slidingAverage[i];
	}
	avgCorrectness /= 100;
	resultAvg /= 100;
}

void MinesweeperController::SelfTrainUntilCorrect()
{	
	Highest = 0.f;
	HighestPos = 0;

	int tries = 10;
	while(!ValidMoveAvailible(grid) && tries >= 0) {
		MSGameTest->Reset();
		MSGameTest->SimulateTileClickForTraining(rand()% m_minesweeperGameSize, rand() % m_minesweeperGameSize);
		grid = MSGameTest->GetGridForNN();
		--tries;
	}

	adaptedInput = adaptMinesweeperInput(grid);

	GetExpectedResult();

	result = m_neuralNetwork->Train(adaptedInput, tempResultData);
	

	for (unsigned int i = 0; i < result.size(); i++)
	{
		if (Highest < result[i])
		{
			Highest = result[i];
			HighestPos = i;
		}
	}

	x = HighestPos / m_minesweeperGameSize;
	y = (HighestPos % m_minesweeperGameSize); 

	if (slidingAveragePos >= 99)
	{
		slidingAveragePos = 0;
	}

	//Need to add a way for it to move to a new square when there isn't a valid click so that 
	//The sliding average isn't biased when its forced to fail because all the squares have been clicked

	if (grid[x][y]->isMine || grid[x][y]->revealed) //error
	{
		slidingAverage[slidingAveragePos++] = 0.f;
		
		if (grid[x][y]->isMine)
		{
			amountMinesSelfTrain++;
		}
		else
		{
			amountRevealedSelfTrain++;
		}

		MSGameTest->Reset();
		grid = MSGameTest->GetGridForNN();
	}
	else
	{
		amountCorrectSelfTrain++;
		slidingAverage[slidingAveragePos++] = 1.f;
		grid = MSGameTest->SimulateTileClickForTraining(x, y); //This is for testing a better solving algorithm
		//MSGameTest->Reset();
		//grid = MSGameTest->GetGridForNN();
	}

	avgCorrectness = 0;
	for (int i = 0; i < 100; i++)
	{
		avgCorrectness += slidingAverage[i];
	}
	avgCorrectness /= 100;
}

void MinesweeperController::Update(float deltaTime)
{
	if (trainingNetwork)
	{
		SelfTrainUntilCorrect();

		ImGui::Begin("Minesweeper NeuralNetwork Training");

		ImGui::Text((std::to_string(avgCorrectness) + " Accuracy (Higher is Better)").c_str());
		ImGui::Text((std::to_string(amountCorrectSelfTrain) + " Amount of Correct Clicks").c_str());
		ImGui::Text((std::to_string(amountRevealedSelfTrain) + " Amount of Revealed Clicks").c_str());
		ImGui::Text((std::to_string(amountMinesSelfTrain) + " Amount of Mine Clicks").c_str());

		if (ImGui::Button("Reweight NN"))
		{
			m_neuralNetwork->reweightNN();
			amountCorrectSelfTrain = 0;
			amountRevealedSelfTrain = 0;
			amountMinesSelfTrain = 0;
		}
		ImGui::End();
	}
	
	if (testingNetwork)
	{
		TestNN();

		ImGui::Begin("Minesweeper NeuralNetwork Testing");

		ImGui::Text(std::to_string(avgCorrectness).c_str());

		if (ImGui::Button("End Testing"))
		{
			testingNetwork = false;
			MSGameTest->SetIsTesting(false);
		}
		ImGui::End();
	}


}

void MinesweeperController::Draw(aie::Renderer2D* renderer)
{

}

std::vector<double> MinesweeperController::GetNNSelection(std::vector<std::vector<MinesweeperNode*>> input)
{
	/*grid = input;
	GetExpectedResult();
	return tempResultData;*/
	//^ That returns what the "perfect" move is in the situation

	return m_neuralNetwork->Test(adaptMinesweeperInput(input));
}

void MinesweeperController::TestNN()
{
	if (slidingAveragePos >= 99)
	{
		slidingAveragePos = 0;
	}

	Highest = 0.f;
	MSGameTest->Reset();
	grid = MSGameTest->GetGridForNN();
	result = m_neuralNetwork->Test(adaptMinesweeperInput(grid));

	for (unsigned int i = 0; i < result.size(); i++)
	{
		if (Highest < result[i])
		{
			Highest = result[i];
			HighestPos = i;
		}
	}

	int x = HighestPos / m_minesweeperGameSize;
	int y = (HighestPos % m_minesweeperGameSize);


	if (grid[x][y]->isMine || grid[x][y]->revealed)
	{
		slidingAverage[slidingAveragePos++] = 0.f;
	}
	else
	{
		slidingAverage[slidingAveragePos++] = 1.f;
	}

	avgCorrectness = 0;
	for (int i = 0; i < 100; i++)
	{
		avgCorrectness += slidingAverage[i];
	}
	avgCorrectness /= 100;
}

void MinesweeperController::GetExpectedResult()
{
	tempResultDataPos = 0;
	for (int u = 0; u < m_minesweeperGameSize; u++)
	{
		for (int z = 0; z < m_minesweeperGameSize; z++)
		{
			if (grid[u][z]->revealed)
			{
				//Dont click on revealed tiles!
				tempResultData[tempResultDataPos++] = 0.0;
				continue;
			}
			else
			{
				if (grid[u][z]->isMine)
				{
					//Don't click on unrevealed mines!
					tempResultData[tempResultDataPos++] = 0.0;
					continue;
				}
			}
			//Set all unrevealed, non-mine tiles to a value of 0, and increase it if there are
			//revealed tiles around it
			tempResultData[tempResultDataPos] = 0.0;
			for (unsigned int i = 0; i < grid[u][z]->surroundingNodes.size(); i++)
			{
				if (grid[u][z]->surroundingNodes[i]->revealed)
				{
					//There is a revealed mine next to this unrevealed Mine
					tempResultData[tempResultDataPos] += 0.166; //There can be a max of 6 reveald tiles around a node, 1 / 6 = .16
				}
			}
			tempResultDataPos++;
		}
	}
}

std::vector<double> MinesweeperController::GetSolution(std::vector<std::vector<MinesweeperNode*>> input)
{
	/*
	TODO:
	Using the logic in the essay in 'documents', create a solver that solves the input, returning probability of a mine being in a location
	*/
	

	std::vector<double> tempVec(m_minesweeperGameSize * m_minesweeperGameSize);

	for (unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			input[x][y]->marked = false;
			input[x][y]->safeToReveal = false;
		}

	for(unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			if (input[x][y]->revealed)
			{
				MarkSquares(input[x][y]);
			}
		}


	for (unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			if (input[x][y]->revealed)
			{
				RevealSquares(input[x][y]);
			}
		}

	int vecPos = 0;
	for (unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			if (input[x][y]->safeToReveal && !input[x][y]->isMine && !input[x][y]->revealed)
			{
				tempVec[vecPos++] = 1.0;
			}
			else
			{
				tempVec[vecPos++] = 0.0;
			}
		}

	return tempVec;
}

std::vector<double> MinesweeperController::adaptMinesweeperInput(std::vector<std::vector<MinesweeperNode*>> input)
{
	std::vector<double> adaptedInput;
	for(unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			adaptedInput.push_back((double)input[x][y]->revealed);
			if (input[x][y]->revealed)
			{
				adaptedInput.push_back((input[x][y]->value / 10.0));
			}
			else
			{
				adaptedInput.push_back((0.f)); //Try this as 0, and see if that helsps
			}
				
		}
	return adaptedInput;
}

std::vector<double> MinesweeperController::explode(const char* s)
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

void MinesweeperController::RevealSquares(MinesweeperNode * input)
{
	//Check to make sure that the amount of mines marked around this tile are equal to its value
	int count = 0;
	for (unsigned int i = 0; i < input->surroundingNodes.size(); i++) //If the the amount of marked tiles around this tile are enough										
	{														//To account for the value of this tile, reveal the non marked ones
		if (input->surroundingNodes[i]->marked)
			count++;
	}

	if (count == input->value)
	{
		for (unsigned int i = 0; i < input->surroundingNodes.size(); i++)
		{
			if (!input->surroundingNodes[i]->marked)
			{
				input->surroundingNodes[i]->safeToReveal = true;
			}
		}
	}
}

bool MinesweeperController::ValidMoveAvailible(std::vector<std::vector<MinesweeperNode*>> input)
{
	for(unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			if (!input[x][y]->revealed && !input[x][y]->isMine)
				return true;
		}
	return false;
}

void MinesweeperController::MarkSquares(MinesweeperNode* input)
{
	int count = 0;

	for (unsigned int i = 0; i < input->surroundingNodes.size(); i++)
	{
		if (!input->surroundingNodes[i]->revealed)
			count++;
	}
	if (count == input->value)
	{
		for (unsigned int i = 0; i < input->surroundingNodes.size(); i++)
		{
			if (!input->surroundingNodes[i]->revealed)
			{
				input->surroundingNodes[i]->marked = true;
			}
		}
	}
}
