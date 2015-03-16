#include<Windows.h>
#include "SnakeProperties.h"

#define WINDOWHEIGHT 24 //height of window
#define XSPACE 75

#define UP 72
#define LEFT 75
#define RIGHT 77  //KEYCODES FOR ARROW KEYS
#define DOWN 80


//Function Prototypes
void PrintChar(int , char);
void PrintNewline();
void PrintNewTab();
void SpacesDown(int);
void TabsAcross(int);
void MoveCursorTabs(int , int );
void MoveCursorSpaces(int , int );
void PrintSnake(Snake);
void EndGame(int);
void GameHeader(int, int );
void gotoxy(int, int);
void DeleteSnake(Snake);
void LineBorder();




void PrintChar(int num, char character)
 {
	 int i;

	 for(i=1;i<=num;i++)
	 {
		 printf("%c", character);
	 }
 }

void PrintNewline()
{
	printf("\n");
}

void PrintNewTab()
{
	printf("\t");
}

void PrintNewSpace()
{
	printf(" ");
}

void SpacesAcross(int num)
{
	int i;
	for(i=1;i<=num;i++)
	{
		PrintNewSpace();
	}
}

void SpacesDown(int num)
{
	int i;
	for(i=1;i<=num;i++)
	{
		PrintNewline();
	}
}

void TabsAcross(int num)
{
	int i;
	for(i=1;i<=num;i++)
	{
		PrintNewTab();
	}
}

void MoveCursorTabs(int spDown, int tbsAcross)
{
	SpacesDown(spDown);
	TabsAcross(tbsAcross);
}

void MoveCursorSpaces(int spDown, int spAcross)
{
	SpacesDown(spDown);
	SpacesAcross(spAcross);
}

void gotoxy(int x, int y) //moves cursor to position on screen
{
	COORD pos;
	HANDLE H;
	H = GetStdHandle(STD_OUTPUT_HANDLE);

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(H,pos);
}

void PrintSnake(Snake snake) //prints a visual representation of the snake
{
	int i;

	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen
	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen


	SetConsoleTextAttribute(hColour, BACKGROUND_GREEN);

	for(i=0;i<=snake.length-1;i++)
	{
		gotoxy(snake.Body[i].xPos, snake.Body[i].yPos);
		printf("%c", snake.Body[i].rep);
	}

	SetConsoleTextAttribute(hColour,original);

}

void DeleteSnake(Snake snake) //deletes a visual representation of the snake
{
	int i;

	for(i=0;i<=snake.length+1;i++)
	{
		gotoxy(snake.Body[i].xPos, snake.Body[i].yPos);
		printf(" ");
	}
}

void LineBorder() //draws a line to show the boundaries of gameplay
{
	
	int x = XSPACE , y;

	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen
	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen



	SetConsoleTextAttribute(hColour, BACKGROUND_BLUE|BACKGROUND_GREEN);

	for(y = 2; y<WINDOWHEIGHT;y++) //right border
	{
		gotoxy(x, y);
		printf(" \n");
	}

	for(y = 2; y<WINDOWHEIGHT;y++)//left border
	{
		gotoxy(5, y);
		printf(" \n");
	} 

	for(x=5;x<XSPACE+1;x++)//top border
	{
		gotoxy(x, 1);
		printf(" ");
	}

	for(x=5;x<XSPACE+1;x++)//bottom border
	{
		gotoxy(x, WINDOWHEIGHT);
		printf(" ");
	}

	SetConsoleTextAttribute(hColour, original);
}

void GameHeader(int score, int highscore)
{
	gotoxy(30, WINDOWHEIGHT+2);
	printf("C Snake");
	gotoxy(30, WINDOWHEIGHT+4);
	printf("Score: %i", score);
	gotoxy(30, WINDOWHEIGHT+6);
	printf("High Score: %i", highscore);
	gotoxy(10, WINDOWHEIGHT+8);
	printf("Use Arrow Keys to Navigate / Press any other key to pause");

	gotoxy(0, WINDOWHEIGHT+10);
	printf("Developed By Kyle Howard");
}

void PrintBorder(int horizStart,int horizEnd, int vertStart, int vertEnd)
{
	int i;

	for(i=horizStart;i<=horizEnd;i++)
	{
		gotoxy(i, vertStart); //top border
		printf(" ");
		gotoxy(i, vertEnd); //lower border
		printf(" ");
	}
	for(i=vertStart;i<= vertEnd ;i++)
	{
		gotoxy(horizStart, i); //left border
		printf(" ");
		gotoxy(horizEnd, i); //right border
		printf(" ");
	}
}

void GameCloseScreen()
{
	HANDLE hColour = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD original; 
	CONSOLE_SCREEN_BUFFER_INFO consoleAtt;//the current attributes of the console screen
	GetConsoleScreenBufferInfo(hColour, &consoleAtt); //gets the current attributes of the console screen
	original = consoleAtt.wAttributes;//original colour attributes of the console screen

	SetConsoleTextAttribute(hColour, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	PrintBorder(20,60,5, WINDOWHEIGHT);
	SetConsoleTextAttribute(hColour, original);

	gotoxy(25, 15);
	printf("Thank You For Playing Snake in C");
	Sleep(3000);

	exit(0);
}



//FUNCTIONS BORROWED FROM VIDAL
void SetScreenSize(int x, int y)
{
	HANDLE h;
	SMALL_RECT newScreenSize;

	newScreenSize.Left = 0; //(Upper left)
	newScreenSize.Right = x; //(Bottom right)
	newScreenSize.Top = 0;
	newScreenSize.Bottom = y; //Height of window
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(h, TRUE, &newScreenSize);
}

void SetScreenPosition(int x, int y)
{
	HWND a;
	a = GetConsoleWindow();
	MoveWindow(a, x, y, 10, 10, 1);
}