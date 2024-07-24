#include <iostream> 
#include <cstring>  

using namespace std;

// Функция для проверки корректности расстановки скобок
void checkBrackets(const char* str) {
    // Стек для хранения открывающих скобок
    char stack[100]; // Предполагаем, что максимальная длина строки 100
    int top = -1; // Индекс вершины стека (-1 означает, что стек пуст)

    // Проходим по каждому символу строки
    for (int i = 0; str[i] != ';' && str[i] != '\0'; i++) { // Цикл продолжается до ';' или конца строки
        char ch = str[i]; // Текущий символ

        // Если символ - открывающая скобка
        if (ch == '{' || ch == '(' || ch == '[') {
            stack[++top] = ch; // Добавляем её в стек
        }
        // Если символ - закрывающая скобка
        else if (ch == '}' || ch == ')' || ch == ']') {
            // Если стек пуст, значит, нет соответствующей открывающей скобки
            if (top < 0) {
                cout << "Error: the closing bracket '" << ch
                    << "' was found without the corresponding opening bracket.\n";
                // Выводим строку до места ошибки
                cout << "String before the error: " << string(str).substr(0, i + 1) << "\n";
                return; // Завершаем выполнение
            }

            // Проверяем соответствие закрывающей скобки последней открывающей
            char lastOpen = stack[top--]; // Берем последнюю открывающую скобку и убираем её из стека
            if ((ch == '}' && lastOpen != '{') ||
                (ch == ')' && lastOpen != '(') ||
                (ch == ']' && lastOpen != '[')) {
                cout << "Error: parenthesis mismatch found\n";
                // Выводим строку до места ошибки
                cout << "String before the error: " << string(str).substr(0, i + 1) << "\n";
                return; // Завершаем выполнение
            }
        }
    }

    // Если на этом этапе стек не пуст, значит, есть незакрытые открывающие скобки
    if (top >= 0) {
        cout << "Error: there are unclosed opening brackets.\n";
        // Выводим строку до места ошибки
        cout << "String before the error:: " << str << "\n";
    }
    else {
        cout << "The parenthesis arrangement string is correct\n";
    }
}

int main() {
    const char str[] = "({x-y-z} * [x+2y] - (z+4x));"; 
    cout << str << endl;
    checkBrackets(str); 
    cout << endl;

    char str2[] = "((x+y+7z) + [x-6y} + {x+9z});";
    cout << str2 << endl;
    checkBrackets(str2);

    return 0; 