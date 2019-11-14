#include "inc/NeuralNetworkProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "imgui.h"

#include "inc/MinesweeperController.h"
#include "inc/Minesweeper.h"
#include "inc/XORController.h"
#include "inc/PatternRecognitionController.h"
NeuralNetworkProjectApp::NeuralNetworkProjectApp() {
	
}

NeuralNetworkProjectApp::~NeuralNetworkProjectApp() {
	
}

bool NeuralNetworkProjectApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	MSgame = new MinesweeperGame(GRIDSIZE, GRIDSIZE, 5);

	MSNNController = new MinesweeperController(GRIDSIZE);

	PatternNNController = new PatternRecognitionController(4, 4, 4);

	MSgame->SetNNRef(MSNNController);

	XORcontroller = new XORController(2, 2, 1);
	XORcontroller->LoadTrainingData();
	setBackgroundColour(0.75f, 0.75f, 0.75f);
	return true;
}

void NeuralNetworkProjectApp::shutdown() {
	delete MSgame;
	delete MSNNController;
	delete XORcontroller;

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
		if (m_trainMinesweeper)
			m_mainMenu = true;
		if (m_testMinesweeperNN)
			m_mainMenu = true;
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

	#pragma region XOR
	if (m_trainXOR)
	{
		XORcontroller->TrainNNUntilCorrect();
	}

	if (m_userTestXOR)
	{
		XORcontroller->TestNN();
	}
#pragma endregion

	#pragma region Pattern
	if (m_trainPattern)
	{
		PatternNNController->TrainNNUntilCorrect();
	}

	if (m_userTestPattern)
	{
		PatternNNController->TestNN();
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
	if (m_mainMenu)
	{
		ImGui::Begin("Main Menu");

		if (ImGui::Button("Mine Sweeper"))
		{
			m_selectMineSweeper = true;
		}

		if (ImGui::Button("XOR"))
		{
			m_selectXOR = true;
		}

		if (ImGui::Button("Pattern"))
		{
			m_selectPattern = true;
		}


		ImGui::End();
		if (m_selectMineSweeper || m_selectXOR || m_selectPattern || m_trainMinesweeper || m_testMinesweeperNN)
			m_mainMenu = false;
	}

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
			std::string path = BINPATH + "NeuralNet/MinesweeperWeights.txt";
			MSNNController->LoadNeuralNetWeightsFromFile(path.c_str());
		}

		if (ImGui::Button("Save NN Weights"))
		{
			std::string path = BINPATH + "NeuralNet/MinesweeperWeights.txt";
			MSNNController->SaveNeuralNetWeightsToFile(path.c_str());
		}

		if (ImGui::Button("Exit"))
		{
			m_mainMenu = true;
			m_selectMineSweeper = false;
			m_testMinesweeperNN = false;
			m_userTestMinesweeper = false;
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
	
#pragma region XOR
	if (m_selectXOR)
	{
		ImGui::Begin("XOR");
		if (ImGui::Button("Train XOR"))
		{
			m_selectXOR = false;
			m_trainXOR = true;
		}

		if (ImGui::Button("Test XOR"))
		{
			m_selectXOR = false;
			m_userTestXOR = true;
		}

		if (ImGui::Button("Load NN Weights"))
		{
			std::string path = BINPATH + "NeuralNet/XORWeights.txt";
			MSNNController->LoadNeuralNetWeightsFromFile(path.c_str());
		}

		if (ImGui::Button("Save NN Weights"))
		{
			std::string path = BINPATH + "NeuralNet/XORWeights.txt";
			MSNNController->SaveNeuralNetWeightsToFile(path.c_str());
		}

		if (ImGui::Button("Exit"))
		{
			m_mainMenu = true;
			m_selectXOR = false;
			m_trainXOR = false;
			m_userTestXOR = false;
		}
		ImGui::End();
	}

	if (m_userTestXOR)
	{
		ImGui::Begin("Test XOR");
		
		if (ImGui::Button("Exit"))
		{
			m_selectXOR = true;
			m_userTestXOR = false;
		}
		ImGui::End();
	}

	if (m_trainXOR)
	{
		ImGui::Begin("Train XOR");
		
		if (ImGui::Button("Exit"))
		{
			m_selectXOR = true;
			m_trainXOR = false;
		}
		ImGui::End();
	}
#pragma endregion
	
#pragma region Pattern
	if (m_selectPattern)
	{
		ImGui::Begin("Pattern");
		if (ImGui::Button("Train Pattern NN"))
		{
			m_selectPattern = false;
			m_trainPattern = true;
		}

		if (ImGui::Button("Test pattern NN"))
		{
			m_selectPattern = false;
			m_userTestPattern = true;
		}

		if (ImGui::Button("Load NN Weights"))
		{
			std::string path = BINPATH + "NeuralNet/PatternWeights.txt";
			MSNNController->LoadNeuralNetWeightsFromFile(path.c_str());
		}

		if (ImGui::Button("Save NN Weights"))
		{
			std::string path = BINPATH + "NeuralNet/PatternWeights.txt";
			MSNNController->SaveNeuralNetWeightsToFile(path.c_str());
		}

		if (ImGui::Button("Exit"))
		{
			m_mainMenu = true;
			m_selectPattern = false;
			m_trainPattern = false;
			m_userTestPattern = false;
		}
		ImGui::End();
	}

	if (m_trainPattern)
	{
		ImGui::Begin("Test Pattern");

		if (ImGui::Button("Exit"))
		{
			m_selectPattern = true;
			m_trainPattern = false;
		}
		ImGui::End();
	}

	if (m_userTestPattern)
	{
		ImGui::Begin("Train Pattern");

		if (ImGui::Button("Exit"))
		{
			m_selectPattern = true;
			m_userTestPattern = false;
		}
		ImGui::End();
	}
#pragma endregion
}
