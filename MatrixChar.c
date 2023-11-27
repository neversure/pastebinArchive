//Необходимо написать программу, которая будет спрашивать у пользователя размер квадратной матрицы, выделять под неё память, //заполнять данными по формуле, считать некоторую характеристику, и удалять матрицу.
//Матрица хранится в виде одномерного массива
//Заполнение по формуле a(i,j) = max(i,j)
//Характеристика: посчитать максимальную сумму модулей элементов по столбцам матрицы
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

void feel(int *matrix, int n, int m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for(j = 0; j < m; j++)
			matrix[i*m + j] = max(i, j);
	}
}

//если правильно понял третий пункт, то посчитать максимальную
//сумму модулей элементов по столбцам матрицы
//значит найти столбец с максимальной суммой модулей его элементов 


//так же в моем случае все элементы матрицы не отрицательны и целы (по условию)
//и я не буду использовать модуль

int max_abs(int * matrix, int n, int m) {
	int i, j, stolbec = 0, max = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			stolbec += matrix[i*m + j];
		}
		if (stolbec > max) max = stolbec;
		stolbec = 0;
	}
	return max;
}
int main() {
	int n, m, *matrix;
	printf("enter n and m: ");
	if (scanf("%d %d", &n, &m) != 2) {
		printf("wrong data\n");
		return -1;
	}
	matrix = (int*)malloc(sizeof(int)*(m*n));
	if (!matrix) {
		printf("malloc error\n");
		return -1;
	}
	feel(matrix, n, m);
	printf("max sum of abss: %d", max_abs(matrix, n, m));
	free(matrix);
	return 0;
}