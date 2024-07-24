#include <iostream>
#include <cstdlib> // Для rand() и srand()
#include <ctime> // Для time()
#include <set> // Для хранения уникальных чисел

using namespace std;

// Инициализация массива случайными уникальными числами
template <typename T>
void initializeRandomArray(T arr[], int size, T min_val, T max_val) {
    set<T> unique_numbers;
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        T rand_num;
        do {
            rand_num = static_cast<T>(rand() % (max_val - min_val + 1) + min_val);
        } while (unique_numbers.count(rand_num));
        unique_numbers.insert(rand_num);
        arr[i] = rand_num;
    }
}

// Поиск максимума
template <typename T>
T findMax(const T arr[], int size) {
    T max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Поиск минимума
template <typename T>
T findMin(const T arr[], int size) {
    T min = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Пузырьковая сортировка (Bubble Sort)
template <typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Обмен элементов
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Двоичный поиск
template <typename T>
int binarySearch(const T arr[], int size, T target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // Найден элемент
        }
        else if (arr[mid] < target) {
            left = mid + 1; // Ищем в правой половине
        }
        else {
            right = mid - 1; // Ищем в левой половине
        }
    }
    return -1; // Элемент не найден
}

// Замена элемента массива
template <typename T>
void replaceElement(T arr[], int size, int index, T newValue) {
    if (index >= 0 && index < size) {
        arr[index] = newValue;
    }
    else {
        cerr << "Error: the index is out of range" << endl;
    }
}

int main() {
    const int SIZE = 10;
    int arr[SIZE];

    // Инициализация массива случайными числами
    initializeRandomArray(arr, SIZE, 1, 100);

    // Вывод исходного массива
    cout << "Source array: ";
    for (int i = 0; i < SIZE; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Поиск максимума и минимума
    cout << "Maximum: " << findMax(arr, SIZE) << endl;
    cout << "Minimum: " << findMin(arr, SIZE) << endl;

    // Сортировка массива
    bubbleSort(arr, SIZE);

    // Сортированный массив
    cout << "Sorted array: ";
    for (int i = 0; i < SIZE; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Двоичный поиск
    int target = arr[SIZE / 2]; // Берем средний элемент как цель для демонстрации
    int index = binarySearch(arr, SIZE, target);
    if (index != -1) {
        cout << "the element " << target << " was found at the index " << index << endl;
    }
    else {
        cout << "the element " << target << " was not found" << endl;
    }

    // Замена элемента
    replaceElement(arr, SIZE, 2, 999); // Замена третьего элемента значением 999

    // Вывод массива после замены элемента
    cout << "array after the element change: ";
    for (int i = 0; i < SIZE; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}