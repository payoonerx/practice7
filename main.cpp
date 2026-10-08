#include <iostream>
#include <new>

void deleteMatrix(int **matrix, size_t rows)
{
    if (matrix == nullptr) {
        return;
    }

    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int **createMatrix(size_t rows, size_t cols)
{
    int **matrix = new int *[rows]();

    try {
        for (size_t i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }
    } catch (...) {
        deleteMatrix(matrix, rows);
        throw;
    }

    return matrix;
}

bool readMatrix(int **matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                return false;
            }
        }
    }

    return true;
}

int **transposeMatrix(const int * const *matrix, size_t rows, size_t cols)
{
    int **transposed = createMatrix(cols, rows);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

void printMatrix(const int * const *matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i][j];

            if (j + 1 != cols) {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }
}

int main()
{
    size_t rows = 0;
    size_t cols = 0;

    if (!(std::cin >> rows >> cols)) {
        return 1;
    }

    int **matrix = nullptr;
    int **transposed = nullptr;

    try {
        matrix = createMatrix(rows, cols);

        if (!readMatrix(matrix, rows, cols)) {
            deleteMatrix(matrix, rows);
            return 1;
        }

        transposed = transposeMatrix(matrix, rows, cols);
        printMatrix(transposed, cols, rows);
    } catch (const std::bad_alloc &) {
        deleteMatrix(transposed, cols);
        deleteMatrix(matrix, rows);
        return 2;
    }

    deleteMatrix(transposed, cols);
    deleteMatrix(matrix, rows);

    return 0;
}