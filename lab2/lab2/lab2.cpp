#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для выделения памяти под матрицу
int** allocate_matrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Функция для освобождения памяти матрицы
void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для заполнения матрицы случайными числами
void fill_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

// Функция для перемножения матриц
void multiply_matrices(int** a, int** b, int** c, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            c[i][j] = 0;
            for (int k = 0; k < size; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {
    int sizes[] = { 100, 200, 400, 1000, 2000, 4000 }; // Размеры матриц
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    clock_t start, end;

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];

        // Динамическое выделение памяти для матриц
        int** a = allocate_matrix(size);
        int** b = allocate_matrix(size);
        int** c = allocate_matrix(size);

        srand(time(NULL));
        fill_matrix(a, size);
        fill_matrix(b, size);

        // Замер времени для перемножения матриц
        start = clock();
        multiply_matrices(a, b, c, size);
        end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Matrix size: %d x %d, Time taken: %.6f seconds\n", size, size, time_taken);

        // Освобождение памяти
        free_matrix(a, size);
        free_matrix(b, size);
        free_matrix(c, size);
    }

    return 0;
}