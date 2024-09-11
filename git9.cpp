#include <iostream>
#include <iomanip>
#include <cstdlib>  // Для rand() та srand()
#include <ctime>    // Для time()

template <typename T>
class Matrix {
private:
    T** data;
    int rows, cols;

public:
    // Конструктор
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Заповнення матриці з клавіатури
    void fillFromInput() {
        std::cout << "Enter elements for a " << rows << "x" << cols << " matrix:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    // Заповнення матриці випадковими значеннями
    void fillRandom(T minVal, T maxVal) {
        srand(static_cast<unsigned int>(time(0)));  // Ініціалізація генератора випадкових чисел
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = minVal + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (maxVal - minVal)));
            }
        }
    }

    // Виведення матриці
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << std::setw(8) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Перевантаження оператора +
    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Перевантаження оператора -
    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Перевантаження оператора *
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrices cannot be multiplied (columns of the first != rows of the second)");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Перевантаження оператора /
    Matrix operator/(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (other.data[i][j] == 0) {
                    throw std::runtime_error("Division by zero in matrix elements.");
                }
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

    // Пошук максимального елемента
    T maxElement() const {
        T max = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] > max) {
                    max = data[i][j];
                }
            }
        }
        return max;
    }

    // Пошук мінімального елемента
    T minElement() const {
        T min = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] < min) {
                    min = data[i][j];
                }
            }
        }
        return min;
    }
};

int main() {
    // Створення двох матриць 3x3
    Matrix<int> mat1(3, 3);
    Matrix<int> mat2(3, 3);

    // Заповнення першої матриці випадковими числами
    mat1.fillRandom(1, 10);
    std::cout << "Matrix 1 (Random values):" << std::endl;
    mat1.display();

    // Заповнення другої матриці з клавіатури
    std::cout << "\nEnter values for Matrix 2:" << std::endl;
    mat2.fillFromInput();

    std::cout << "\nMatrix 2:" << std::endl;
    mat2.display();

    // Додавання матриць
    Matrix<int> matAdd = mat1 + mat2;
    std::cout << "\nMatrix 1 + Matrix 2:" << std::endl;
    matAdd.display();

    // Множення матриць
    Matrix<int> matMul = mat1 * mat2;
    std::cout << "\nMatrix 1 * Matrix 2:" << std::endl;
    matMul.display();

    // Пошук максимального і мінімального елементів у першій матриці
    std::cout << "\nMax element in Matrix 1: " << mat1.maxElement() << std::endl;
    std::cout << "Min element in Matrix 1: " << mat1.minElement() << std::endl;

    return 0;
}
