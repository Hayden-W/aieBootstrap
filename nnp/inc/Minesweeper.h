#pragma once
#include <vector>
#include "glm/vec2.hpp"
#define USING_2_NODENEURAL_NET true

#define GRID_SIZE 5

namespace aie {
	class Texture;
	class Input;
	class Renderer2D;
}

class MinesweeperController;

struct MinesweeperNode {
	MinesweeperNode(int x, int y);
	~MinesweeperNode();

	bool Reveal();

	void firstTile();
	
	bool isMine;
	bool marked = false;
	bool revealed;

	int value;
	int xPos, yPos;
	
	
	bool mineAllowed;
	bool isPressed;
	// These last two are only used for the basic stratergy solver
	
	bool safeToReveal = false;
	std::vector<MinesweeperNode*> surroundingNodes;
};

class MinesweeperGame {
public:
	MinesweeperGame(int gridSize, int mineCount, glm::vec2 center);
	~MinesweeperGame();

	void SetupGrid(int firstX, int firstY);

	void UpdateGrid(aie::Input* input, float deltaTime);

	void DrawGrid(aie::Renderer2D* rend2D);

	void GetTileAtMouse(int mouseX, int mouseY, int* tileX, int* tileY);

	void Reset();

	void SetupGrid();

	std::vector<std::vector<MinesweeperNode*>> GetGridForNN();

	std::vector<std::vector<MinesweeperNode*>> SimulateTileClickForTraining(int x, int y);

	void SetCtreateTrainingData(bool input) { createTrainingData = input; };

	void SetIsTesting(bool input) { isTesting = input; };

	void SetNNRef(MinesweeperController* ref) { m_NNController = ref; };
private:
	void PushTrainingDataToVec(std::vector<std::vector<MinesweeperNode*>> trainingData); //Puts trainingdata into a holding vector

	void PushResultDataToVec(int x, int y); //puts result data into holding vector

	void CheckPushDataToFile(); //flushes training data pairs into a .txt file
	//Checks if there are any valid moves on the board
	bool ValidMoveAvailible(std::vector<std::vector<MinesweeperNode*>> input);
private:
	std::vector<std::vector<MinesweeperNode*>> nodeGrid;

	#pragma region Texture Variables
	aie::Texture* tileTexture0;
	aie::Texture* tileTexture1;
	aie::Texture* tileTexture2;
	aie::Texture* tileTexture3;
	aie::Texture* tileTexture4;
	aie::Texture* tileTexture5;
	aie::Texture* tileTexture6;
	aie::Texture* tileTexture7;
	aie::Texture* tileTexture8;
	aie::Texture* tilePressed;
	aie::Texture* tileClosed;
	aie::Texture* mineExposed;
	aie::Texture* lastMine;
#pragma endregion

	//NN shit
	MinesweeperController* m_NNController;

	bool NNSuggestMove = false;
	int NNSuggestionX = 0;
	int NNSuggestionY = 0;

	int HighestPos = 0;
	double Highest = 0.f;
	//End


	bool isTesting = false;

	bool createTrainingData = false;
	bool clickRegisteredForTraining = false;
	bool pushDataToFile = false;

	std::vector<double> trainingDataHoldingVector;
	std::vector<double> resultDataHoldingVector;
	
	glm::vec2 screenPos;

	int gridSize, maxMines; 
	int gridXPos = 600, gridYPos = 500, spacing = 16;
	bool firstClick = true;
	bool mouseDown = false;
	bool gameOver = false;
	float timeBeforeReset = 0.6f;
	int m_selectedTileX, m_selectedTileY;
};