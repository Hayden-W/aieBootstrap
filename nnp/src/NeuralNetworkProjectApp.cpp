#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"

#include "../inc/NeuralNetworkProjectApp.h"
#include "../inc/MinesweeperController.h"
#include "../inc/Minesweeper.h"
#include "glm/vec2.hpp"

NeuralNetworkProjectApp::NeuralNetworkProjectApp() {
	
}

NeuralNetworkProjectApp::~NeuralNetworkProjectApp() {
	
}

bool NeuralNetworkProjectApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	MSgame = new MinesweeperGame(GRIDSIZE, MINECOUNT, glm::vec2(this->getWindowWidth() / 2, this->getWindowHeight() / 2));

	MSNNController = new MinesweeperController(GRIDSIZE, MINECOUNT);

	MSgame->SetNNRef(MSNNController);

	setBackgroundColour(0.75f, 0.75f, 0.75f);
	return true;
}

void NeuralNetworkProjectApp::shutdown() {
	delete MSgame;
	delete MSNNController;

	delete m_font;
	delete m_2dRenderer;
}

void NeuralNetworkProjectApp::update(float deltaTime) {
	updateGUI();
	// input example
	aie::Input* input = aie::Input::getInstance();

	#pragma region Minesweeper
	if (m_userTestMinesweeper)
	{
		MSgame->UpdateGrid(input, deltaTime);
	}

	if (MSNNController->trainingNetwork || MSNNController->testingNetwork)
	{
		MSNNController->Update(deltaTime);
	}
	else
	{
		m_trainMinesweeper = false;
		m_testMinesweeperNN = false;
	}

	if (createMinesweeperTrainingData)
	{
		MSgame->SetCtreateTrainingData(true);
		MSgame->UpdateGrid(input, deltaTime);

	}
	else
	{
		MSgame->SetCtreateTrainingData(false);
	}
#pragma endregion

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void NeuralNetworkProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	
	// begin drawing sprites
	m_2dRenderer->begin();

	if (m_userTestMinesweeper || createMinesweeperTrainingData)
	{
		MSgame->DrawGrid(m_2dRenderer);
	}

	if (m_trainMinesweeper || m_testMinesweeperNN)
	{
		MSNNController->Draw(m_2dRenderer);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void NeuralNetworkProjectApp::updateGUI()
{
	#pragma region MineSweeper 
	if (m_selectMineSweeper)
	{
		ImGui::Begin("Minesweeper");
		if (ImGui::Button("Play Minesweeper W/ NN Help"))
		{
			m_selectMineSweeper = false;
			m_userTestMinesweeper = true;
			MSgame->Reset();
		}

		if (ImGui::Button("Train MineSweeper NN"))
		{
			m_selectMineSweeper = false;
			m_trainMinesweeper = true;
			MSNNController->MSGameTest->SetCtreateTrainingData(true);
			MSNNController->trainingNetwork = true;
			MSNNController->MSGameTest->Reset();
			MSNNController->grid = MSNNController->MSGameTest->GetGridForNN();
			MSgame->Reset();
		}

		if (ImGui::Button("Load NN Weights"))
		{
			std::string path = "./bin/NeuralNet/MinesweeperWeights.txt";
			MSNNController->LoadNeuralNetWeightsFromFile(path.c_str());
		}

		if (ImGui::Button("Save NN Weights"))
		{
			std::string path = "./bin/NeuralNet/MinesweeperWeights.txt";
			MSNNController->SaveNeuralNetWeightsToFile(path.c_str());
		}
		ImGui::End();
	}

	if (m_userTestMinesweeper)
	{
		ImGui::Begin("Test Minesweeper Menu");

		if (ImGui::Button("Exit"))
		{
			m_selectMineSweeper = true;
			m_userTestMinesweeper = false;
			MSNNController->MSGameTest->SetCtreateTrainingData(false);
			MSNNController->trainingNetwork = false;
		}

		ImGui::End();
	}

	if (m_trainMinesweeper)
	{
		ImGui::Begin("Train Minesweeper Menu");

		if (ImGui::Button("Exit"))
		{
			m_selectMineSweeper = true;
			m_trainMinesweeper = false;
			MSNNController->MSGameTest->SetCtreateTrainingData(false);
			MSNNController->trainingNetwork = false;
		}

		ImGui::End();
	}
	#pragma endregion
}
