#include <iostream>
#include <cstdlib>

class Matrix 
{
private:
    int** data; 
    unsigned int m; 
    unsigned int n; 

public:
    Matrix(unsigned int rows, unsigned int columns) 
    {
        m = rows;
        n = columns;

       
        data = new int* [m];
        for (unsigned int i = 0; i < m; i++) {
            data[i] = new int[n];
        }
    }

    ~Matrix() 
    {
        
        for (unsigned int i = 0; i < m; i++) 
        {
            delete[] data[i];
        }
        delete[] data;
    }

    
    void fillRandomValues() 
    {
        for (unsigned int i = 0; i < m; i++) 
        {
            for (unsigned int j = 0; j < n; j++) 
            {
                data[i][j] = rand() % 10;
            }
        }
    }

    
    int* operator[](unsigned int index) 
    {
        return data[index];
    }


    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) 

        for (unsigned int i = 0; i < matrix.m; i++) 
        {
            for (unsigned int j = 0; j < matrix.n; j++) 
            {
                os << matrix.data[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    
    Matrix& operator+=(const Matrix& other) 
    {
        for (unsigned int i = 0; i < m; i++) 
        {
            for (unsigned int j = 0; j < n; j++) 
            {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    
    friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2) 
    {
        Matrix result(matrix1.m, matrix1.n);
        for (unsigned int i = 0; i < matrix1.m; i++) 
        {
            for (unsigned int j = 0; j < matrix1.n; j++) 
            {
                result.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
            }
        }
        return result;
    }

    
    Matrix& operator-=(const Matrix& other) 
    {
        for (unsigned int i = 0; i < m; i++) 
        {
            for (unsigned int j = 0; j < n; j++) 
            {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    
    friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2) 
    {
        Matrix result(matrix1.m, matrix1.n);
        for (unsigned int i = 0; i < matrix1.m; i++) 
        {
            for (unsigned int j = 0; j < matrix1.n; j++) 
            {
                result.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
            }
        }
        return result;
    }

    
    friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2) 
    {
        Matrix result(matrix1.m, matrix2.n);
        for (unsigned int i = 0; i < matrix1.m; i++) 
        {
            for (unsigned int j = 0; j < matrix2.n; j++) 
            {
                result.data[i][j] = 0;
                for (unsigned int k = 0; k < matrix1.n; k++) 
                {
                    result.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
                }
            }
        }
        return result;
    }

   
    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2) 
    {
        if (matrix1.m != matrix2.m || matrix1.n != matrix2.n) 
        {
            return false;
        }
        for (unsigned int i = 0; i < matrix1.m; i++) 
        {
            for (unsigned int j = 0; j < matrix1.n; j++) 
            {
                if (matrix1.data[i][j] != matrix2.data[i][j]) 
                {
                    return false;
                }
            }
        }
        return true;
    }

    
    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2) 
    {
        return !(matrix1 == matrix2);
    }
};

int main() 
{
    Matrix matrix1(3, 3);
    matrix1.fillRandomValues();
    std::cout << "Matrix 1:" << std::endl << matrix1;

    Matrix matrix2(3, 3);
    matrix2.fillRandomValues();
    std::cout << "Matrix 2:" << std::endl << matrix2;

    Matrix matrix3 = matrix1 + matrix2;
    std::cout << "Matrix 1 + Matrix 2:" << std::endl << matrix3;

    Matrix matrix4 = matrix1 - matrix2;
    std::cout << "Matrix 1 - Matrix 2:" << std::endl << matrix4;

    Matrix matrix5 = matrix1 * matrix2;
    std::cout << "Matrix 1 * Matrix 2:" << std::endl << matrix5;

    return 0;
}