cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(aieBootstrapProject)

#TODO: Update to use the target_complile_requires
set(CMAKE_CXX_STANDARD 14)

cmake_policy(SET CMP0072 OLD)

find_package(OpenGL REQUIRED)


#add build glfw
option(GLFW_BUILD_EXAMPLES NO)
option(GLFW_BUILD_TESTS NO)
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/glfw-source)

add_subdirectory(bootstrap)


#PROJECT TO BUILD
add_subdirectory(nnp)
add_subdirectory(project2D)
add_subdirectory(project3D)