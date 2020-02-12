#include <iostream>
#include <string>
#include <time.h>
#include "Forest.h"


using namespace std;

Forest::Forest()
{
	srand(time(0));
}

string Forest::NextLocation()
{
	int itemGeneration = 1 + rand() % 30;
	int exitGeneration = 1 + rand() % 10;
	int directionGenerator = 1 + rand() % 5;
	int botGeneration = 1 + rand() % 7;
	if (botGeneration == 7)
	{
		message = "You met the giant spider\n #1. Take the fight in the forest";
	}
	else
	{
		if (itemGeneration == 30)
		{
			message = "You've found item\n #1. Pick up it";
		}
		else
		{
			if (exitGeneration == 10)
			{
				message = "You left the forest\n #1. Exit from forest";
			}
			else
			{
				switch (directionGenerator)
				{
				case 1:
					message = "You keep walking through the forest\n #1. Left #2. Straight";
					break;
				case 2:
					message = "You keep walking through the forest\n #1. Left #2. Right";
					break;
				case 3:
					message = "You keep walking through the forest\n #1. Straight #2. Right";
					break;
				case 4:
					message = "You keep walking through the forest\n #1. Straight";
					break;
				case 5:
					message = "You keep walking through the forest\n #1. Left #2. Straight #3. Right";
					break;
				default:
					message = "Something went wrong\n #1. Straight";
					break;
				}
			}
		}
	}
	return message;
}
