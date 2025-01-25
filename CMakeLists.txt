cmake_minimum_required(VERSION 3.29)
project(sfmlProject)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.0)
FETCHCONTENT_MAKEAVAILABLE(SFML)


set(CMAKE_CXX_STANDARD 20)

add_executable(sfmlProject main.cpp
        button/button.cpp
        button/button.h
        textField/textField.cpp
        textField/textField.h
        loginSystem/UserManager.cpp
        loginSystem/UserManager.h
        gameMenu.cpp
        gameMenu.h)
target_link_libraries(sfmlProject sfml-graphics sfml-window sfml-audio)
