#pragma once
#include "Controller.h"

#include <string>

class XORController : public Controller
{
public:
	XORController(int inputs, int hidden, int output);
	~XORController();

	void LoadTrainingData();

	void TrainNN(unsigned int trainingIterations);

	void TrainNNUntilCorrect();

	void SelfTrain();

	void TestNN();
protected:
	double trainingAccuracy = 0.01;
	int trainingIterationsBeforeReweight = 10000;

	float input1 = 0.f, input2 = 0.f;

	double AvgAccuracy = 0.0;
	double rollingAccuracyAvg[100] = {0};
	int accAvgPos = 0;

	double result = 0.0;
	std::vector<double> InputVec;
	std::vector<double> OutputVec;
	std::string output;
};