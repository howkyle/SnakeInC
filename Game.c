/* Programmer Kyle Howard
Snake.*/

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"GamePlay.h"


#define true 1
#define false 0



int main()
{
	Snake snake;
	Food food;
	int play = true, dir, option, quit = false; //holds the score of the individual

	SetScreenPosition(300,100);
	SetScreenSize(79, 35);
	system("Title Snake in C");
		

	//start: 
	snake = Initialize();
	food = GenerateFood(&snake,'*', NORMAL); //makes the first instance of food

	do
	{
		MainMenu(&snake, &food, &quit);

	}while(play == true);


	MoveCursorTabs(10,0);

	system("pause");
	return 0;
}


