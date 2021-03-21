#pragma once
#include<stdio.h>
#include<stdlib.h>

//定义应显示棋盘的大小
#define ROW 9
#define COL 9

//防止查雷时越界，多开两行两列
#define ROWS ROW+2
#define COLS COL+2

//设置游戏难度
enum Difficulty
{
	EASY = 10,
	MEDIUM = 20,
	HARD = 30
};

//初始化棋盘
void InitBoard(char arr[ROWS][COLS], int row, int col, char val);

//展示棋盘
void ShowBoard(char arr[ROWS][COLS], int row, int col);

//生成雷
void GenerateMine(char arr[ROWS][COLS], int row, int col, int difficulty);

//获取(x,y)处周围雷的数量 
int GetMine(char mine[ROWS][COLS], int i,int j);

//遇到周围没有雷时，对周围进行展开搜索雷的数目
void SearchMine(char mine[ROWS][COLS], char show[ROWS][COLS], int i, int j);