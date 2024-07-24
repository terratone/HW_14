#include <iostream> 
#include <cstring>  

using namespace std;

// ������� ��� �������� ������������ ����������� ������
void checkBrackets(const char* str) {
    // ���� ��� �������� ����������� ������
    char stack[100]; // ������������, ��� ������������ ����� ������ 100
    int top = -1; // ������ ������� ����� (-1 ��������, ��� ���� ����)

    // �������� �� ������� ������� ������
    for (int i = 0; str[i] != ';' && str[i] != '\0'; i++) { // ���� ������������ �� ';' ��� ����� ������
        char ch = str[i]; // ������� ������

        // ���� ������ - ����������� ������
        if (ch == '{' || ch == '(' || ch == '[') {
            stack[++top] = ch; // ��������� � � ����
        }
        // ���� ������ - ����������� ������
        else if (ch == '}' || ch == ')' || ch == ']') {
            // ���� ���� ����, ������, ��� ��������������� ����������� ������
            if (top < 0) {
                cout << "Error: the closing bracket '" << ch
                    << "' was found without the corresponding opening bracket.\n";
                // ������� ������ �� ����� ������
                cout << "String before the error: " << string(str).substr(0, i + 1) << "\n";
                return; // ��������� ����������
            }

            // ��������� ������������ ����������� ������ ��������� �����������
            char lastOpen = stack[top--]; // ����� ��������� ����������� ������ � ������� � �� �����
            if ((ch == '}' && lastOpen != '{') ||
                (ch == ')' && lastOpen != '(') ||
                (ch == ']' && lastOpen != '[')) {
                cout << "Error: parenthesis mismatch found\n";
                // ������� ������ �� ����� ������
                cout << "String before the error: " << string(str).substr(0, i + 1) << "\n";
                return; // ��������� ����������
            }
        }
    }

    // ���� �� ���� ����� ���� �� ����, ������, ���� ���������� ����������� ������
    if (top >= 0) {
        cout << "Error: there are unclosed opening brackets.\n";
        // ������� ������ �� ����� ������
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