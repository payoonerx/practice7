#include <iostream>
#include <cstddef>
#include <new>

void freeMatrix(int** matrix, size_t rows)
{
    if (matrix == nullptr)
    {
        return;
    }

    for (size_t i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int** createMatrix(size_t rows, size_t cols)
{
    int** matrix = new int*[rows];

    size_t i = 0;

    try
    {
        for (; i < rows; ++i)
        {
            matrix[i] = new int[cols];
        }
    }
    catch (const std::bad_alloc&)
    {
        freeMatrix(matrix, i);
        throw;
    }

    return matrix;
}

int main()
{
    size_t rows;
    size_t cols;

    if (!(std::cin >> rows >> cols))
    {
        return 1;
    }

    int** matrix = nullptr;

    try
    {
        matrix = createMatrix(rows, cols);
    }
    catch (const std::bad_alloc&)
    {
        return 2;
    }

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            if (!(std::cin >> matrix[i][j]))
            {
                freeMatrix(matrix, rows);
                return 1;
            }
        }
    }

    int** transposed = nullptr;

    try
    {
        transposed = createMatrix(cols, rows);
    }
    catch (const std::bad_alloc&)
    {
        freeMatrix(matrix, rows);
        return 2;
    }

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            transposed[j][i] = matrix[i][j];
        }
    }

    for (size_t i = 0; i < cols; ++i)
    {
        for (size_t j = 0; j < rows; ++j)
        {
            std::cout << transposed[i][j];

            if (j + 1 < rows)
            {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }

    freeMatrix(matrix, rows);
    freeMatrix(transposed, cols);

    return 0;
}