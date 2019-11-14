#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "imgui.h"
#include <functional>

struct MinesweeperNode;
class MinesweeperGame;
class MinesweeperController;
class XORController;
class PatternRecognitionController;

#define GRIDSIZE 5
#define BINPATH "/home/hayden/dev/aieBootstrap/bin"

class NeuralNetworkProjectApp : public aie::Application {
public:

	NeuralNetworkProjectApp();
	virtual ~NeuralNetworkProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void updateGUI();

protected:


	MinesweeperGame* MSgame;
	MinesweeperController* MSNNController;
	XORController* XORcontroller;
	PatternRecognitionController* PatternNNController;																																																						std::function<int()> mfn;


	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	float avgCorrectness = 0.f;

	bool m_mainMenu = true;
	bool m_exitMenu = false;

	bool m_userTestMinesweeper = false;
	bool m_userTestXOR = false;
	bool m_userTestPattern = false;

	bool m_trainMinesweeper = false;
	bool m_trainXOR = false;
	bool m_trainPattern = false;

	bool m_selectMineSweeper = false;
	bool m_selectXOR = false;
	bool m_selectPattern = false;

	bool m_testMinesweeperNN = false;

	bool createMinesweeperTrainingData = false;
};