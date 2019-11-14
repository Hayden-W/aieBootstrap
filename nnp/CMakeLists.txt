cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(nnp)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Controller.cpp
    src/Minesweeper.cpp
    src/MinesweeperController.cpp
    src/NeuralNetwork.cpp
    src/NeuralNetworkProjectApp.cpp
    )

target_link_libraries(${PROJECT_NAME} aieBootstrap)
