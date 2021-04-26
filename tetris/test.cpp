//#include <stdio.h>
//
//
//void print_board(int aa[][3], int col,int row);
//
//
//int main(void)
//{
//	int ar[3][3] = {
//
//		1,2,3,
//		4,5,6,
//		7,8,9,
//	};
//
//	int col = sizeof(ar[0]) / sizeof(int);
//	int row = sizeof(ar) / sizeof(ar[0]);
//	
//	print_board(ar, col, row);
//
//}
//
//void print_board(int aa[][3], int col, int row)
//{
//	int i,j;
//	for (i = 0; i < row; i++)
//	{
//		for (j = 0; j < col; j++)
//		{
//			printf("%d", aa[i][j]);
//		}
//		printf("\n");
//
//	}
//}

/*
#include <stdio.h>

void main(void)
{
	enum{EMPTY, BRICK, WALL};
	char artile[] = { '. ', 'бс', '##' };

	printf("%c", artile[BRICK]);

}
*/

/*
#include <stdio.h>
#include <Windows.h>

};


void main(void)
{
	int i,j;

	memcpy(stage, game_board[0], sizeof(stage));

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (blocks[3][0][i][j] == 1)
			{
				printf("бс");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
}
*/
