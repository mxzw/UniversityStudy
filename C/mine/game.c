#include "game.h"


//��ʼ������
void InitBoard(char arr[ROWS][COLS], int row, int col, char val)
{
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			arr[i][j] = val;
		}
	}
}

//չʾ����
void ShowBoard(char arr[ROWS][COLS], int row, int col) {
	for (int i = 0;i <= row;++i) {
		//��ʾ�к�
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 1;i <= row;i++) {
		//��ʾ�к�
		printf("%d ", i);
		for (int j = 1;j <= col;j++) {
			if (arr[i][j] >= '1' && arr[i][j] < '9') {
				//��ʾ��ɫ���ַ� printf("\033[40;31m  \033[0m");--����ʾ��ӡ������ɫ������
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

//������
void GenerateMine(char arr[ROWS][COLS], int row, int col, int difficulty) {
	while (difficulty) {
		//��������׵�x��y����
		int i = rand() % row + 1;
		int j = rand() % col + 1;
		if (arr[i][j] == '0') {
			arr[i][j] = '1';
			--difficulty;
		}
	}
}

//��ȡ(x,y)����Χ�׵����� 
int GetMine(char mine[ROWS][COLS], int i, int j) {
	//�˸����������
	int n = mine[i - 1][j - 1] + mine[i - 1][j] + mine[i - 1][j + 1] + mine[i][j - 1] + mine[i][j + 1] +
		mine[i + 1][j - 1] + mine[i + 1][j] + mine[i + 1][j + 1];
	//����0���ǽ����Ϊint���͵�����
	return n - 8 * '0';
}

//������Χû����ʱ������Χ����չ�������׵���Ŀ
void SearchMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j) {
	//�涨�߽�
	if (i<1 || i>ROW || j<1 || j>COL) {
		return;
	}
	show[i][j] = ' ';
	//����8�����������
	int posArr[8][2] = { {i - 1,j - 1},{i - 1,j},{i - 1,j + 1},{i,j - 1},{i ,j + 1}
		,{i + 1,j - 1},{i + 1,j},{i + 1,j + 1} };
	for (int k = 0;k < 8;k++) 
	{
		int row = posArr[k][0];
		int col = posArr[k][1];

		//�Ѿ���������λ�ò���̽��
		if ((show[row][col] >= '1' && show[row][col] <= '8') || show[row][col] == ' ') {
			continue;
		}

		//1.����˷�����ΧһȦ�����ף�����ʾ�׵����������ٽ���̽��
		//2.����˷���һȦû���ף���ݹ�ļ����������ܱ߽���̽����ֱ����ΧһȦ������Ϊֹ
		int mineNum = 0;
		mineNum = GetMine(mine, row, col);
		if (mineNum > 0) {
			//+'0'�ǽ����Ϊ�ַ����͵�����
			show[row][col] = mineNum + '0';
		}
		else {
			SearchMine(mine, show, row, col);
		}
	}
}