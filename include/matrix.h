// Public API for the matrix library.
//
// Defines a simple struct representing a matrix of doubles along with
// declarations for functions used to manipulate matrices. Users of this
// header must link against the corresponding implementation in matrix.cpp.

#pragma once

// C-структура для хранения данных матрицы
typedef struct {
    double** data;
    int rows;
    int cols;
} Matrix;

// Базовые функции
Matrix create_matrix(int rows, int cols);
void   free_matrix(Matrix m);
Matrix matrix_add(Matrix a, Matrix b);
Matrix matrix_multiply(Matrix a, Matrix b);
Matrix matrix_transpose(Matrix m);
double matrix_sum(Matrix m);

// Вспомогательные функции
void   print_matrix(Matrix m);
Matrix matrix_from_array(double* data, int rows, int cols);

// Сохранение/загрузка
void   matrix_to_file(Matrix m, const char* filename);
// Объединение матриц по горизонтали: [A | B]
// Требования: A.rows == B.rows, обе матрицы валидны (data != nullptr, rows>0, cols>0).
// При нарушении условий возвращает пустую матрицу 0x0 (data == nullptr).
Matrix matrix_hstack(Matrix a, Matrix b);
