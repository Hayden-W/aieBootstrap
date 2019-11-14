#include "../inc/Minesweeper.h"
#include "../inc/MinesweeperController.h"
#include "Texture.h"
#include "Renderer2D.h"
#include "Input.h"
#include "imgui.h"


#include <iostream>
#include <fstream>
#include <random>
#include <assert.h>


#pragma region Nodes
MinesweeperNode::MinesweeperNode(int x, int y)
{
	revealed = false;
	mineAllowed = true;
	isMine = false;
	isPressed = false;

	xPos = x;
	yPos = y;
	value = 0;
}

MinesweeperNode::~MinesweeperNode()
{
}

bool MinesweeperNode::Reveal()
{
	revealed = true;

	if (value == 0 && !isMine)
	{
		for (unsigned int i = 0; i < surroundingNodes.size(); i++)
		{
			if (!surroundingNodes[i]->revealed && !surroundingNodes[i]->isMine)
				surroundingNodes[i]->Reveal();
		}
	}

	if (isMine)
	{
		return true;
	}

	return false;
}

void MinesweeperNode::firstTile()
{
	mineAllowed = false;
	for (unsigned int i = 0; i < surroundingNodes.size(); i++)
	{
		surroundingNodes[i]->mineAllowed = false;
	}
}
#pragma endregion

#pragma region Game

MinesweeperGame::MinesweeperGame(int gridSize, int mineCount, glm::vec2 center) :
	gridSize(gridSize), maxMines(mineCount), screenPos(center)
{
	std::vector<MinesweeperNode*> tempVec;

	for (int x = 0; x < gridSize; x++)
	{
		tempVec.clear();
		for (int y = 0; y < gridSize; y++)
		{
			tempVec.push_back(new MinesweeperNode(x, y));
		}
		nodeGrid.push_back(tempVec);
	}

	#pragma region addSurroundingNodes

	for (int x = 0; x < gridSize; x++)
		for (int y = 0; y < gridSize; y++)
		{
			if (y != 0)
			{
				nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x][y - 1]);
				if (x != 0)
					nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x - 1][y - 1]);
			}

			if (x != 0)
			{
				nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x - 1][y]);
				if(y != (gridSize - 1))
					nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x - 1][y + 1]);
			}

			if (y != (gridSize - 1))
			{
				nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x][y + 1]);
				if (x != (gridSize - 1))
					nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x + 1][y + 1]);
			}

			if (x != (gridSize - 1))
			{
				nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x + 1][y]);
				if (y != 0)
					nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x + 1][y - 1]);
			}
		}

#pragma endregion

	#pragma region Texture bullshit
	std::string path = std::string(BINPATH + "Tiles/0.png");
	tileTexture0 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/1.png");
	tileTexture1 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/2.png");
	tileTexture2 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/3.png");
	tileTexture3 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/4.png");
	tileTexture4 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/5.png");
	tileTexture5 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/6.png");
	tileTexture6 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/7.png");
	tileTexture7 = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/8.png");
	tileTexture8 = new aie::Texture(path.c_str());

	path = std::string(BINPATH + "Tiles/Pressed.png");
	tilePressed = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/Closed.png");
	tileClosed = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/Bomb.png");
	mineExposed = new aie::Texture(path.c_str());
	path = std::string(BINPATH + "Tiles/FinalBomb.png");
	lastMine = new aie::Texture(path.c_str());

	spacing = tileClosed->getWidth();

#pragma endregion

}

MinesweeperGame::~MinesweeperGame()
{
	delete tileTexture0;
	delete tileTexture1;
	delete tileTexture2;
	delete tileTexture3;
	delete tileTexture4;
	delete tileTexture5;
	delete tileTexture6;
	delete tileTexture7;
	delete tileTexture8;

	delete tilePressed;
	delete tileClosed;
	delete mineExposed;
	delete lastMine;
}

void MinesweeperGame::SetupGrid(int firstX, int firstY)
{
	//Make sure that the first node that player clicks on isn't a mine, and make sure the ones around it aren't either
	nodeGrid[firstX][firstY]->mineAllowed = false;
	for (unsigned int i = 0; i < nodeGrid[firstX][firstY]->surroundingNodes.size(); i++)
	{
		nodeGrid[firstX][firstY]->surroundingNodes[i]->mineAllowed = false;
	}

	for (int i = 0; i < maxMines; i++)
	{
		do
		{
			int randX = rand() % gridSize;
			int randY = rand() % gridSize;

			if (nodeGrid[randX][randY]->mineAllowed && !nodeGrid[randX][randY]->isMine)
			{
				nodeGrid[randX][randY]->isMine = true;
				for (unsigned int i = 0; i < nodeGrid[randX][randY]->surroundingNodes.size(); i++)
				{
					nodeGrid[randX][randY]->surroundingNodes[i]->value += 1;
				}
				break;
			}
		} while (true); //BAD!
	}
	
	nodeGrid[firstX][firstY]->Reveal();
	PushTrainingDataToVec(nodeGrid);
}

bool MinesweeperGame::ValidMoveAvailible(std::vector<std::vector<MinesweeperNode*>> input)
{
	for(unsigned int x = 0; x < input.size(); x++)
		for (unsigned int y = 0; y < input[0].size(); y++)
		{
			if (!input[x][y]->revealed && !input[x][y]->isMine)
				return true;
		}
	return false;
}

void MinesweeperGame::UpdateGrid(aie::Input * input, float deltaTime)
{
	GetTileAtMouse(input->getMouseX(), input->getMouseY(), &m_selectedTileX, &m_selectedTileY);

	for (int x = 0; x < gridSize; x++)
		for (int y = 0; y < gridSize; y++)
		{
			nodeGrid[x][y]->isPressed = false;
		}

	ImGui::Begin("NN Helper");
	if (ImGui::Button("Suggest Move"))
	{
		NNSuggestMove = true;
		Highest = 0.f;
		HighestPos = 0;
		std::vector<double> result = m_NNController->GetNNSelection(nodeGrid);
		for (unsigned int i = 0; i < result.size(); i++)
		{
			if (Highest < result[i])
			{
				Highest = result[i];
				HighestPos = i;
			}
		}

		NNSuggestionX = HighestPos / gridSize;
		NNSuggestionY = (HighestPos % gridSize);
	}

	if (ImGui::Button("Do Move"))
	{
		if (NNSuggestMove)
		{
			NNSuggestMove = false;
			if (firstClick)
			{
				firstClick = false;
				SetupGrid(NNSuggestionX, NNSuggestionY);
			}
			else
			{
				if (nodeGrid[NNSuggestionX][NNSuggestionY]->Reveal())
				{
					gameOver = true;
				}
				else if(!ValidMoveAvailible(nodeGrid)) {
					gameOver = true;
				}
			}
		}
		else
		{
			Highest = 0.f;
			HighestPos = 0;
			std::vector<double> result = m_NNController->GetNNSelection(nodeGrid);
			for (unsigned int i = 0; i < result.size(); i++)
			{
				if (Highest < result[i])
				{
					Highest = result[i];
					HighestPos = i;
				}
			}

			NNSuggestionX = HighestPos / gridSize;
			NNSuggestionY = (HighestPos % gridSize);

			if (firstClick)
			{
				firstClick = false;
				do {
					SetupGrid(NNSuggestionX, NNSuggestionY);
				}
				while(!ValidMoveAvailible(nodeGrid));
			}
			else
			{
				if (nodeGrid[NNSuggestionX][NNSuggestionY]->Reveal())
				{
					gameOver = true;
				}
				else if(!ValidMoveAvailible(nodeGrid)) {
					gameOver = true;
				}
			}
		}
	}

	if (ImGui::Button("Reset Board"))
	{
		NNSuggestMove = false;
		gameOver = true;
		timeBeforeReset = 0.0;
		isTesting = true;
	}

	ImGui::End();

	if (NNSuggestMove)
	{
		nodeGrid[NNSuggestionX][NNSuggestionY]->isPressed = true;
	}

	if (input->isMouseButtonDown(0))
	{
		
		mouseDown = true;
		if (m_selectedTileX != -1 && m_selectedTileY != -1 && !nodeGrid[m_selectedTileX][m_selectedTileY]->revealed)
			nodeGrid[m_selectedTileX][m_selectedTileY]->isPressed = true;
	}

	if (input->isMouseButtonUp(0) && mouseDown)
	{
		mouseDown = false;
		if (m_selectedTileX != -1 && m_selectedTileY != -1)
		{
			NNSuggestMove = false;
			if (firstClick)
			{
				firstClick = false;
				SetupGrid(m_selectedTileX, m_selectedTileY);
			}
			else
			{
				if (nodeGrid[m_selectedTileX][m_selectedTileY]->Reveal())
				{
					//end game stuff here
					NNSuggestMove = false;
					gameOver = true;
				}
				else
				{
					PushResultDataToVec(m_selectedTileX, m_selectedTileY);
					clickRegisteredForTraining = true;
					NNSuggestMove = false;
				}
			}	
		}
		
		if (m_selectedTileX != -1 && m_selectedTileY != -1)
			nodeGrid[m_selectedTileX][m_selectedTileY]->Reveal();
	}

	

	if (gameOver)
	{
		timeBeforeReset -= deltaTime;
		if (timeBeforeReset <= 0.f)
		{
			timeBeforeReset = 0.7f;
			Reset();
		}
	}
	else
	{
		if (clickRegisteredForTraining && createTrainingData)
		{
			clickRegisteredForTraining = false;
			CheckPushDataToFile();
			PushTrainingDataToVec(nodeGrid); //Check this to make sure the board updates before this happens
		}
	}

}

void MinesweeperGame::DrawGrid(aie::Renderer2D* rend2D)
{
	int xPos = screenPos.x - ((gridSize/2) * spacing); 
	int yPos = screenPos.y - ((gridSize/2) * spacing); 
	for(int x = 0; x < gridSize; x++)
		for (int y = 0; y < gridSize; y++)
		{
			aie::Texture* texture = tileClosed;
			if (nodeGrid[x][y]->isPressed)
			{
				texture = tilePressed;
			}
			else
			{
				if (nodeGrid[x][y]->revealed == false)
				{
					texture = tileClosed;
				}
				else
				{
					if (nodeGrid[x][y]->isMine)
					{
						texture = lastMine;
					}
					else
					{
						switch (nodeGrid[x][y]->value)
						{
						case 0: texture = tileTexture0;
							break;
						case 1: texture = tileTexture1;
							break;
						case 2: texture = tileTexture2;
							break;
						case 3: texture = tileTexture3;
							break;
						case 4: texture = tileTexture4;
							break;
						case 5: texture = tileTexture5;
							break;
						case 6: texture = tileTexture6;
							break;
						case 7: texture = tileTexture7;
							break;
						case 8: texture = tileTexture8;
							break;
						}
					}
				}
			}
			rend2D->drawSprite(texture, ((float)xPos + (spacing * x)), ((float)yPos + (spacing * y)));
		}
}

void MinesweeperGame::GetTileAtMouse(int mouseX, int mouseY, int * tileX, int * tileY)
{
	int xPos = screenPos.x - ((gridSize/2) * spacing); 
	int yPos = screenPos.y - ((gridSize/2) * spacing); 

	if ((mouseX >= xPos - (spacing / 2) && mouseX <= (xPos + (spacing * gridSize)) - (spacing / 2)) && (mouseY >= yPos - (spacing / 2) && mouseY <= (yPos + (spacing * gridSize)) - (spacing / 2)))
	{
		for (int x = 0; x < gridSize; x++)
			for (int y = 0; y < gridSize; y++)
			{
				if ((mouseX >= (xPos + (spacing * x) - (spacing / 2)) && mouseX < (xPos + (spacing * (x + 1)) - (spacing / 2))) && (mouseY >= (yPos + (spacing * y) - (spacing / 2)) && mouseY < (yPos + (spacing * (y + 1)) - (spacing / 2))))
				{
					*tileX = x;
					*tileY = y;
					return;
				}
			}
	}
	else
	{
		*tileX = -1;
		*tileY = -1;
	}
}

void MinesweeperGame::Reset()
{
	firstClick = true;
	gameOver = false;
	for (int x = 0; x < gridSize; x++)
		for (int y = 0; y < gridSize; y++)
		{
			nodeGrid[x][y]->isMine = false;
			nodeGrid[x][y]->revealed = false;
			nodeGrid[x][y]->mineAllowed = true;
			nodeGrid[x][y]->value = 0;
		}

	if (createTrainingData || isTesting)
	{
		int xPos = rand() % gridSize;
		int yPos = rand() % gridSize;
		SetupGrid(xPos, yPos);
		
		firstClick = false;
	}
	if(!ValidMoveAvailible(nodeGrid)) {
		Reset();
	}
}

void MinesweeperGame::SetupGrid()
{
	Reset();

	int xPos = rand() % gridSize;
	int yPos = rand() % gridSize;

	SetupGrid(xPos, yPos);
}

std::vector<std::vector<MinesweeperNode*>> MinesweeperGame::GetGridForNN()
{
	return nodeGrid;
}

std::vector<std::vector<MinesweeperNode*>> MinesweeperGame::SimulateTileClickForTraining(int x, int y)
{
	nodeGrid[x][y]->Reveal();
	return nodeGrid;
}

void MinesweeperGame::PushTrainingDataToVec(std::vector<std::vector<MinesweeperNode*>> trainingData)
{
	/*
	change grid data into NN input data, and store it in trainingDataHoldingVector
	*/
	trainingDataHoldingVector.clear();

	for (unsigned int x = 0; x < trainingData.size(); x++)
		for (unsigned int y = 0; y < trainingData[0].size(); y++)
		{
			trainingDataHoldingVector.push_back((double)trainingData[x][y]->revealed);
			if (trainingData[x][y]->revealed)
			{
				trainingDataHoldingVector.push_back((trainingData[x][y]->value / 10.0));
			}
			else
			{
				trainingDataHoldingVector.push_back((0.0)); //Try this as 1, and see if that helsps
			}

		}
}
void MinesweeperGame::PushResultDataToVec(int x, int y)
{
	/*
	change x and y selection into NN Result data, and store it in resultDataHoldingVector
	*/
	resultDataHoldingVector.clear();
	for (int i = 0; i < gridSize * gridSize; i++)
	{
		resultDataHoldingVector.push_back(0.0);
	}

	resultDataHoldingVector[(x * gridSize) + y] = 1.0;
}
void MinesweeperGame::CheckPushDataToFile()
{
	if (resultDataHoldingVector.size() != 0 && trainingDataHoldingVector.size() != 0)
	{
		std::ofstream trainingDataFile;

		trainingDataFile.open(BINPATH + "NeuralNet/trainingData.txt", std::ios::app);
		if (trainingDataFile.good())
		{
			for (unsigned int i = 0; i < trainingDataHoldingVector.size(); i++)
			{
				trainingDataFile << trainingDataHoldingVector[i] << " "; //The space is so that the values can be seperated when being read in later
			}
			trainingDataHoldingVector.clear();
			trainingDataFile << "\n"; // add a line between the training and result data
			for (unsigned int i = 0; i < resultDataHoldingVector.size(); i++)
			{
				trainingDataFile << resultDataHoldingVector[i] << " "; //The space is so that the values can be seperated when being read in later
			}
			resultDataHoldingVector.clear();
			trainingDataFile << "\n";// add a line between this set of result data and the next set of training data
		}
		else
		{
			assert(false);
			printf("File did not open correctly");
		}
		trainingDataFile.close();
	}
	//Open file for write, then write the Training data, and THEN the result data
}
#pragma endregion