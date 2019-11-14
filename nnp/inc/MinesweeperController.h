#pragma once
#include "Controller.h"
#include <vector>

#define BINPATH std::string("/home/hayden/dev/aieBootstrap/bin/")

struct MinesweeperNode;
class MinesweeperGame;

namespace aie {
	class Renderer2D;
}

class MinesweeperController : public Controller
{
public:
	MinesweeperController(int gridSize);

	virtual ~MinesweeperController();

	bool LoadTrainingDataFromFile();

	void LoadTrainingData();

	void TrainNNUntilCorrect();

	void SelfTrainUntilCorrect();

	void Update(float deltaTime);

	void Draw(aie::Renderer2D* renderer);

	std::vector<double> GetNNSelection(std::vector<std::vector<MinesweeperNode*>> input);
public:

	bool trainingNetwork = false;

	bool selfTrainNetwork = false;

	bool testingNetwork = false;

	std::vector<std::vector<MinesweeperNode*>> grid;

	MinesweeperGame* MSGameTest; //BAD!

private:
	void TrainNN(unsigned int trainingIterations) {};

	void TestNN();

	void GetExpectedResult();

	std::vector<double> GetSolution(std::vector<std::vector<MinesweeperNode*>> input);

	std::vector<double> adaptMinesweeperInput(std::vector<std::vector<MinesweeperNode*>> input);

	std::vector<double> explode(const char* s);
	
	void MarkSquares(MinesweeperNode* input);

	void RevealSquares(MinesweeperNode* input);

	bool ValidMoveAvailible(std::vector<std::vector<MinesweeperNode*>> input);
private:
	//Clean this shit up Oh god
	int x;
	int y;

	int tempResultDataPos = 0;

	int amountCorrectSelfTrain = 0;
	int amountRevealedSelfTrain = 0;
	int amountMinesSelfTrain = 0;

	std::vector<double> result;
	std::vector<double> adaptedInput;
	
	std::vector<double> tempResultData;

	double results[100] = { 0 };
	double resultAvg;
	int currentResultPos = 0;
	int currentData = 0;


	bool correctResult = false;

	double Highest = 0.f;
	float avgCorrectness = 0.f;
	float slidingAverage[100] = { 0 };

	int HighestPos = 0;
	int m_minesweeperGameSize = 5;
	int m_numberOfMines = 8;

	int slidingAveragePos = 0;
	int NumberResult = 0;
};