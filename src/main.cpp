#include <iostream>
#include "matrix.h"

// print helper
static void print_with_title(const char* title, const Matrix& m) {
    std::cout << title << "\n";
    print_matrix(m);
    std::cout << "\n";
}

int main() {
    // Matrices A and B (2x2)
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    // A = [[1,2],[3,4]]
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    // B = [[5,6],[7,8]]
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    print_with_title("Matrix A:", A);
    print_with_title("Matrix B:", B);

    // C = A + B
    Matrix C = matrix_add(A, B);
    print_with_title("A + B:", C);

    // D = A * B
    Matrix D = matrix_multiply(A, B);
    print_with_title("A * B:", D);

    // AT = A^T
    Matrix AT = matrix_transpose(A);
    print_with_title("Transpose of A:", AT);

    // Horizontal stack [A | B]
    Matrix H = matrix_hstack(A, B);
    print_with_title("HSTACK [A | B]:", H);

    // Sum elements in A
    double s = matrix_sum(A);
    std::cout << "Sum of all elements in matrix A: " << s << "\n\n";

    std::cout << "All operations completed successfully!\n";

    // Free all matrices
    free_matrix(H);
    free_matrix(AT);
    free_matrix(D);
    free_matrix(C);
    free_matrix(B);
    free_matrix(A);
    return 0;
}
