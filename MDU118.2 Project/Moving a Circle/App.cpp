#include "stdafx.h"
#include "App.h"

using namespace std;

//Create menu buttons and variables
sf::RectangleShape saveButton(sf::Vector2f(100, 50));
sf::RectangleShape loadButton(sf::Vector2f(100, 50));
sf::RectangleShape loadBackground(sf::Vector2f(100, 50));
string backgroundname = "background1.jpg";
sf::RectangleShape border1(sf::Vector2f(800, 60));
sf::RectangleShape border2(sf::Vector2f(140, 600));

//Create brick selector buttons
const int NUMBEROFRECTS = 5;
sf::RectangleShape editorBricks[NUMBEROFRECTS];
sf::Color colors[NUMBEROFRECTS] = {
	sf::Color(0, 0, 255, 255),
	sf::Color(0, 255, 255, 255),
	sf::Color(0, 255, 0, 255),
	sf::Color(255, 255, 0, 255),
	sf::Color(255, 0, 0, 255)
};

//Create array for new bricks (starts empty)
const int MAXBRICKS = 20;
int currentBrickNumber = 0;
sf::RectangleShape *newBricks[MAXBRICKS+1];

// Constructor
App::App(char *Title, int ScreenWidth, int ScreenHeight,int ScreenBpp)
{
	window.create(
		sf::VideoMode(ScreenWidth, ScreenHeight, ScreenBpp), Title, sf::Style::Close);
	window.setFramerateLimit(0);
	view = window.getDefaultView();
}

// Destructor
App::~App()
{
	// release memory
}

bool App::Init()
{
	// Initialise App data member
	window.setVerticalSyncEnabled(true);

	// Initialise Background
	SetBackground();

	// initialise Menu Interface (buttons & borders)	
	saveButton.setPosition(100, 5);
	saveButton.setFillColor(sf::Color(200, 200, 200, 255));
	
	loadButton.setPosition(250, 5);
	loadButton.setFillColor(sf::Color(200, 200, 200, 255));
	
	loadBackground.setPosition(400, 5);
	loadBackground.setFillColor(sf::Color(200, 200, 200, 255));
	
	border1.setFillColor(sf::Color(100, 100, 100, 255));
	border2.setPosition(660, 0);
	border2.setFillColor(sf::Color(100, 100, 100, 255));

	//Initialise fonts and text
	if (!font.loadFromFile("arial.ttf"))
	{
		//SFML will post an error in the console if font can't be loaded.
	}
	saveText.setFont(font);
	saveText.setString("Save");
	saveText.setCharacterSize(20);
	saveText.setFillColor(sf::Color::Black);
	saveText.setPosition(saveButton.getPosition());

	loadText.setFont(font);
	loadText.setString("Load");
	loadText.setCharacterSize(20);
	loadText.setFillColor(sf::Color::Black);
	loadText.setPosition(loadButton.getPosition());

	backgroundText.setFont(font);
	backgroundText.setString("Background");
	backgroundText.setCharacterSize(18);
	backgroundText.setFillColor(sf::Color::Black);
	backgroundText.setPosition(loadBackground.getPosition());

	// Initialise defaults for editor buttons
	for (int i = 0; i < NUMBEROFRECTS; ++i)
	{
		editorBricks[i].setSize(sf::Vector2f(100, 50));
		editorBricks[i].setPosition(680, (50 + i * 100));
		editorBricks[i].setFillColor(colors[i]);
		editorBricks[i].setOutlineThickness(5.0);
		editorBricks[i].setOutlineColor(sf::Color::White);
	}
		
	return true;
}

void App::Update()
{
	// update
	float deltaTime = Clock.restart().asSeconds();
	bool collisionDetected = false;
	
	// Dectect if brick is outside of game area (off screen or on the menu bar)
	// Left border collision detection
	if (newBricks[currentBrickNumber] != nullptr)
	{
		// move current brick to the position of the cursor
		newBricks[currentBrickNumber]->setPosition(localMousePosition.x, localMousePosition.y);

		// Left border collision detection
		if (newBricks[currentBrickNumber]->getPosition().x <= 0)
		{
			collisionDetected = true;
		}

		// Right border collision detection
		if (newBricks[currentBrickNumber]->getPosition().x >= 
			window.getSize().x - border2.getSize().x - newBricks[currentBrickNumber]->getSize().x)
		{
			collisionDetected = true;
		}

		// Top border collision detection
		if (newBricks[currentBrickNumber]->getPosition().y <= border1.getSize().y)
		{
			collisionDetected = true;
		}

		// Bottom border collision detection
		if (newBricks[currentBrickNumber]->getPosition().y >= 
			window.getSize().y - newBricks[currentBrickNumber]->getSize().y)
		{
			collisionDetected = true;
		}

		// Detect collision with other bricks
		for (int i = 0; i < MAXBRICKS; i++)
		{
			if (newBricks[i] != nullptr)
			{
				// Skip this step if current brick is equal to i as this would check if a brick 
				// intersects itself...
				if (currentBrickNumber != i)
				{
					newBricks[i]->setOutlineColor(newBricks[i]->getFillColor());

					if (newBricks[currentBrickNumber]->getGlobalBounds().intersects
					(newBricks[i]->getGlobalBounds()))
					{
						collisionDetected = true;
					}
				}
			}
		}

		if (collisionDetected)
		{
			newBricks[currentBrickNumber]->setOutlineColor(sf::Color::Red);

			if (!leftMouseButton)
			{
				newBricks[currentBrickNumber] = nullptr;
			}
		}
		else
		{
			newBricks[currentBrickNumber]->setOutlineColor(sf::Color::White);
		}
	}
}

void App::Draw()
{	
	window.clear();
	window.setView(view);

	// draw menu interface
	window.draw(background);
	window.draw(border1);
	window.draw(border2);
	window.draw(saveButton);
	window.draw(loadButton);
	window.draw(loadBackground);
	
	// draw text
	window.draw(saveText);
	window.draw(loadText);
	window.draw(backgroundText);
	
	// draw editor brick buttons
	for (int i = 0; i < NUMBEROFRECTS; i++)
	{
		window.draw(editorBricks[i]);
	}

	// draw bricks
	for (int i = 0; i < MAXBRICKS; i++)
	{
		if(newBricks[i] != nullptr)
			window.draw(*newBricks[i]);
	}

	window.display();
}

void App::HandleEvents()
{
	if (event.type == sf::Event::Closed)
		window.close();

	// other keyboard, mouse events
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	// do something if the left mouse button is clicked.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		leftMouseButton = true;
		// Get the local mouse position (relative to a window)
		localMousePosition = sf::Mouse::getPosition(window);

		//Menu Interactions
		//TODO: for all elements in Menu Interactions, when buttons are pressed find files using windows explorer 
		//	instead of typing file names and having to put the files in the same folder as the project

		//clicking the save button
		if (saveButton.getGlobalBounds().contains(localMousePosition.x, localMousePosition.y))
		{
			// onbutton down
			if (save)
			{
				save = false;
				//save the level to a file
				WriteToFile();
			}
		}

		//clicking the load button
		if (loadButton.getGlobalBounds().contains(localMousePosition.x, localMousePosition.y))
		{
			// onbutton down
			if (load)
			{
				load = false;
				//load the level
				ReadFromFile();
			}
		}

		//clicking the background button
		if (loadBackground.getGlobalBounds().contains(localMousePosition.x, localMousePosition.y))
		{
			// onbutton down
			if (changeBackground)
			{
				changeBackground = false;
				//change the background
				cout << "Type in the full name of the background file, including the .filetype." << endl;
				cout << "Also be sure to put the background image file in the same folder as the Main.cpp file." << endl;
				cin >> backgroundname;
				SetBackground();
			}
		}

		//Create bricks
		for (int i = 0; i < NUMBEROFRECTS; i++)
		{
			// Check if the editor bricks were pressed
			if (editorBricks[i].getGlobalBounds().contains(localMousePosition.x, localMousePosition.y))
			{
				//onbuttondown check
				if (createBrick)
				{
					// Create a moveable bring with the same settings as the editor brick
					sf::Color editorBrickColor;
					editorBrickColor = editorBricks[i].getFillColor();
					editorBricks[i].setOutlineColor(sf::Color::Blue);

					// Set nonselected editor brick borders back to white
					int skipbrick = i;
					for (int o = 0; o < NUMBEROFRECTS; o++)
					{
						if (o != skipbrick)
						{
							editorBricks[o].setOutlineColor(sf::Color::White);
						}
					}

					//create brick and add to newbricks array
					AddBrick(new sf::RectangleShape(sf::Vector2f(100, 50)), editorBrickColor, &currentBrickNumber);
					createBrick = false;
				}
			}
		}

		// Check if user is clicking on an already existing brick
		for (int i = 0; i < MAXBRICKS; i++)
		{
			if (newBricks[i] != nullptr)
			{
				// If user clicks on a brick, set that brick as the currently selected brick;
				if (newBricks[i]->getGlobalBounds().contains(localMousePosition.x,localMousePosition.y))
				{
					currentBrickNumber = i;
				}
			}
		}
	}
	else
	{
		// Allow the users to use onbuttondown events
		changeColor = true;
		createBrick = true;
		save = true;
		load = true;
		changeBackground = true;
		leftMouseButton = false;
	}

	// do something if the right mouse button is clicked.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		rightMouseButton = true;
		// The local mouse position (relative to a window)
		localMousePosition = sf::Mouse::getPosition(window);

		// if statement turns isbuttonpressed into onbuttondown.
		if (deleteBrick)
		{
			deleteBrick = false;
			// Delete clicked on object
			for (int i = 0; i < MAXBRICKS; i++)
			{
				if (newBricks[i] != nullptr)
				{
					if (newBricks[i]->getGlobalBounds().contains(localMousePosition.x, localMousePosition.y))
					{
						newBricks[i] = nullptr;
					}
				}
			}
		}
	}
	else
	{
		// Allow user to destroy bricks again.
		deleteBrick = true;
		rightMouseButton = false;
	}
}

void App::Run()
{
	// Runs the program
	Init();
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			HandleEvents();
		}
		Update();
		Draw();
	}
}

bool App::WriteToFile()
{
	string filename;

	cout << "Enter a name for the save file: ";
	cin >> filename;

	ofstream out(filename);

	// check if file is open
	if (!out)
	{
		cout << "\n\nCannot oen file!\n\n";
		cin.get();
		return false;
	}

	// write to the file
	//out << "Number" << "\t" << "Xposition" << "\t" << "Yposition" << "\t" << "RColor" << "\t" << "GColor" << "\t" << "BColor" << endl;

	// Get the location, and color of the bricks (size is always the same), file data format below:
	// number	x position	y position	color(color contains r,g,b values)
	for (int i = 0; i < MAXBRICKS; i++)
	{
		if (newBricks[i] != nullptr)
		{
			int red = newBricks[i]->getFillColor().r;
			int green = newBricks[i]->getFillColor().g;
			int blue = newBricks[i]->getFillColor().b;
			// input to file the number of the brick (index in array), the x position, and the y position
			out << i << " " << newBricks[i]->getPosition().x << " " << newBricks[i]->getPosition().y << " ";
			// input to file the color (r,g,b) (does not include alpha because alpha is always 255; (these aren't returned as floats)
			out << red << " " << green << " " << blue;
			out << endl;
		}
		else
		{
			out << "-52 -52 -52 -52 -52 -52" << endl;
		}
	}

	out << "end file" << endl << endl;

	// close the file.
	out.close();

	cout << "File has be saved" << endl;

	return true;
}

bool App::ReadFromFile()
{
	int number;
	int xposition;
	int yposition;
	int rcolor;
	int gcolor;
	int bcolor;
	char filename[15];
	bool nullRef;

	for (int i = 0; i < MAXBRICKS; i++)
	{
		newBricks[i] = nullptr;
	}

	// Get file name
	cout << "Enter the name of the file you would like to load: ";
	cin >> filename;

	//Declare and initialise our input stream.
	ifstream infile;
	infile = ifstream(filename);

	//check if file is open for reading.
	if (!infile)
	{
		cout << "\n\nCannot open file!\n\n";
		cin.get();
		return false;
	}

	char str[255];

	//Reads the values from file into a 2D array
	int my_array[20][6]{};
	for (int col = 0; col < 20; ++col)
	{
		nullRef = false;
		for (int row = 0; row < 6; ++row)
		{
			infile >> my_array[col][row];
			cout << my_array[col][row];
			if (row != 5)
			{
				cout << ", ";
			}
			else
			{
				cout << endl;
			}

			if (row == 0 && my_array[col][row] == -52)
			{
				nullRef = true;
			}
			else
			{
				if (row == 0)
					number = my_array[col][row];
				if (row == 1)
					xposition = my_array[col][row];
				if (row == 2)
					yposition = my_array[col][row];
				if (row == 3) 
					rcolor = my_array[col][row];
				if (row == 4)
					gcolor = my_array[col][row];
				if (row == 5)
					bcolor = my_array[col][row];
			}
		}

		cout << "Number: " << number <<
			"\t Position: (" << xposition << "," << yposition << ")\tColor: (" <<
			rcolor << "," << gcolor << "," << bcolor << ")" << endl;

		if (!nullRef)
		{
			// Recreate bricks
			AddBrick(new sf::RectangleShape(sf::Vector2f(100, 50)),sf::Color(rcolor,gcolor,bcolor,255),&number);
			newBricks[number]->setPosition(xposition, yposition);
			cout << endl << "Brick Recreated!" << endl;
		}

		cout << endl;
	}
	cout << endl << endl << endl;
	
	cout << "File has be loaded" << endl;

	return true;
}

int App::AddBrick(sf::RectangleShape *brick,sf::Color color,int *brickNumber)
{
	// Search for a free spot in the array to put new brick
	for (int i = 0; i < MAXBRICKS; i++)
	{
		if (newBricks[i] != nullptr)
		{
			// Do nothing, check next element in array
		}
		else
		{
			// Create new brick and add to array
			newBricks[i] = brick;
			*brickNumber = i;
			brick->setFillColor(color);
			brick->setOutlineThickness(5.0);
			brick->setOutlineColor(sf::Color::White);
			return i;
			break;
		}
	}
	// Notify player that there are no more free slots to put new brick.
	cout << "Max number of bricks reached" << endl;
	return 0;
}

int App::SetBackground()
{
	if (!backgroundTexture.loadFromFile(backgroundname))
	{
		//SFML will print an error on the console if file is not found or unable to open.
		return 1;
	}
	else
	{
		TextureSize = backgroundTexture.getSize(); //Get size of texture.
		WindowSize = window.getSize();             //Get size of window.

		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

		background.setTexture(backgroundTexture);
		background.setScale(ScaleX, ScaleY);      //Set scale.  
	}
	return 0;
}

