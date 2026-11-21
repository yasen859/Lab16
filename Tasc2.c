#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

double* insert(double* ptr_arr, int* size, int index, double num) {
    int size_n = (*size) + 1;
    if (ptr_arr == NULL) return NULL;
    double* ptr_arr_n = (double*)realloc(ptr_arr, size_n * sizeof(double));
    if (ptr_arr_n == NULL) return ptr_arr;
    ptr_arr = ptr_arr_n;
    for (int i = size_n - 1; i > index; i--)
        ptr_arr[i] = ptr_arr[i - 1];
    ptr_arr[index] = num;
    *size = size_n;
    return ptr_arr;
}

// Заполнение массива случайными числами от -1 до 1
double* full_elements(double* ptr_array, int size)
{
    for (int i = 0; i < size; i++)
        ptr_array[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    return ptr_array;
}

// Печать элементов массива
int put_elements(double* ptr_array, int size)
{
    for (int i = 0; i < size; i++)
        printf("a[%d] = %.4f\n", i, ptr_array[i]);
    return size;
}

// Удаление элемента с заданным номером k
int delete_k(double* ptr_arr, int size, int k)
{

    int n = size - 1;
    for (int i = k; i < (size - 1); i++)
        ptr_arr[i] = ptr_arr[i + 1];
    return n;                        // новое число элементов массива
}

int main(void)
{
    setlocale(LC_ALL, ".UTF8");

    int size, k;
    double num = -999.0;

    srand((unsigned)time(NULL));     // инициализация генератора случайных чисел

    printf("Введите размер массива: ");
    scanf_s("%d", &size);

    double* ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        puts("error");
        return -1;
    }

    // Заполнение массива случайными числами от -1 до 1
    full_elements(ptr_array, size);
    printf("\nИсходный массив (случайные числа от -1 до 1):\n");
    put_elements(ptr_array, size);

    printf("\nВведите индекс удаляемого элемента k = ");
    scanf_s("%d", &k);

    // Удаление элемента с заданным номером
    int new_size = delete_k(ptr_array, size, k);

    printf("\nМассив после удаления элемента с индексом %d:\n", k);
    put_elements(ptr_array, new_size);

    printf("\nВведите индекс k элемента, ПОСЛЕ которого вставить %d = ", (int)num);
    scanf_s("%d", &k);

    // Вставка -999 после элемента с индексом k
    ptr_array = insert(ptr_array, &size, k + 1, num);

    printf("\nМассив после вставки %d после элемента с индексом %d:\n",
        (int)num, k);
    put_elements(ptr_array, size);

    free(ptr_array);

    return 0;
}