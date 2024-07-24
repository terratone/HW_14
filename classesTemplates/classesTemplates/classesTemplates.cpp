#include <iostream>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()

using namespace std;

template<typename T>
class Matrix {
private:
    T** data;  // Данные матрицы
    int rows;  // Количество строк
    int cols;  // Количество столбцов

public:
    // Конструктор
    Matrix(int r, int c) : rows(r), cols(c) {
        // Динамическое выделение памяти для матрицы
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    // Деструктор
    ~Matrix() {
        // Освобождение памяти
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Метод для заполнения матрицы с клавиатуры
    void fillFromInput() {
        cout << "Input elements of matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    // Метод для заполнения матрицы случайными значениями
    void fillRandom() {
        // Инициализация генератора случайных чисел
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = rand() % 100; // Случайные числа от 0 до 99
            }
        }
    }

    // Метод для отображения матрицы
    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t"; // Печать с табуляцией
            }
            cout << endl;
        }
    }

    // Перегрузка оператора сложения
    Matrix operator+(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора вычитания
    Matrix operator-(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора умножения
    Matrix operator*(const Matrix& other) {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0; // Инициализация элемента
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Перегрузка оператора деления
    Matrix operator/(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (other.data[i][j] != 0) { // Проверка на деление на ноль
                    result.data[i][j] = data[i][j] / other.data[i][j];
                }
                else {
                    result.data[i][j] = 0; // Или любое другое значение по вашему выбору
                }
            }
        }
        return result;
    }

    // Поиск максимального элемента
    T findMax() const {
        T maxVal = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] > maxVal) {
                    maxVal = data[i][j];
                }
            }
        }
        return maxVal;
    }

    // Поиск минимального элемента
    T findMin() const {
        T minVal = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] < minVal) {
                    minVal = data[i][j];
                }
            }
        }
        return minVal;
    }
};

int main() {
    srand(time(NULL));

    int rows, cols;
    cout << "Input a number of cols and rows: ";
    cin >> rows >> cols;

    Matrix<int> mat1(rows, cols);
    Matrix<int> mat2(rows, cols);
    mat1.fillRandom(); // Заполнение первой матрицы случайными числами
    mat2.fillRandom(); // Заполнение второй матрицы случайными числами

    int choice;
    do {
        cout << "\nChoose an option:\n";
        cout << "1. Show matrices\n";
        cout << "2. Add matrices\n";
        cout << "3. Subtract matrices\n";
        cout << "4. Multiply matrices\n";
        cout << "5. Divide matrices\n";
        cout << "6. Find maximal element in the first matrix\n";
        cout << "7. Find minimal element in the second matrix\n";
        cout << "0. Exit\n";
        cout << "Yer choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Matrix 1:\n";
            mat1.display();
            cout << "Matrix 2:\n";
            mat2.display();
            break;
        case 2:
        {
            Matrix<int> sum = mat1 + mat2;
            cout << "The sum of matrices:\n";
            sum.display();
        }
        break;
        case 3:
        {
            Matrix<int> diff = mat1 - mat2;
            cout << "The subtraction of matrices:\n";
            diff.display();
        }
        break;
        case 4:
        {
            Matrix<int> prod = mat1 * mat2;
            cout << "The multiplication of matrices:\n";
            prod.display();
        }
        break;
        case 5:
        {
            Matrix<int> div = mat1 / mat2;
            cout << "The division of matrices:\n";
            div.display();
        }
        break;
        case 6:
            cout << "Maximal element of the 1 matrix: " << mat1.findMax() << endl;
            break;
        case 7:
            cout << "Minimal element of the 1 matrix: " << mat1.findMin() << endl;
            break;
        case 0:
            cout << "Exit.\n";
            break;
        default:
            cout << "Wrong choice. Try again\n";
            break;
        }
    } while (choice != 0);

    return 0;
}