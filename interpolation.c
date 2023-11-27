#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x) {
	return sin(x) / x;
}
double L(double *x, int n, double a) {
	double rez = 0, l;
	int i, j;
	for (i = 0; i < n; i++) {
		l = 1;
		for (j = 0; j < n; j++) {
			if (i != j) {
				l = l * (a - x[j]);
				l = l / (x[i] - x[j]);
			}
		}
		rez = rez + f(x[i]) * l;
	}
	return rez;
}

int main() {
	double *x, tochka;
	int n;
	printf("enter n (kolichestvo peremennih v kotorih izvestno znachenie): ");
	scanf("%d", &n);
	x = (double*)malloc(sizeof(double) * n);
	if (x == NULL) {
		printf("malloc x error\n");
		return -1;
	}
	for (int i = 0; i < n; i++) {
		printf("%d\nenter xi :", i);
		scanf("%lf", &x[i]);
	}
	printf("enter x v kotorom hotim y: ");
	scanf("%lf", &tochka);
	printf("lagranj: %lf\n", L(x, n, tochka));
	printf("the real value in tochka: %lf\n", f(tochka));
	free(x);
	return 0;
}