#include <stdio.h>
#include <math.h>

// ищем интеграл: dt / (t * sqrt(1 + t^4))
// делаем замену: t = tan(u), dt = du / cos^2 u
// заменяем интервалы: x-> arctan(x), inf -> pi/2
// du / (tan(u) * sqrt(1 + tan^4(u)) * cos^2 (u)) = du / sin(x) / cos(x) / sqrt(1 + tan(u)^4) 
double f1(double u) {
    return 1.0 / (sin(u) * cos(u) * sqrt(1 + pow(tan(u), 4)));
}

// вторая функция
double f2(double t) {
    return 1.0 / sqrt(1 + t*t*t*t);
}

// интегрирование с заданной точностью
double integrate(double (*f)(double), double a, double b, long n) {
    double h = (b - a) / n; // шаг интегрирования
    double sum = 0, sum1;
    
    // вычисляем значение интеграла для n = 2
    for (int i = 1; i <= n / 2; i++)
        sum += 4 * f(a + (2 * i - 1) * h);

    for (int i = 1; i < n / 2; i++)
        sum += 2 * f(a + 2 * i * h);

    return (f(a) + sum + f(b)) * h / 3;
}

double getIntegral(double (*f)(double), double a, double b, long n, double eps) {
   double x = integrate(f, a, b, n);
    double y = integrate(f, a, b, 2 * n);

    if (fabs(x - y) < eps)
        return y;

    return getIntegral(f, a, (a + b) / 2, n, eps) + getIntegral(f, (a + b) / 2, b, n, eps);
}

// функция для поиска корня
double f(double x, double alpha, double eps) {
    return alpha * getIntegral(f1, atan(x), M_PI / 2, 2, eps) - getIntegral(f2, 0, x, 2, eps);
}

// производная функции для поиска корня
double df(double x, double alpha) {
    return -(alpha / x + 1) / sqrt(1 + x*x*x*x) - 1;
}

// метод Ньютона
double newtone_method(double x0, double alpha, double eps) {
    double x;

    do {
        x = x0; // сохраняем предыдущую точку
        x0 -= f(x0, alpha, eps) / df(x0, alpha); // делаем шаг метода
    } while (fabs(x - x0) > eps); // повторяем, пока не достигнем нужной точности

    return x0; // возвращаем найденный корень
}

int main(void) {
    double alpha; // параметр уравнения
    double eps; // точность
    double x; // корень

    printf("Enter alpha: ");
    scanf("%lf", &alpha); // считываем параметр

    // проверяем параметр на корректность
    if (alpha <= 0) {
        printf("Invalid alpha value\n");
        return -1;
    }

    printf("Enter eps: ");
    scanf("%lf", &eps); // считываем точность

    // проверяем точность на корректность
    if (eps < 1e-13 || eps > 1) {
        printf("Invalid eps value\n");
        return -1;
    }

    x = newtone_method(1, alpha, eps); // ищем корень
    printf("x: %.15lf\nf(x): %lf", x, f(x, alpha, eps));
    return 0;
}