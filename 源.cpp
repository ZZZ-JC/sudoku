#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include"random.h"
using namespace std;

int chess[9][9];
int suiji[9];
int temp[9];
int chessboard[9][9];

RandomNumber R;
ofstream ocout;
int flag;
int model[9][9] = {
	{ '2', '6', '7', '8', '5', '9', '4', '3', '1' },
	{ '4', '1', '3', '6', '7', '2', '9', '5', '8' },
	{ '8', '9', '5', '1', '4', '3', '2', '7', '6' },
	{ '5', '3', '6', '4', '9', '1', '8', '2', '7' },
	{ '7', '4', '1', '2', '8', '5', '3', '6', '9' },
	{ '9', '2', '8', '3', '6', '7', '5', '1', '4' },
	{ '3', '8', '2', '9', '1', '6', '7', '4', '5' },
	{ '1', '5', '4', '7', '3', '8', '6', '9', '2' },
	{ '6', '7', '9', '5', '2', '4', '1', '8', '3' }
};

int fc(int row, int col)
{
	for (int j = 0; j < 9; j++)//排除行中的重复数
	{
		if (chess[row][j] == chess[row][col] && j != col)
			return 0;
	}
	for (int i = 0; i < 9; i++)//排除列中的重复数
	{
		if (chess[i][col] == chess[row][col] && i != row)
			return 0;
	}
	int tempRow = row / 3 * 3;
	int tempCol = col / 3 * 3;
	for (int j = tempRow; j< tempRow + 3; ++j)
	{
		for (int k = tempCol; k < tempCol + 3; ++k) {
			if (chess[j][k] == chess[row][col] && j != row &&k != col) {
				return 0;
			}
		}
	}
	return 1;
}

void backtrace(int count)
{
	if (count == 81)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				ocout << chess[i][j] << " ";
			}
			ocout << " \n";
		}
		flag = 1;
		return;
	}
	int row = count / 9;
	int col = count % 9;
	if (chess[row][col] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{

			chess[row][col] = i;
			if (fc(row, col) == 1)
				backtrace(count + 1);
			if (flag == 1)
				return;
		}
		chess[row][col] = 0;
	}
	else
	{
		backtrace(count + 1);
		if (flag == 1)
			return;
	}
}

void replace();
void print();
void random();
void xuehao();

int main(int argc, char *argv[])
{
	if (strcmp(argv[1], "-s") == 0)
	{
		flag = 0;
		ocout.open("E:\\项目\\数独\\Debug\\sudoku.txt");
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				scanf("%d", &chess[i][j]);
			}
		}
		backtrace(0);
		ocout.close();
		system("pause");
		return 0;
	}
	else if (strcmp(argv[1], "-c") == 0 && atoi(argv[2]) > 0 && atoi(argv[2]) <= 1000000)
	{
		clock_t start, finish;
		double totaltime;
		ocout.open("E:\\项目\\数独\\Debug\\sudoku.txt");
		start = clock();
		for (int i = 0; i < atoi(argv[2]); i++)
		{
			xuehao();
			replace();
			print();
		}
		finish = clock();
		totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		ocout << "\n所需的时间是" << totaltime << "s" << endl;
		ocout.close();
		system("pause");
	}
	else
	{
		printf("wrong\n");
	}
	return 0;
}

void random()
{
	for (int i = 0; i < 9; i++)
	{
		temp[i] = 0;
	}
	for (int i = 0; i < 9; i++)
	{
		temp[i] = R.Rondom(10) % 9 + 1;
		for (int j = 0; j < i; j++)
		{
			if (temp[i] == temp[j])
			{
				i--;
				break;
			}
		}
	}
}

void xuehao()
{
	random();
	for (int i = 0; i < 9; i++)
	{
		if (temp[i] == 3)
		{
			temp[i] = temp[0];
			temp[0] = 3;
		}
	}
}

void replace()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (model[i][j] == '1'){ chessboard[i][j] = temp[1]; }
			else if (model[i][j] == '2'){ chessboard[i][j] = temp[0]; }
			else if (model[i][j] == '3'){ chessboard[i][j] = temp[2]; }
			else if (model[i][j] == '4'){ chessboard[i][j] = temp[3]; }
			else if (model[i][j] == '5'){ chessboard[i][j] = temp[4]; }
			else if (model[i][j] == '6'){ chessboard[i][j] = temp[5]; }
			else if (model[i][j] == '7'){ chessboard[i][j] = temp[6]; }
			else if (model[i][j] == '8'){ chessboard[i][j] = temp[7]; }
			else if (model[i][j] == '9'){ chessboard[i][j] = temp[8]; }
		}
	}
}

void print()
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			ocout << chessboard[i][j] << " ";
		}
		ocout << "\n";
	}
	ocout << "\n";
}