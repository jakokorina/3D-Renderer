cmake_minimum_required(VERSION 3.16)
project(3D_Renderer)

set(CMAKE_CXX_STANDARD 17)

add_executable(3D_Renderer main.cpp camera.h world.h renderer.h screen.h triangle.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(3D_Renderer sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

find_package(glm REQUIRED)
target_link_libraries(3D_Renderer glm::glm)