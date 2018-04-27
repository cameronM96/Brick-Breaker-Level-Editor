// Moving a Circle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "App.h"

using namespace std;

int main()
{
	char name[13] = { 'L','e','v','e','l',' ','E','d','i','t','o','r' };
	App Game(name, 800, 600, 32);

	if (!Game.Init())
	{
		printf("Game could not be started!");
		return 1;
	}
	else
	{
		Game.Run();
	}
	return 0;
}