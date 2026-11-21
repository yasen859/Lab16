#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

double* full_elements(double* ptr_array, int size)
{
    for (int i = 0; i < size; i++)
        ptr_array[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    return ptr_array;
}

int put_elements(double* ptr_array, int size)
{
    for (int i = 0; i < size; i++)
        printf("a[%d] = %.4f\n", i, ptr_array[i]);
    return size;
}

// Новый массив d: чередование положительных элементов a и отрицательных элементов c
double* d_array(double* a, int n, double* c, int l, int* size_d)
{
    // Подсчёт количества положительных элементов a
    int pos_count = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > 0.0) pos_count++;

    // Подсчёт количества отрицательных элементов c
    int neg_count = 0;
    for (int i = 0; i < l; i++)
        if (c[i] < 0.0) neg_count++;

    *size_d = pos_count + neg_count;

    double* d = (double*)calloc(*size_d, sizeof(double));
    if (d == NULL) {
        puts("error");
        return NULL;
    }

    int ia = 0, ic = 0, pos = 0;
    while (ia < n && ic < l) {
        // Пропуск неподходящих элементов
        while (ia < n && a[ia] <= 0.0) ia++;
        while (ic < l && c[ic] >= 0.0) ic++;

        if (ia < n) d[pos++] = a[ia++];
        if (ic < l) d[pos++] = c[ic++];
    }

    return d;
}

int main(void)
{
    setlocale(LC_ALL, ".UTF8");

    int n, m, l, size_d;
    srand((unsigned)time(NULL));

    
    n = 10 + rand() % 41;
    m = 10 + rand() % 41;
    l = 10 + rand() % 41;

   
    double* a = (double*)malloc(n * sizeof(double));
    double* b = (double*)malloc(m * sizeof(double));
    double* c = (double*)malloc(l * sizeof(double));
    if (a == NULL || b == NULL || c == NULL) {
        puts("error");
        return -1;
    }

    full_elements(a, n);
    full_elements(b, m);
    full_elements(c, l);

    printf("Размеры: n = %d, m = %d, l = %d\n", n, m, l);
    printf("\nМассив a (n = %d):\n", n);
    put_elements(a, n);
    printf("\nМассив b (m = %d):\n", m);
    put_elements(b, m);
    printf("\nМассив c (l = %d):\n", l);
    put_elements(c, l);

    // Новый массив d с чередованием положительных a и отрицательных c
    double* d = d_array(a, n, c, l, &size_d);
    
    printf("\nМассив d (чередование положительных a и отрицательных c, size = %d):\n",
        size_d);
    put_elements(d, size_d);

    
    free(a);
    free(b);
    free(c);
    free(d);

    return 0;
}