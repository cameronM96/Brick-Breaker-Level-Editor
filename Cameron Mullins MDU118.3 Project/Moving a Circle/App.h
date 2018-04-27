#pragma once

//#ifndef APP_H
#define APP_H

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

class App
{
private:
	sf::Event			event;

	//Start Clock
	sf::Clock Clock;

	//Background Variables
	sf::Texture			backgroundTexture;
	sf::Sprite			background;
	sf::Vector2u		TextureSize;  //Added to store texture size.
	sf::Vector2u		WindowSize;   //Added to store window size.

	//Menu Button Variables
	sf::Font font;
	sf::Text newText;
	sf::Text saveText;
	sf::Text loadText;
	sf::Text backgroundText;

	sf::View			view;
	sf::RenderWindow	window;

	// The local mouse position (relative to a window)
	sf::Vector2i localMousePosition;

	// Variable to make onbuttondown checks
	bool isred = true;
	bool changeColor = true;
	bool createBrick = true;
	bool deleteBrick = true;
	bool newPressed = false;
	bool save = false;
	bool load = false;
	bool changeBackground = false;
	bool leftMouseButton = false;
	bool rightMouseButton = false;

	// Private Prototypes
	bool WriteToFile();
	bool ReadFromFile();
	int AddBrick(sf::RectangleShape *brick, sf::Color color, int *brickNumber);
	int SetBackground();

public:
	App(char *Title, int ScreenWidth, int ScreenHeight, int ScreenBpp);

	~App();

	// Public Prototypes
	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
};