#include <iostream>
#include <cstdlib>

using namespace std;

class Matrix {
private:
    int** data; // Указатель на указатель типа int, который используется для динамического выделения двумерного массива, хранящего элементы матрицы.
    unsigned int m; //Количество строк матрицы
    unsigned int n; //Количество столбцов матрицы

public:
    Matrix(unsigned int rows, unsigned int columns) { //Конструктор, принимабющий кол-во строк и столбцов для матрицы,  выделяет память для хранения элементов матрицы и инициализирует их нулями
        m = rows;
        n = columns;

        data = new int* [m];
        for (unsigned int i = 0; i < m; i++) {
            data[i] = new int[n];
        }
    }

    ~Matrix() {
        for (unsigned int i = 0; i < m; i++) { // Деструктор
            delete[] data[i];
        }
        delete[] data;
    }

    void fillRandomValues() { // Заполняет матрицу случайными значениями от 0 до 9
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                data[i][j] = rand() % 10;
            }
        }
    }

    int* operator[](unsigned int index) const { //Позволяет обращаться к строкам матрицы как к массивам
        return data[index];
    }

    friend ostream& operator<<(ostream& os, const Matrix& matrix) { //Позволяет красиво печатать матрицу в стандартный вывод или в файл.
        for (unsigned int i = 0; i < matrix.m; i++) {
            for (unsigned int j = 0; j < matrix.n; j++) {
                os << matrix.data[i][j] << ' ';
            }
            os << endl;
        }
        return os;
    }

    Matrix& operator+=(const Matrix& other) {
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2) {
        Matrix result(matrix1.m, matrix1.n);
        for (unsigned int i = 0; i < matrix1.m; i++) {
            for (unsigned int j = 0; j < matrix1.n; j++) {
                result.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator-=(const Matrix& other) {
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2) {
        Matrix result(matrix1.m, matrix1.n);
        for (unsigned int i = 0; i < matrix1.m; i++) {
            for (unsigned int j = 0; j < matrix1.n; j++) {
                result.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
            }
        }
        return result;
    }

    friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2) {
        Matrix result(matrix1.m, matrix2.n);
        for (unsigned int i = 0; i < result.m; i++) {
            for (unsigned int j = 0; j < result.n; j++) {
                result.data[i][j] = 0;
                for (unsigned int k = 0; k < matrix1.n; k++) { // Перебираем элементы строки первой матрицы и столбца второй
                    result.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
                }
            }
        }
        return result;
    }

    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.m != matrix2.m || matrix1.n != matrix2.n) {
            return false;
        }
        for (unsigned int i = 0; i < matrix1.m; i++) {
            for (unsigned int j = 0; j < matrix1.n; j++) {
                if (matrix1.data[i][j] != matrix2.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2) {
        return !(matrix1 == matrix2);
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Для генерации разных случайных чисел при каждом запуске

    Matrix matrix1(3, 3);
    matrix1.fillRandomValues();
    cout << "Matrix 1:" << endl << matrix1;

    Matrix matrix2(3, 3);
    matrix2.fillRandomValues();
    cout << "Matrix 2:" << endl << matrix2;

    Matrix matrix3 = matrix1 + matrix2;
    cout << "Matrix 1 + Matrix 2:" << endl << matrix3;

    Matrix difference = matrix1 - matrix2;
    cout << "Difference of Matrix 1 and Matrix 2:" << endl << difference;

    Matrix product = matrix1 * matrix2;
    cout << "Product of Matrix 1 and Matrix 2:" << endl << product;

    return 0;
}