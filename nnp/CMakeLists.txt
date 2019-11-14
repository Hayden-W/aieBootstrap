cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(nnp)

add_executable(${PROJECT_NAME}
    main.cpp
    Controller.cpp
    Minesweeper.cpp
    MinesweeperController.cpp
    NeuralNetwork.cpp
    NeuralNetworkProjectApp.cpp
    PatternRecognitionController.cpp
    XORController.cpp
    )

target_link_libraries(${PROJECT_NAME} aieBootstrap)
