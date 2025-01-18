cmake_minimum_required(VERSION 3.29)
project(sfmlProject)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)


set(CMAKE_CXX_STANDARD 20)

add_executable(sfmlProject main.cpp)
target_link_libraries(sfmlProject sfml-graphics)
