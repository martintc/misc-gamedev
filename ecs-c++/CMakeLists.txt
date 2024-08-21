cmake_minimum_required(VERSION 3.15)

find_package(Catch2 3 REQUIRED)

project(ECS VERSION 1.0
						DESCRIPTION "Implementation of a C++ ECS Architecture"
						LANGUAGES CXX)

add_executable(ecs src/main.cpp src/ecs.cpp)
target_link_libraries(ecs PRIVATE:Catch2::Catch2WithMain)
target_include_directories(ecs PUBLIC include)

set_property(TARGET ecs PROPERTY CXX_STANDARD 17)
