// Unit tests for the matrix library using GoogleTest.

#include <gtest/gtest.h>
#include <stdexcept>
#include "matrix.h"

// Тест: создание и освобождение матрицы
TEST(MatrixTest, CreateAndFree) {
    Matrix m = create_matrix(2, 2);
    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 2);
    EXPECT_NE(m.data, nullptr);
    free_matrix(m);
}

// Тест: создание матрицы с недопустимым размером должно выбросить исключение
TEST(MatrixTest, InvalidSize) {
    EXPECT_THROW(create_matrix(-1, 2), std::invalid_argument);
}

// Тест: сложение матриц
TEST(MatrixTest, MatrixAddition) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_add(A, B);
    EXPECT_EQ(C.data[0][0], 6);
    EXPECT_EQ(C.data[0][1], 8);
    EXPECT_EQ(C.data[1][0], 10);
    EXPECT_EQ(C.data[1][1], 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// Тест: умножение матриц
TEST(MatrixTest, MatrixMultiplication) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_multiply(A, B);
    EXPECT_EQ(C.data[0][0], 19);
    EXPECT_EQ(C.data[0][1], 22);
    EXPECT_EQ(C.data[1][0], 43);
    EXPECT_EQ(C.data[1][1], 50);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// Тест: сумма всех элементов в матрице
TEST(MatrixTest, MatrixSum) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    EXPECT_DOUBLE_EQ(matrix_sum(A), 10.0);
    free_matrix(A);
}
// --- HSTACK: базовый кейс
TEST(MatrixTest, HStackBasic) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 1);

    // A = [[1,2],[3,4]]
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    // B = [[5],[6]]
    B.data[0][0] = 5;
    B.data[1][0] = 6;

    Matrix C = matrix_hstack(A, B);
    ASSERT_NE(C.data, nullptr);
    EXPECT_EQ(C.rows, 2);
    EXPECT_EQ(C.cols, 3);

    // Ожидаем [[1,2,5],[3,4,6]]
    EXPECT_DOUBLE_EQ(C.data[0][0], 1);
    EXPECT_DOUBLE_EQ(C.data[0][1], 2);
    EXPECT_DOUBLE_EQ(C.data[0][2], 5);
    EXPECT_DOUBLE_EQ(C.data[1][0], 3);
    EXPECT_DOUBLE_EQ(C.data[1][1], 4);
    EXPECT_DOUBLE_EQ(C.data[1][2], 6);

    free_matrix(C);
    free_matrix(B);
    free_matrix(A);
}

// --- HSTACK: несовпадающее число строк -> пустая матрица
TEST(MatrixTest, HStackRowMismatch) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 1);

    Matrix C = matrix_hstack(A, B);
    EXPECT_EQ(C.data, nullptr);
    EXPECT_EQ(C.rows, 0);
    EXPECT_EQ(C.cols, 0);

    free_matrix(C);
    free_matrix(B);
    free_matrix(A);
}

// --- HSTACK: невалидный ввод (nullptr/нулевые размеры) -> пустая матрица
TEST(MatrixTest, HStackInvalidInput) {
    Matrix A{}; // data = nullptr, rows/cols = 0
    Matrix B = create_matrix(1, 1);
    B.data[0][0] = 42;

    Matrix C = matrix_hstack(A, B);
    EXPECT_EQ(C.data, nullptr);
    EXPECT_EQ(C.rows, 0);
    EXPECT_EQ(C.cols, 0);

    free_matrix(C);
    free_matrix(B);
}
