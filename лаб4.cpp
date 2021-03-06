
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <clocale>
#include <time.h>
#include <math.h>
#include <memory.h>
#include <limits.h>

#ifdef _DEBUG //утечка памяти
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

/**
*\file
*\brief  Замена строки с наименьшей суммой элементов на главную диагональ
*\author Елисеенко М.А.
*\date 19.11.2018
*\version 1.0
*/
///Функция выделяющая пямять для матрицы
void entermatrix(int **&a, int &heig, int &wid);
///Функция для заполнения матрицы с клавиатуры
void input(int**a, int heig, int wid);
///Функция для заполнения матрицы случайными числами
void random(int**a, int heig, int wid);
///Функция обрабатывающая матрицу
void processing(int &strmin, int &stop, int **a, int heig, int wid, int &wasent, int &wascalc);
///Функция выводящая на экран поученную матрицу
void output(int**a, int heig, int wid, int &stop, int &wascalc, int strmin);
///Функция проверяющая корректность введенных данных
int correctVallue(int min, int max);

int menu()
///Функция выводит меню
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int c = 1;
	while (c == 1)
	{
		printf("Выберете пункт меню:\n");
		printf("1.Информация о программе\n");
		printf("2.Ввод элементов матрицы\n");
		printf("3.Обработка элементов матрицы\n");
		printf("4.Вывод значения на экран\n");
		printf("5.Выход\n");

		int vid = _getch();
		switch (vid - 48)
		{
		case 1:
			while (true)
			{
				system("cls");
				printf("1)Найти минимальную сумму строки\n2)Заменить её элементы на элементы главной диагонали\n");
				printf("\n1. Назад\n");

				int vid2 = _getch();
				switch (vid2 - 48)
				{
				case 1:
					system("cls");
					break;
				default:;
				}
				if (vid2 - 48 == 1) break;
			}
			break;
		case 2:
			while (true)
			{
				system("cls");
				printf("1.Заполнить матрицу случайными числами\n");
				printf("2.Заполнить матрицу самостоятельно\n");
				printf("3.Назад\n");

				int vid2 = _getwch();
				switch (vid2 - 48)
				{
				case 1:
					return 8;
				case 2:
					return 7;
				case 3:
					system("cls");
					break;
				default:;
				}
				if (vid2 - 48 == 3)
					break;

			}

			break;
		case 3:
			return 3;
			break;

		case 4:
			return 4;
		case 5:
			return 5;
			break;
		default:
			system("cls");
			break;
		}

	}
}

int main()
///Основная функция main, точка входа в программу
{
	

	int wascalc = 0;
	int wasent = 0;
	int stop = -1;
	int heig = 0;
	int wid = 0;
	int strmin = 0;
	int **a = NULL;
	srand(time(NULL));
	while (true)
	{
		system("cls");
		int choice = 0;
		choice = menu();
		if ((choice == 7) || (choice == 8))
		{
			entermatrix(a, heig, wid);

			if (choice == 7)
			{
				input(a, heig, wid);
			}
			else
			{
				random(a, heig, wid);
			}
			printf("\nНажмите любую клавишу");
			wasent = 1;
			wascalc = 0;
			_getch();
			_getch();
			system("cls");
		}
		//обработка
		if (choice == 3)
		{
			processing(strmin, stop, a, heig, wid, wasent, wascalc);
		}
		//вывод
		if (choice == 4)
		{
		output(a, heig, wid, stop, wascalc, strmin);	
		}
		if (choice == 5)
		{
			return 0;
		}
	}
	for (int i = 0; i < heig; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	_CrtDumpMemoryLeaks();
	return 0;
}
int correctVallue(int min, int max)
{
	

	int value = 0;
	char c = '\0';

	do
	{
		while (scanf_s("%d%c", &value, &c, 1) != 2 || c != '\n')
		{
			printf("Неверное значение\n");
			printf("Введите значение заново: ");
			while (getchar() != '\n');
		} 
		 
		if (value<min || value>max)
		{
			printf("Неверное значение\n");
			printf("Введите значение между %d и %d: \n", min, max);
		}
	} while (value<min || value>max);
	return value;
}
void entermatrix(int **&a, int &heig, int &wid)
{
	
	char check[256];

	if (a != NULL)
	{
		for (int i = 0; i < heig; i++)
		{
			delete[] a[i];
		}
		delete[] a;
	}
	system("cls");
	printf("Введите размерность матрицы");

	printf("\nКоличество строк: ");
	heig = correctVallue(0, 256); 

	printf("\nКоличество столбцов: ");
	wid = correctVallue(0, 256);

	system("cls");


	a = new int*[heig];
	for (int i = 0; i < heig; i++)
	{
		a[i] = new int[wid];
	}

	
}
void input(int**a, int heig, int wid)
{
	/**
	*\brief 
		*Используется в Menu().
		*\param[in] a Двумерный массив для матрицы.
		*\param[in] heig Высота матрицы.
		*\param[in] wid Длинна матрицы.
	*\code
		char c = '\0';
		for (int i = 0; i < heig; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				printf("%d %d элемент: ", i + 1, j + 1);
				printf("\n\nВведите %d %d элемент: ", i + 1, j + 1);
				int input = 0;
				while (scanf_s("%d%c", &input, &c, 1) != 2 || c != '\n')
				{
					system("cls");
					printf("\tВводите элементы по одному \n");
					printf("\n\nИзвините, вы ввели некорректные значения.");
					printf("\nПопробуйте ввести %d %d элемент снова: ", i + 1, j + 1);
					while (getchar() != '\n');
				}
				a[i][j] = input;
			}

		}
		system("cls");
		printf("\nВаша матрица: \n");
		for (int i = 0; i < heig; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}
		*\endcode
		*/
		
}
void random(int**a, int heig, int wid)
{
	for (int i = 0; i < heig; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			a[i][j] = rand() % 10;
		}

	}
	printf("Ваша матрица: \n");
	for (int i = 0; i < heig; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
void processing(int &strmin, int &stop, int **a, int heig, int wid, int &wasent, int &wascalc)
{
	if (wasent == 1)
	{
		system("cls");
		int min = 10000000;
		for (int i = 0; i < heig; i++)
		{
			int sum = 0;
			for (int j = 0; j < wid; j++)
			{
				sum += a[i][j];
			}
			if (min > sum)
			{
				strmin = i;
				min = sum;
			}
		}
		if (stop != strmin)
		{
			printf("\nВаша матрица: \n");
			for (int i = 0; i < heig; i++)
			{
				for (int j = 0; j < wid; j++)
				{
					printf("%d ", a[i][j]);
				}
				printf("\n");
			}
			printf("Сумма построчно\n");
			min = 10000000;
			for (int i = 0; i < heig; i++)
			{
				int sum = 0;
				for (int j = 0; j < wid; j++)
				{
					sum += a[i][j];
				}
				if (min > sum)
				{
					strmin = i;
					min = sum;
				}
				printf("%d) %d\n", i + 1, sum);
			}
			printf("Минимальная сумма строки %d", min);
			printf("\nНомер строки %d\n", strmin + 1);
			printf("\nВаша матрица обработана \n");
		}
		else
		{
			printf("\n\nВ последующих обработках нет смысла, т.к. матрица изменяться не будет\n");
			printf("Создайте новую матрицу\n");
		}

		wascalc = 1;
		_getch();
		_getch();
		system("cls");
	}
	else
	{
		printf("Сначала введите матрицу");
		_getch();
		_getch();
	}
}
void output(int**a, int heig, int wid, int &stop, int &wascalc, int strmin)
{
	if (wascalc == 1)
	{
		system("cls");
		printf("\nВаша матрица: \n");
		for (int i = 0; i < heig; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}

		if (wid < heig)
		{
			for (int i = 0; i < wid; i++)
			{
				a[strmin][i] = a[i][i];
			}
		}
		else
		{
			for (int i = 0; i < heig; i++)
			{
				a[strmin][i] = a[i][i];
			}
		}

		printf("\nИзмененная матрица:\n");
		for (int i = 0; i < heig; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}
		printf("\nИзменeна строка №%d\n", strmin + 1);
		printf("\nНажмите любую клавишу");
		stop = strmin;
		wascalc = 0;
		_getch();
		_getch();
	}
	else
	{
		printf("Сначала обработайте матрицу");
		_getch();
		_getch();
	}
}