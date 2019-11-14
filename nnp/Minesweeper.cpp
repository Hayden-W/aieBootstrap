#include "inc/Minesweeper.h"
#include "inc/MinesweeperController.h"
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

MinesweeperGame::MinesweeperGame(int gridX, int gridY, int mineCount) :
	gridSizeX(gridX), gridSizeY(gridY), maxMines(mineCount)
{
	std::vector<MinesweeperNode*> tempVec;

	for (int x = 0; x < gridSizeX; x++)
	{
		tempVec.clear();
		for (int y = 0; y < gridSizeY; y++)
		{
			tempVec.push_back(new MinesweeperNode(x, y));
		}
		nodeGrid.push_back(tempVec);
	}

	#pragma region addSurroundingNodes

	for (int x = 0; x < gridSizeX; x++)
		for (int y = 0; y < gridSizeY; y++)
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
				if(y != (gridSizeY - 1))
					nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x - 1][y + 1]);
			}

			if (y != (gridSizeY - 1))
			{
				nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x][y + 1]);
				if (x != (gridSizeX - 1))
					nodeGrid[x][y]->surroundingNodes.push_back(nodeGrid[x + 1][y + 1]);
			}

			if (x != (gridSizeX - 1))
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

	if (createTrainingData || isTesting)
	{
		maxMines = rand() % 6 + 2;
	}

	for (int i = 0; i < maxMines; i++)
	{
		do
		{
			int randX = rand() % gridSizeX;
			int randY = rand() % gridSizeY;

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

void MinesweeperGame::UpdateGrid(aie::Input * input, float deltaTime)
{
	GetTileAtMouse(input->getMouseX(), input->getMouseY(), &m_selectedTileX, &m_selectedTileY);

	for (int x = 0; x < gridSizeX; x++)
		for (int y = 0; y < gridSizeY; y++)
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

		NNSuggestionX = HighestPos / 5;
		NNSuggestionY = (HighestPos % 5);
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

			NNSuggestionX = HighestPos / 5;
			NNSuggestionY = (HighestPos % 5);

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
	for(int x = 0; x < gridSizeX; x++)
		for (int y = 0; y < gridSizeY; y++)
		{
			if (nodeGrid[x][y]->isPressed)
			{
				rend2D->drawSprite(tilePressed, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
			}
			else
			{
				if (nodeGrid[x][y]->revealed == false)
				{
					rend2D->drawSprite(tileClosed, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
				}
				else
				{
					if (nodeGrid[x][y]->isMine)
					{
						rend2D->drawSprite(lastMine, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
					}
					else
					{
						switch (nodeGrid[x][y]->value)
						{
						case 0: rend2D->drawSprite(tileTexture0, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 1: rend2D->drawSprite(tileTexture1, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 2: rend2D->drawSprite(tileTexture2, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 3: rend2D->drawSprite(tileTexture3, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 4: rend2D->drawSprite(tileTexture4, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 5: rend2D->drawSprite(tileTexture5, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 6: rend2D->drawSprite(tileTexture6, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 7: rend2D->drawSprite(tileTexture7, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						case 8: rend2D->drawSprite(tileTexture8, ((float)gridXPos + (spacing * x)), ((float)gridYPos + (spacing * y)));
							break;
						}
					}
				}
			}
		}
}

void MinesweeperGame::GetTileAtMouse(int mouseX, int mouseY, int * tileX, int * tileY)
{
	if ((mouseX >= gridXPos && mouseX <= (gridXPos + (spacing * gridSizeX))) && (mouseY >= gridYPos && mouseY <= (gridYPos + (spacing * gridSizeY))))
	{
		for (int x = 0; x < gridSizeX; x++)
			for (int y = 0; y < gridSizeY; y++)
			{
				if ((mouseX >= (gridXPos + (spacing * x)) && mouseX < (gridXPos + (spacing * (x + 1)))) && (mouseY >= (gridYPos + (spacing * y)) && mouseY < (gridYPos + (spacing * (y + 1)))))
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
	for (int x = 0; x < gridSizeX; x++)
		for (int y = 0; y < gridSizeY; y++)
		{
			nodeGrid[x][y]->isMine = false;
			nodeGrid[x][y]->revealed = false;
			nodeGrid[x][y]->mineAllowed = true;
			nodeGrid[x][y]->value = 0;
		}

	if (createTrainingData || isTesting)
	{
		int xPos = rand() % 2 + 1;
		int yPos = rand() % 2 + 1;

		SetupGrid(xPos, yPos);
		firstClick = false;
	}
}

void MinesweeperGame::SetupGrid()
{
	Reset();

	int xPos = rand() % 4;
	int yPos = rand() % 4;

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
	for (int i = 0; i < 25; i++)
	{
		resultDataHoldingVector.push_back(0.0);
	}

	resultDataHoldingVector[(x * 5) + y] = 1.0;
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