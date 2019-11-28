#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "imgui.h"
#include <functional>

struct MinesweeperNode;
class MinesweeperGame;
class MinesweeperController;

#define GRIDSIZE 4 //Don't go below 4, tends to cause an infinite loop
#define MINECOUNT 3

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
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	float avgCorrectness = 0.f;

	bool m_selectMineSweeper = true;

	bool m_userTestMinesweeper = false;

	bool m_trainMinesweeper = false;

	bool m_testMinesweeperNN = false;

	bool createMinesweeperTrainingData = false;
};