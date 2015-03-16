#include<conio.h>
#include "Display.h"
#include<time.h>

#define true 1
#define false 0

#define GAMEWAIT 100
#define SPECIAL 1
#define NORMAL 0

#define EASY 150
#define NORMAL 100
#define HARD 20
#define VET 0

int difficulty = NORMAL;
int score = 0;
int highscore = 0;
int eatenCount=0;

Food GenerateFood(Snake*, char);
void PrintFood(Food);
int CheckEaten(Food, Snake);
int PlayAgain(int);
void RunGame(Snake*, Food *, int*);
int MainMenu();
void ChooseDiff();
void HighScore();
void SaveHS();
void UpdateScoreNormal();
void UpdateScoreSpecial();
void ReadHS();
void DiffMenu();

Snake Initialize() //initializes properties of the snake
{
	int i, xpos = 40;
	char rep = ':'; //representation of the snake body segment
	Snake snake;
	
	snake.length = 5;

	for (i=0;i<=snake.length-1;i++)
	{
		snake.Body[i].rep = rep;
		rep = ' ';
		snake.Body[i].xPos = xpos;
		snake.Body[i].yPos = 10;
		xpos++;
	}

	snake.headPosX = snake.Body[0].xPos;  //initializes the position of the head of the snake as the position of the first in the array
	snake.headPosY = snake.Body[0].yPos;
	

	return snake;
}

void MoveLeft(Snake*snake, Direction*dir, int*quit) //changes the position of the head of the snake left on the X axis
{
	int i;
	Snake snakeBuff;

	snakeBuff = *snake;
	PrintSnake(snakeBuff);

	if(snake->Body[0].xPos <= snake->Body[1].xPos && dir->moveL == true)
		{
		
			for(i=snake->length-1;i>=1;i--)
			{
				snake->Body[i].xPos = snake->Body[i-1].xPos;
				snake->Body[i].yPos = snake->Body[i-1].yPos;
			}
			snake->headPosX--;
			snake->Body[0].xPos = snake->headPosX; //updates position at segment 0 as head
			LineBorder();
			Sleep(difficulty);
			if(Collision(snake) == true) //checks if snake head has reached the boundary of gameplay
			{
				*quit = true;
			}
			else
			{
				DeleteSnake(snakeBuff);
				PrintSnake(*snake);
			}

		}
}

void MoveUp(Snake *snake, Direction*dir, int*quit) //changes the position of the head of the snake up on the Y axis
{
	int i/* move = false*/;

	Snake snakeBuff;

	snakeBuff = *snake;
	PrintSnake(snakeBuff);

	if (snake->Body[0].yPos <= snake->Body[1].yPos && dir->moveU == true)
	{
		for(i=snake->length-1;i>=1;i--)
		{
			snake->Body[i].xPos = snake->Body[i-1].xPos;
			snake->Body[i].yPos = snake->Body[i-1].yPos;
		}	
		snake->headPosY--;
		snake->Body[0].yPos = snake->headPosY; //updates position at segment 0 as head
		LineBorder();
		Sleep(difficulty);

		if(Collision(snake) == true) //checks if snake head has reached the boundary of gameplay
		{
			*quit = true;
		}
		else
		{
			DeleteSnake(snakeBuff);
			PrintSnake(*snake);
		}
	}
}

void MoveDown(Snake *snake,  Direction*dir, int*quit) //changes the position of the head of the snake down on the Y axis
{
	int i;

	Snake snakeBuff;

	snakeBuff = *snake;
	PrintSnake(snakeBuff);

	if (snake->Body[0].yPos >= snake->Body[1].yPos && dir->moveD == true)
	{
		
		for(i=snake->length-1;i>=1;i--)
		{
			snake->Body[i].xPos = snake->Body[i-1].xPos;
			snake->Body[i].yPos = snake->Body[i-1].yPos;
		}	
		snake->headPosY++;
		snake->Body[0].yPos = snake->headPosY; //updates position at segment 0 as head
		LineBorder();
		Sleep(difficulty);
		if(Collision(snake) == true) //checks if snake head has reached the boundary of gameplay
		{
			*quit = true;
		}
		else
		{
			DeleteSnake(snakeBuff);
			PrintSnake(*snake);
		}
			
	}
}

void MoveRight(Snake *snake,  Direction*dir, int*quit) //changes the position of the head of the snake right on the X axis
{
	int i;

	Snake snakeBuff;

	snakeBuff = *snake;
	PrintSnake(snakeBuff);

	if(snake->Body[0].xPos >= snake->Body[1].xPos && dir->moveR == true)
	{
		
		for(i=snake->length-1;i>=1;i--)
		{
			snake->Body[i].xPos = snake->Body[i-1].xPos;
			snake->Body[i].yPos = snake->Body[i-1].yPos;
		}	
		snake->headPosX++;
		snake->Body[0].xPos = snake->headPosX; //updates position at segment 0 as head
		LineBorder();
		Sleep(difficulty);
		if(Collision(snake) == true) //checks if snake head has reached the boundary of gameplay
		{
			*quit = true;
		}
		else
		{
			DeleteSnake(snakeBuff);
			PrintSnake(*snake);
		}
	}
}

int GetKey()
{
	int key, k1;


	k1= getch();

	if (k1 == 224)  //key will only be return if it is a special key(arrow key)
	{
		key = getch();
		return key;
	}
	else
	{
		return k1;
	}

}

void Movement(int key, Snake *snake, Food*food, int*quit)
{
	Direction dir;
	int change;

	switch(key)
	{
	case UP:do
			{
				GameHeader(score, highscore);
				PrintFood(*food);

				dir.moveU = true;
				dir.moveD = false;
				dir.moveL = false;
				dir.moveR = false;
				MoveDown(snake, &dir, quit);
				MoveLeft(snake, &dir, quit);
				MoveRight(snake, &dir, quit);
				MoveUp(snake, &dir, quit);

				if(CheckEaten(*food,*snake) == true) //if the food was eaten a new one is generated
				{
					
					eatenCount+=1;
					snake->length++;
					snake->Body[snake->length-1].xPos = snake->Body[snake->length-2].xPos;
					snake->Body[snake->length-1].yPos = snake->Body[snake->length-2].yPos;
					snake->Body[snake->length-1].rep = ' ';
					if(food->priority == SPECIAL)
					{
						UpdateScoreSpecial();
						HighScore();
					}
					else
					{
						UpdateScoreNormal();
						HighScore();
					}
					if(eatenCount%4==0)
					{
						*food= GenerateFood(snake,'&', SPECIAL);
					}
					else
					{
						//snake->length++;
						//snake->Body[snake->length-1].rep = ' ';
						*food= GenerateFood(snake,'*', NORMAL);
					}
					

				}

				if(*quit == true)
				{
					break;
				}


			}while(!kbhit());

			break;
	case DOWN:	do
				{
					GameHeader(score, highscore);
					PrintFood(*food);

					dir.moveD = true;
					dir.moveU = false;
					dir.moveL = false;
					dir.moveR = false;
					MoveUp(snake, &dir, quit);
					MoveLeft(snake, &dir, quit);
					MoveRight(snake, &dir, quit);
					MoveDown(snake, &dir, quit);

					if(CheckEaten(*food,*snake) == true) //if the food was eaten a new one is generated
					{
						
						
						snake->length++;
						snake->Body[snake->length-1].xPos = snake->Body[snake->length-2].xPos;
						snake->Body[snake->length-1].yPos = snake->Body[snake->length-2].yPos;
						snake->Body[snake->length-1].rep = ' ';
						eatenCount+=1;
						if(food->priority == SPECIAL)
						{
							UpdateScoreSpecial();
							HighScore();
						}
						else
						{
							UpdateScoreNormal();
							HighScore();
						}
						if(eatenCount%4==0)
						{
							*food= GenerateFood(snake,'&', SPECIAL);
						}
						else
						{
							*food= GenerateFood(snake,'*', NORMAL);
						}
						
					}

					if(*quit == true)
					{
						break;
					}


				}while(!kbhit());

			break;
		case LEFT:	do
					{
						
						GameHeader(score, highscore);
						PrintFood(*food);

						dir.moveL = true;
						dir.moveU = false;
						dir.moveD = false;
						dir.moveR = false;
						MoveUp(snake, &dir, quit);
						MoveDown(snake, &dir, quit);
						MoveRight(snake, &dir, quit);
						MoveLeft(snake, &dir, quit);

						if(*quit == true)
						{
							break;
						}
						if(CheckEaten(*food,*snake) == true) //if the food was eaten a new one is generated
						{
							
							snake->length++;
							snake->Body[snake->length-1].xPos = snake->Body[snake->length-2].xPos;
							snake->Body[snake->length-1].yPos = snake->Body[snake->length-2].yPos;
							snake->Body[snake->length-1].rep = ' ';
							eatenCount+=1;
							if(food->priority == SPECIAL)
							{
								UpdateScoreSpecial();
								HighScore();
							}
							else
							{
								UpdateScoreNormal();
								HighScore();
							}
							if(eatenCount%4==0)
							{
								*food= GenerateFood(snake,'&', SPECIAL);
							}
							else
							{
								*food= GenerateFood(snake,'*', NORMAL);
							}
							
						}

					}while(!kbhit());

			break;
		case RIGHT:do
					{

						GameHeader(score, highscore);
						PrintFood(*food);

						dir.moveR = true;
						dir.moveU = false;
						dir.moveD = false;
						dir.moveL = false;
						MoveUp(snake, &dir, quit);
						MoveDown(snake, &dir, quit);
						MoveLeft(snake, &dir, quit);
						MoveRight(snake, &dir, quit);

						if(*quit == true)
						{
							break;
						}
						
						if(CheckEaten(*food,*snake) == true) //if the food was eaten a new one is generated
						{
							snake->length++;
							snake->Body[snake->length-1].xPos = snake->Body[snake->length-2].xPos;
							snake->Body[snake->length-1].yPos = snake->Body[snake->length-2].yPos;
							snake->Body[snake->length-1].rep = ' ';
							eatenCount+=1;
							if(food->priority == SPECIAL)
							{
								UpdateScoreSpecial();
								HighScore();
							}
							else
							{
								UpdateScoreNormal();
								HighScore();
							}

							if(eatenCount%4==0)
							{
								*food= GenerateFood(snake,'&', SPECIAL);
							}
							else
							{
								*food= GenerateFood(snake,'*', NORMAL);
							}
						}


					}while(!kbhit());
	}
}

void RunGame(Snake*snake, Food*food,int*quit)
{ 
	GameHeader(score, highscore);
	PrintFood(*food);
	Movement(GetKey(), snake, food,quit);	
}

int Collision(Snake*snake) //checks if snake head has reached the boundary of gameplay
{
	int col = false, i;

	if(snake->headPosX == 5 || snake->headPosX == XSPACE || snake->headPosY==1 || snake->headPosY==24)
	{
		col = true;
	}

	for(i=1;i<=snake->length-1;i++)
	{
		if(snake->Body[0].xPos == snake->Body[i].xPos && snake->Body[0].yPos == snake->Body[i].yPos)
		{
			col = true;
		}
	}

	return col;

}

//FOOD AND GROWING FUNCTIONS

Food GenerateFood(Snake*snake, char rep, int priority)
{
	Food f;
	int i, equal = false, x = XSPACE-1, y = WINDOWHEIGHT-1 ;

	srand(time(NULL));

	do
	{
		f.xPos = rand() % (x-6)+6;
		f.yPos = rand() % (y-3)+3;
		f.rep = rep;
		f.eaten = false;
		f.priority = priority;

		for (i=0;i<=snake->length;i++)
		{
			if(snake->Body[i].xPos == f.xPos && snake->Body[i].yPos == f.yPos)
			{
				equal = true;
			}
		}
	}while(equal != false);

	return f;
}

void PrintFood(Food food)
{
	gotoxy(food.xPos, food.yPos);
	printf("%c", food.rep);
}
		
int CheckEaten(Food food, Snake snake) //checks is food has been eaten by snake
{
	int eaten = false;
	if(snake.headPosX == food.xPos && snake.headPosY == food.yPos)
	{
		eaten = true;
	}
	
	return eaten;
}

int PlayAgain(int score)
{
	int choice;

	printf("Press Enter to Play Again");
	choice = getch();

	if(choice == 13)
	{
		return true;
	}
	else
	{
		exit(0);
	}
}

void EndGame(int score)
{
	int i;

	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen
	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen

	Sleep(1000);
	system("cls");

	SetConsoleTextAttribute(hColour, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);

	for(i=20;i<=60;i++)
	{
		gotoxy(i, 5); //top border
		printf(" ");
		gotoxy(i, WINDOWHEIGHT); //lower border
		printf(" ");
	}
	for(i=5;i<= WINDOWHEIGHT ;i++)
	{
		gotoxy(20, i); //left border
		printf(" ");
		gotoxy(60, i); //right border
		printf(" ");
	}

	SetConsoleTextAttribute(hColour, original);

	gotoxy(25, 10);
	printf("GAME OVER\n");
	gotoxy(25, 15);
	printf("Final Score: %i", score);
	gotoxy(25, 20);
	printf("High Score: %i", highscore);
	Sleep(2500);
}

/*int MainMenu(Snake* snake, Food* food, int* play)
{
	int i, choice, quit = false;
	FILE *fp;
	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen

	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen

	system("cls");

	SetConsoleTextAttribute(hColour, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	PrintBorder(20, 60, 5, WINDOWHEIGHT);
	SetConsoleTextAttribute(hColour, original);

	gotoxy(25, 10);
	puts("[1] Play");
	gotoxy(25, 15);
	puts("[2] Difficulty");
	gotoxy(25, 20);
	puts("[3] Exit");

	gotoxy(25, 27);
	puts("Choice: ");
	fflush(stdin);
	scanf("%i", &choice);
	fflush(stdin);

	switch(choice)
	{
		case 1: 
				system("cls");
				LineBorder();
				PrintSnake(*snake);
				eatenCount = 0;
				if((fp = fopen("highscore.txt", "rb")) == NULL)
				{
					SaveHS();
					fclose(fp);
				}
				else
				{
					ReadHS();
				}
		
				while(quit == false)
				{
					RunGame(snake, food, &quit);
					if(quit == true)
					{
						EndGame(score);
						*snake = Initialize();
						score = 0;
						quit = false;
					}
					SaveHS();
				}
				break;
		
		case 2:	
				DiffMenu();
				Sleep(1000);
				break;
			
		case 3:
				system("cls");
				*play == false;
				GameCloseScreen();
				break;
   
		default:
				system("cls");
				gotoxy(25, 15);
				printf("Invalid Option");
				Sleep(2500);
	}
}*/

int MainMenu(Snake*snake,Food* food, int*play)
{
	int i, choice, quit = false;
	char choiceBuffer[5];
	FILE *fp;

	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen
	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen

mainMenu:
	system("cls");

	SetConsoleTextAttribute(hColour, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	PrintBorder(20,60,5, WINDOWHEIGHT);
	SetConsoleTextAttribute(hColour, original);

	gotoxy(25, 10);
	printf("[1] Play");
	gotoxy(25, 15);
	printf("[2] Difficulty");
	gotoxy(25, 20);
	printf("[3] Exit");

	gotoxy(25, 27);
	printf("Choice: ");
	fflush(stdin);
	scanf("%s", choiceBuffer);
	
	if(checkString(choiceBuffer) == true)
	{
		goto invalidOpMain;
	}
	else
	{
		choice = atoi(choiceBuffer);
	}

	switch(choice)
	{
	case 1: system("cls");
			LineBorder();
			PrintSnake(*snake);
			eatenCount=0;
		    if((fp = fopen("highscore.txt", "rb"))==NULL)
			{
				SaveHS();
			}
			else
			{
				ReadHS();
			}
			while(quit == false)
			{
				RunGame(snake, food, &quit);
				if(quit == true)
				{
					EndGame(score);
					*snake = Initialize();
					score = 0;
					//quit = false;
					//goto mainMenu;
					MainMenu(snake, food, play);
				}
				SaveHS();
			}
			break;
	case 2: DiffMenu();
			Sleep(1000);
			break;
			
			
	case 3:system("cls");
		  *play == false;
		  GameCloseScreen();
		break;
   default:invalidOpMain:  //if a string is entered for the case then invalid op is called
			system("cls");
			gotoxy(25,15);
			printf("Invalid Option");
			Sleep(2500);
			MainMenu(snake,food, play);
	}

}


void ChooseDiff()
{
	char choiceBuffer[10];
	int choice;

Diff:

	gotoxy(25, 10);
	printf("[1] Easy");
	gotoxy(25, 15);
	printf("[2] Normal");
	gotoxy(25, 20);
	printf("[3] Hard");
	gotoxy(25, 25);
	printf("[4] Veteran");


	gotoxy(25, 30);
	printf("Choice: ");
	fflush(stdin);
	scanf("%s", choiceBuffer);
	
	if(checkString(choiceBuffer) == true)
	{
		goto invalidOpDiff;
	}
	else
	{
		choice = atoi(choiceBuffer);
	}

	switch (choice)
	{
	case 1: difficulty = EASY;
		break;
	case 2: difficulty = NORMAL;
		break;
	case 3: difficulty = HARD;
		break;
	case 4: difficulty = VET;
		break;
	default: 
			invalidOpDiff:  //if a string is entered for the case then invalid op is called
			system("cls");
			gotoxy(25,15);
			printf("Invalid Option");
			Sleep(2500);
			DiffMenu();
			//goto Diff;
	}

}

int checkString(char *string) //checks if input was a string
{
	int i, isString = true;

	for (i=0;i<=strlen(string);i++)
	{
		if(isdigit(string[i]))
		{
			isString = false;
			break;
		}
		fflush(stdin);
		return isString;
	}
}

void HighScore() //updates highscore
{
	if(score>=highscore)
	{
		highscore = score;
	}
}

void SaveHS() //saves the highscore to file
{
	FILE *fp;

	if((fp =fopen("highscore.txt", "wb")) == NULL)
	{
		fprintf(stderr, "\a\a\a\n\nFile could not be opened\n"); //fix/find out real purpose
	}
	else
	{
		fwrite(&highscore, sizeof(int), 1 ,fp);
	}
	fclose(fp);
}

void ReadHS() //reads the highscore from file
{
	FILE *fp; 

	if((fp = fopen("highscore.txt", "rb"))==NULL) 
	{
		fprintf(stderr, "\a\a\a\n\nFile could not be opened\n");
	}
	else 
	{
		while(!feof(fp))
		{
			fread(&highscore, sizeof(int), 1 ,fp); 
		}
		
	}
	fclose(fp);	
}

void UpdateScoreNormal()
{
	switch(difficulty)
	{
	case EASY : score+=1;
		break;
	case NORMAL: score+=2;
		break;
	case HARD: score+=3;
		break;
	case VET: score+=4;
	}		
}

void UpdateScoreSpecial()
{
	switch(difficulty)
	{
	case EASY : score+=5;
		break;
	case NORMAL: score+=7;
		break;
	case HARD: score+=10;
		break;
	case VET: score+=13;
	}		
}

void DiffMenu()
{
	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen
	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen

	system("cls");
	SetConsoleTextAttribute(hColour, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	PrintBorder(20,60,5, 27);
	SetConsoleTextAttribute(hColour, original);
	ChooseDiff();
	Sleep(500);
	gotoxy(25, 33);
	printf("Difficulty Changed");
}