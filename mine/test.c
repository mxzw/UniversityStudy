#define _CRT_SECURE_NO_WARNINGS��

#include"game.h"
#include<stdlib.h>

int main() {
	//ϵͳ��������--��Ϊ�˺����ܴ�ӡ��������ɫ������
	system("cls");
	char mine[ROWS][COLS];
	char show[ROWS][COLS];

	//'0'��ʾû����
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//������������ӣ�ʹÿ�δ��׵�λ�ö��ڱ仯
	//srand(time(0));
	GenerateMine(mine, ROW, COL, EASY);
	ShowBoard(mine, ROW, COL);
	

	while (1)
	{
		ShowBoard(show, ROW, COL);
		printf("��������Ҫչ�������꣺");
		int i, j;
		scanf("%d %d", &i, &j);
		if (i<1 || i>ROW || j<1 || j>COL || show[i][j] != '*') {
			printf("����������������������\n");
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