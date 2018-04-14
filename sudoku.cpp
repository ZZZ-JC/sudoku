#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include"random.h"
using namespace std;

int chess[9][9];
int temp[9];

RandomNumber R;
ofstream ocout;
FILE *fp1;
int flag;

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
	int temprow = row / 3 * 3;
	int tempcol = col / 3 * 3;
	for (int j = temprow; j< temprow + 3; ++j)
	{
		for (int k = tempcol; k < tempcol + 3; ++k) {
			if (chess[j][k] == chess[row][col] && j != row &&k != col) {
				return 0;
			}
		}
	}
	return 1;
}

void backtrace(int count)//深搜与回溯
{
	if (count == 81)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				ocout << chess[i][j] << " ";
			}
			ocout << "\n";
		}
		ocout << " \n";
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

void random()//随机选出一个1-9的随机数
{
	for (int i = 0; i < 9; i++)
		temp[i] = 0;
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

void xuehao()//将生成数独终局第一行第一列的数字改成与自己学号想关的数字
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
	for (int i = 0; i < 9; i++)
	{
		chess[0][i] = temp[i];
	}
}

int main(int argc, char *argv[])
{
	memset(chess, 0, sizeof(int)* 9 * 9);
	if (argc != 3)
		printf("error\n");
	if (strcmp(argv[1], "-s") == 0)//求解数独
	{
		flag = 0;
		ocout.open("sudoku.txt");
		fp1 = fopen(argv[2], "r");
		char str[100];
		if (NULL == fp1)
		{
			printf("error\n");
			return 0;
		}
		int i = 0;
		int k = 0;
		while (!feof(fp1))
		{
			memset(str, 0, sizeof(str));
			fgets(str, sizeof(str)-1, fp1); 
			if (str[0] == '\n' || str[0] == '\0')
				continue;
			else
			{
				for (int j = 0; j < 17; j = j + 2)
				{
					chess[i][k] = str[j] - '0';
					k++;
				}
				i++;
				k = 0;
			}
		}
		backtrace(0);
		ocout.close();
		system("pause");
		return 0;
	}
	else if (strcmp(argv[1], "-c") == 0 && atoi(argv[2]) > 0 && atoi(argv[2]) <= 1000000)//生成数独终盘
	{
		flag = 0;
		clock_t start, finish;
		ocout.open("sudoku.txt");
		start = clock();
		for (int i = 0; i < atoi(argv[2]); i++)
		{
			xuehao();
			backtrace(9);
		}
		finish = clock();
		ocout << "所需要的时间为" << (finish - start) << "ms" << endl;
		ocout.close();
		system("pause");
	}
	else
		printf("error\n");
	return 0;
}
