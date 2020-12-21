#include "game.h"


//初始化棋盘
void InitBoard(char arr[ROWS][COLS], int row, int col, char val)
{
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			arr[i][j] = val;
		}
	}
}

//展示棋盘
void ShowBoard(char arr[ROWS][COLS], int row, int col) {
	for (int i = 0;i <= row;++i) {
		//显示行号
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 1;i <= row;i++) {
		//显示列号
		printf("%d ", i);
		for (int j = 1;j <= col;j++) {
			if (arr[i][j] >= '1' && arr[i][j] < '9') {
				//显示红色的字符 printf("\033[40;31m  \033[0m");--》表示打印带有颜色的内容
				printf("\033[40;31m%c \033[0m", arr[i][j]);
			}
			else {
				printf("%c ", arr[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

//生成雷
void GenerateMine(char arr[ROWS][COLS], int row, int col, int difficulty) {
	while (difficulty) {
		//随机生成雷的x，y坐标
		int i = rand() % row + 1;
		int j = rand() % col + 1;
		if (arr[i][j] == '0') {
			arr[i][j] = '1';
			--difficulty;
		}
	}
}

//获取(x,y)处周围雷的数量 
int GetMine(char mine[ROWS][COLS], int i, int j) {
	//八个方向的坐标
	int n = mine[i - 1][j - 1] + mine[i - 1][j] + mine[i - 1][j + 1] + mine[i][j - 1] + mine[i][j + 1] +
		mine[i + 1][j - 1] + mine[i + 1][j] + mine[i + 1][j + 1];
	//减‘0’是将其变为int类型的数字
	return n - 8 * '0';
}

//遇到周围没有雷时，对周围进行展开搜索雷的数目
void SearchMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j) {
	//规定边界
	if (i<1 || i>ROW || j<1 || j>COL) {
		return;
	}
	show[i][j] = ' ';
	//设置8个方向的坐标
	int posArr[8][2] = { {i - 1,j - 1},{i - 1,j},{i - 1,j + 1},{i,j - 1},{i ,j + 1}
		,{i + 1,j - 1},{i + 1,j},{i + 1,j + 1} };
	for (int k = 0;k < 8;k++) 
	{
		int row = posArr[k][0];
		int col = posArr[k][1];

		//已经搜索过的位置不再探索
		if ((show[row][col] >= '1' && show[row][col] <= '8') || show[row][col] == ' ') {
			continue;
		}

		//1.如果此方向周围一圈都有雷，则显示雷的数量，不再进行探索
		//2.如果此方向一圈没有雷，则递归的继续往他的周边进行探索，直到周围一圈都有雷为止
		int mineNum = 0;
		mineNum = GetMine(mine, row, col);
		if (mineNum > 0) {
			//+'0'是将其变为字符类型的数字
			show[row][col] = mineNum + '0';
		}
		else {
			SearchMine(mine, show, row, col);
		}
	}
}