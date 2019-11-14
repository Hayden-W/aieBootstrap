#pragma once
#include "Controller.h"
#include <string>

class PatternRecognitionController : public Controller
{
public:
	PatternRecognitionController(int inputs, int hidden, int output);
	~PatternRecognitionController();

	void LoadTrainingData();

	void TrainNN(unsigned int trainingIterations);

	void TrainNNUntilCorrect();

	void TestNN();
public: 


protected:
	double trainingAccuracy = 0.01;

	double rollingAccurcacyAvg[100] = { 0 };
	int rollAvgPos = 0;
	int amountCorrect;
	double correctPercent;
	float i1 = 0, i2 = 0, i3 = 0, i4 = 0;

	std::vector<double> NNResult;
	std::vector<double> m_resultVec;
	std::vector<double> m_inputVec; 
	
	std::string m_outputInput;
	std::string m_outputOutput;
	std::string m_outputResult;
	std::string m_avg;
};