#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand()%(n))
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32
#define ABSX 1
#define ABSY 5

typedef struct tetris {
	int level;
	int gameover;
	int score;
	int rotation;
	int absX, absY;
	int curX, curY;
	int curblock;
	int nextblock;
}Tetris;

void gotoCursor(int x, int y);
void removeCursor();
void print_board(int ar[][14], int col, int row);
void playermove(Tetris* pt);
void remove_preblock(Tetris* pt);
int block_left_check(Tetris* p, int ar[][4][4][4]);
int block_right_check(Tetris* p, int ar[7][4][4][4]);
int block_bottom_check(Tetris* p, int ar[7][4][4][4]);
void block_full_check();

int stage[22][14];
int blocks[7][4][4][4] = {
	{{0,0,0,0, 0,1,0,0, 0,1,1,1, 0,0,0,0}, {0,0,0,0, 0,1,1,0, 0,1,0,0, 0,1,0,0},
	{0,0,0,0, 1,1,1,0, 0,0,1,0, 0,0,0,0}, {0,0,1,0, 0,0,1,0, 0,1,1,0, 0,0,0,0}}, //ㄴ

	{{0,0,0,0, 0,0,1,0, 1,1,1,0, 0,0,0,0}, {0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0, 0,1,1,1, 0,1,0,0, 0,0,0,0}, {0,0,0,0, 0,1,1,0,0,0,1,0,0,0,1,0}}, // ㄴ반대

	{{0,0,0,0, 1,1,0,0, 0,1,1,0, 0,0,0,0},{0,0,1,0, 0,1,1,0, 0,1,0,0, 0,0,0,0},
	{0,0,0,0, 0,1,1,0, 0,0,1,1, 0,0,0,0}, {0,0,0,0, 0,0,1,0, 0,1,1,0, 0,1,0,0}}, //ㄱㄴ

	{{0,0,0,0, 0,0,1,1, 0,1,1,0, 0,0,0,0}, {0,0,0,0, 0,1,0,0, 0,1,1,0, 0,0,1,0},
	{0,0,0,0, 0,1,1,0, 1,1,0,0, 0,0,0,0}, {0,1,0,0, 0,1,1,0, 0,0,1,0, 0,0,0,0}}, //ㄱㄴ 반대

	{{0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0}, {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0},
	{0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0}, {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0}}, //ㅁ

	{{0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0}, {0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0},
	{0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0}, {0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0}}, //ㅡ

	{{0,0,0,0, 0,1,1,1, 0,0,1,0, 0,0,0,0}, {0,0,0,0, 0,0,1,0, 0,1,1,0, 0,0,1,0},
	{0,0,0,0, 0,1,0,0, 1,1,1,0, 0,0,0,0}, {0,1,0,0, 0,1,1,0, 0,1,0,0, 0,0,0,0}} // ㅗ
};

int game_board[22][14] = {
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

int main(void)
{
	randomize();
	//system("cls");
	int i, j, k, block_side_x, block_side_y;
	int col = sizeof(game_board[0]) / sizeof(int);
	int row = sizeof(game_board) / sizeof(game_board[0]);

	Tetris game = { 0,0,0,0,0,0,0,0 };
	Tetris* game_pointer = &game;

	game.absX = ABSX; game.absY = ABSY;

	memcpy(stage, game_board[0], sizeof(stage));

	while (1)
	{
		game.curX = 0; game.curY = 0;
		game.curblock = random(7);
		for (k = 0; k < 18; k++)
		{
			print_board(stage, col, row);
			remove_preblock(game_pointer);
			playermove(game_pointer);
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					if (blocks[game.curblock][game.rotation][i][j] == 1)
					{
						stage[game.absX + i + game.curX][game.absY + j + game.curY] = blocks[game.curblock][game.rotation][i][j];
					}
				}
			}
			Sleep(300);
			system("cls");
			game.curX++;
			if (block_bottom_check(game_pointer, blocks) == 1)
			{
				printf("%d", block_bottom_check(game_pointer, blocks));
				block_full_check();
				break;
			}
		}
		//system("cls");
		//Sleep(100);
	}
}

void gotoCursor(int x, int y) // 커서 위치 이동
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void removeCursor() // 커서 숨김
{
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.bVisible = 0;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void print_board(int ar[][14], int col, int row) // 2차원 배열 출력
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//printf("%d", ar[i][j]);
			if (ar[i][j] == 1)
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
}

void playermove(Tetris* pt)
{
	char ch;

	while (_kbhit()) // 키 입력 없으면 0 있으면 1 
	{
		ch = _getch();
		if (ch == SPACEBAR)
		{
			(*pt).rotation = ((*pt).rotation + 1) % 4;
		}
		else if (ch == LEFT)
		{
			if (block_left_check(pt, blocks) == 1)
			{
				return;
			}
			else
			{
				(*pt).curY = (*pt).curY - 1;
			}
		}
		else if (ch == RIGHT)
		{
			if (block_right_check(pt, blocks) == 1)
			{
				return;
			}
			else
			{
				(*pt).curY = (*pt).curY + 1;
			}
		}
	}
}

void remove_preblock(Tetris *pt)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoCursor((*pt).curX - 1, (*pt).curY);
			if (blocks[(*pt).curblock][(*pt).rotation][i][j] == 1)
			{
				stage[(*pt).absX + i + (*pt).curX - 1][(*pt).absY + j + (*pt).curY] = 0;
			}
		}
	}
}

int block_left_check(Tetris *p, int ar[7][4][4][4])
{
	int i, j, side_max_x = 1, side_max_y = 3;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (ar[(*p).curblock][(*p).rotation][i][j] == 1)
			{
				if (side_max_y >= j)
				{
					side_max_x = i;
					side_max_y = j;
				}
			}
		}
	}
	if (stage[ABSX + side_max_x + (*p).curX][ABSY + side_max_y + (*p).curY - 1] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int block_right_check(Tetris* p, int ar[7][4][4][4])
{
	int i, j, side_max_x = 1, side_max_y = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (ar[(*p).curblock][(*p).rotation][i][j] == 1)
			{
				if (side_max_y <= j)
				{
					side_max_x = i;
					side_max_y = j;
				}
			}
		}
	}
	if (stage[ABSX + side_max_x + (*p).curX][ABSY + side_max_y + (*p).curY + 1] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int block_bottom_check(Tetris* p, int ar[7][4][4][4])
{
	int i, j, k, cnt = 0, ar_x[4] = { 0 }, ar_y[4] = { 0 };

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (ar[(*p).curblock][(*p).rotation][i][j] == 1)
			{
				if (ar[(*p).curblock][(*p).rotation][i+1][j] == 0)
				{
					ar_x[cnt] = i, ar_y[cnt] = j;
					cnt = cnt + 1;
				}
			}
		}
	}
	for (k = 0; k < cnt; k++)
	{
		if (stage[ABSX + ar_x[k] + (*p).curX][ABSY + ar_y[k] + (*p).curY] == 1)
		{
			printf("Asdf sadf ");
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

void block_full_check()
{
	int i,j,k,l, cnt = 0;
	for (i = 1; i < 21; i++)
	{
		for (j = 1; j < 13; j++)
		{
			cnt = cnt + stage[i][j];
		}
		if (cnt == 12)
		{
			for (j = 1; j < 13; j++)
			{
				stage[i][j] = 0;
			}
			for (k = i; k >0; k--)
			{
				for (l = 0; l < 13; l++)
				{
					stage[k][l] = stage[k-1][l];
				}
			}
		}
		cnt = 0;
	}
}