#include "inc/NeuralNetworkProjectApp.h"

int main() {
	auto app = new NeuralNetworkProjectApp();
	app->run("AIE", 1280, 720, false);
	delete app;
	return 0;
}