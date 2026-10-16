#include <iostream>
#include <new>
#include <cstddef>

using namespace std;

int** concat_rows(
    const int* const* lhs, size_t n1, size_t m1,
    const int* const* rhs, size_t n2, size_t m2)
{
    size_t rows;

    if (n1 > n2)
        rows = n1;
    else
        rows = n2;

    int** result = new (nothrow) int*[rows]();

    if (result == nullptr)
        return nullptr;

    for (size_t i = 0; i < rows; i++)
    {
        size_t left_size = 0;
        size_t right_size = 0;

        if (i < n1)
            left_size = m1;

        if (i < n2)
            right_size = m2;

        result[i] = new (nothrow) int[left_size + right_size];

        if (result[i] == nullptr)
        {
            for (size_t j = 0; j < rows; j++)
                delete[] result[j];

            delete[] result;
            return nullptr;
        }

        for (size_t j = 0; j < left_size; j++)
            result[i][j] = lhs[i][j];

        for (size_t j = 0; j < right_size; j++)
            result[i][left_size + j] = rhs[i][j];
    }

    return result;
}

int** create_matrix(size_t rows, size_t cols)
{
    int** matrix = new (nothrow) int*[rows]();

    if (matrix == nullptr)
        return nullptr;

    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = new (nothrow) int[cols];

        if (matrix[i] == nullptr)
        {
            for (size_t j = 0; j < rows; j++)
                delete[] matrix[j];

            delete[] matrix;
            return nullptr;
        }
    }

    return matrix;
}

void delete_matrix(int** matrix, size_t rows)
{
    if (matrix == nullptr)
        return;

    for (size_t i = 0; i < rows; i++)
        delete[] matrix[i];

    delete[] matrix;
}

bool input_matrix(int** matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (!(cin >> matrix[i][j]))
                return false;
        }
    }

    return true;
}

void print_result(int** result,
                  size_t n1, size_t m1,
                  size_t n2, size_t m2)
{
    size_t rows;

    if (n1 > n2)
        rows = n1;
    else
        rows = n2;

    for (size_t i = 0; i < rows; i++)
    {
        size_t left_size = 0;
        size_t right_size = 0;

        if (i < n1)
            left_size = m1;

        if (i < n2)
            right_size = m2;

        size_t cols = left_size + right_size;

        for (size_t j = 0; j < cols; j++)
        {
            if (j > 0)
                cout << " ";

            cout << result[i][j];
        }

        cout << endl;
    }
}

int main()
{
    int n1, m1, n2, m2;

    cout << "Enter rows and columns of the first matrix:" << endl;

    if (!(cin >> n1 >> m1) || n1 <= 0 || m1 <= 0)
    {
        cerr << "Input error" << endl;
        return 1;
    }

    int** lhs = create_matrix(n1, m1);

    if (lhs == nullptr)
    {
        cerr << "Memory allocation error" << endl;
        return 2;
    }

    cout << "Enter elements of the first matrix:" << endl;

    if (!input_matrix(lhs, n1, m1))
    {
        cerr << "Input error" << endl;
        delete_matrix(lhs, n1);
        return 1;
    }

    cout << "Enter rows and columns of the second matrix:" << endl;

    if (!(cin >> n2 >> m2) || n2 <= 0 || m2 <= 0)
    {
        cerr << "Input error" << endl;
        delete_matrix(lhs, n1);
        return 1;
    }

    int** rhs = create_matrix(n2, m2);

    if (rhs == nullptr)
    {
        cerr << "Memory allocation error" << endl;
        delete_matrix(lhs, n1);
        return 2;
    }

    cout << "Enter elements of the second matrix:" << endl;

    if (!input_matrix(rhs, n2, m2))
    {
        cerr << "Input error" << endl;
        delete_matrix(lhs, n1);
        delete_matrix(rhs, n2);
        return 1;
    }

    int** result = concat_rows(lhs, n1, m1, rhs, n2, m2);

    if (result == nullptr)
    {
        cerr << "Memory allocation error" << endl;
        delete_matrix(lhs, n1);
        delete_matrix(rhs, n2);
        return 2;
    }

    cout << "Result matrix:" << endl;

    print_result(result, n1, m1,n2, m2);

    delete_matrix(lhs, n1);
    delete_matrix(rhs, n2);

    size_t result_rows;

    if (n1 > n2)
        result_rows = n1;
    else
        result_rows = n2;

    delete_matrix(result, result_rows);

    return 0;
}