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
int flag;

int fc(int row, int col)
{
	for (int j = 0; j < 9; j++)//�ų����е��ظ���
	{
		if (chess[row][j] == chess[row][col] && j != col)
			return 0;
	}
	for (int i = 0; i < 9; i++)//�ų����е��ظ���
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

void backtrace(int count)//���������
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

void random()//���ѡ��һ��1-9�������
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

void xuehao()//�����������վֵ�һ�е�һ�е����ָĳ����Լ�ѧ����ص�����
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
		printf("wrong\n");
	if (strcmp(argv[1], "-s") == 0)//�������
	{
		flag = 0;
		ocout.open("sudoku.txt");
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
	else if (strcmp(argv[1], "-c") == 0 && atoi(argv[2]) > 0 && atoi(argv[2]) <= 1000000)//������������
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
		printf("%dms\n", (finish - start));
		ocout << "����Ҫ��ʱ��Ϊ" << (finish - start) << "ms" << endl;
		ocout.close();
		system("pause");
	}
	else
		printf("wrong\n");
	return 0;
}
