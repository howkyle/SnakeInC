#define MAX 1000

typedef struct
{
	int xPos;
	int yPos;
	char rep;
}Segment;

typedef struct
{
	Segment Body[MAX];
	int headPosX; //position of the head of the snake
	int headPosY;
	int length;
}Snake;

typedef struct
{
	int xPos;
	int yPos;
	char rep;
	int eaten; //whether food has been 'eaten' by snake
	int priority;
}Food;

typedef struct
{
	int moveU;
	int moveD;
	int moveL;
	int moveR;
}Direction;