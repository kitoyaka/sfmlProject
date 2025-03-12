# Tetris on SFML

This project is an implementation of the classic game *Tetris* using the [SFML](https://github.com/SFML/SFML.git) library.

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Build and Run](#build-and-run)
- [Features](#features)
- [Project Structure](#project-structure)
- [Project Contribution](#project-contribution)

## Description

Tetris is a classic game in which the player controls falling pieces, trying to fill horizontal lines without gaps. This project implements the basic mechanics of the game, such as:
- Controlling and moving the pieces
- Checking the filling of lines and removing them
- Scoring and changing the difficulty level
In this project were added such features as:
- Registration of new users

## Installation

Download the project from [GITHUB] at https://github.com/kitoyaka/sfmlProject.

## Build and Run

Before building the project, make sure that the following dependencies are installed on your computer:
- [SFML](https://github.com/SFML/SFML.git) (version 3.0.0 or higher is recommended)
- C++ compiler with support for C++20 or higher

## Features

The project was written with SFML 3.0.0 using the CLion 2024.3.1.1 program

## Project Structure

sfmlProject/  
├─── .idea/ # # Development environment configuration files  
├─── button/ # Components related to interface buttons  
├──── font/ # Fonts used in the project  
├──── image/ # Images and textures  
├──── loginSystem/ # Login system module  
├──── music/ # Audio files and music  
├──── tetris/ # Basic logic of Tetris game  
├──── textField/ # Components for working with text fields  
├──── .gitignore # File defining files to be ignored by Git  
├──── BuildDir.var # Variables for the build directory  
├──── CMakeLists.txt # CMake configuration file  
├──── SourceDir.var # Variables for the source directory  
├──── gameMenu.cpp # Implementation of the game menu  
├─── gameMenu.h # Header file for the game menu  
└─── main.cpp # Main file with the entry point to the program  

## Project Contribution

SSBNDRK wrote 90% of the code, all sounds were added by him (purchased), all textures were drawn using Photoshop programme.
special thanks to kitoyaka for participating in the project and for writing maximum 10% of the code by him 
