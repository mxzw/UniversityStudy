#define _CRT_SECURE_NO_WARNINGS；

#include"game.h"
#include<stdlib.h>

int main() {
	//系统清屏函数--》为了后面能打印出带有颜色的数字
	system("cls");
	char mine[ROWS][COLS];
	char show[ROWS][COLS];

	//'0'表示没有雷
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//加入随机化种子，使每次打开雷的位置都在变化
	//srand(time(0));
	GenerateMine(mine, ROW, COL, EASY);
	ShowBoard(mine, ROW, COL);
	

	while (1)
	{
		ShowBoard(show, ROW, COL);
		printf("请输入你要展开的坐标：");
		int i, j;
		scanf("%d %d", &i, &j);
		if (i<1 || i>ROW || j<1 || j>COL || show[i][j] != '*') {
			printf("输入坐标有误，请重新输入\n");
			continue;
		}

		if (mine[i][j] == '1') {
			printf("game over\n");
			ShowBoard(mine, ROW, COL);
			break;
		}
		else {
			int mineNum = GetMine(mine, i, j);
			if (mineNum == 0) {
				SearchMine(mine, show, i, j);
			}
			else {
				show[i][j] = mineNum + '0';
				ShowBoard(show, ROW, COL);
			}
		}
	}
	return 0;
}