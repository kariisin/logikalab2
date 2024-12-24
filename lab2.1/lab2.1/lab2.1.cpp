
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* a, const void* b) //сравнение двух элементов для qsort
{
    return (*(int*)a - *(int*)b);
}

int main(void)
{
    setlocale(LC_ALL, "");
    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    clock_t start, end; // объявляем переменные для определения времени выполнения

    const int size = 3000;
    int m[size], i = 0;

    for (int i = 0; i < size; i++)
    {
        m[i] = rand() % 100 + 1; // заполняем массив случайными числами
    }

    start = clock();

    shell(m, size);

    end = clock();
    printf("\nВремя(сорт. Шелла):%f", float(end - start) / float(CLOCKS_PER_SEC));

    for (int i = 0; i < size; i++)
    {
        m[i] = rand() % 100 + 1; // заполняем массив случайными числами
    }

    start = clock_t();

    qs(m, 0, size - 1);

    end = clock();
    printf("\nВремя(быстрая сорт.):%f", float(end - start) / float(CLOCKS_PER_SEC));

    for (int i = 0; i < size; i++)
    {
        m[i] = rand() % 100 + 1; // заполняем массив случайными числами
    }

    start = clock();

    qsort(m, size, 4, compare);

    end = clock();
    printf("\nВремя(qsort):%f", float(end - start) / float(CLOCKS_PER_SEC));

    return(0);
}