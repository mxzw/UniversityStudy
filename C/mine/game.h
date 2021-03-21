#pragma once
#include<stdio.h>
#include<stdlib.h>

//����Ӧ��ʾ���̵Ĵ�С
#define ROW 9
#define COL 9

//��ֹ����ʱԽ�磬�࿪��������
#define ROWS ROW+2
#define COLS COL+2

//������Ϸ�Ѷ�
enum Difficulty
{
	EASY = 10,
	MEDIUM = 20,
	HARD = 30
};

//��ʼ������
void InitBoard(char arr[ROWS][COLS], int row, int col, char val);

//չʾ����
void ShowBoard(char arr[ROWS][COLS], int row, int col);

//������
void GenerateMine(char arr[ROWS][COLS], int row, int col, int difficulty);

//��ȡ(x,y)����Χ�׵����� 
int GetMine(char mine[ROWS][COLS], int i,int j);

//������Χû����ʱ������Χ����չ�������׵���Ŀ
void SearchMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j);