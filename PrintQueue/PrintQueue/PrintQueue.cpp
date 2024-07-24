#include <iostream> // Для ввода-вывода
#include <ctime>   // Для работы со временем
#include <cstring> // Для работы со строками

using namespace std;

// Структура для представления клиента
struct Client {
    char name[50]; // Имя клиента
    int priority;  // Приоритет
};

// Структура для представления статистики печати
struct PrintJob {
    char clientName[50]; // Имя клиента
    time_t requestTime;   // Время запроса
};

// Класс очереди для клиентов
class PrintQueue {
private:
    Client queue[100];    // Массив для хранения очереди клиентов
    int front;            // Индекс начала очереди
    int rear;             // Индекс конца очереди
    int size;             // Текущий размер очереди

public:
    // Конструктор
    PrintQueue() : front(0), rear(0), size(0) {}

    // Метод для добавления клиента в очередь с учетом приоритета
    void enqueue(Client client) {
        if (size == 100) {
            cout << "The queue is full!" << endl;
            return;
        }
        // Поиск позиции для вставки согласно приоритету
        int i = rear;
        while (i > front && queue[i - 1].priority < client.priority) {
            queue[i] = queue[i - 1];  // Сдвигаем клиентов
            i--;
        }
        queue[i] = client; // Вставляем клиента
        rear++;
        size++;
    }

    // Метод для извлечения клиента из очереди
    Client dequeue() {
        if (size == 0) {
            cout << "The queue is empty!" << endl;
            return Client(); // Возвращаем пустого клиента
        }
        Client client = queue[front]; // Получаем клиента с высокой приоритетностью
        front++;
        size--;
        return client; // Возвращаем клиента
    }

    // Метод для проверки, пуста ли очередь
    bool isEmpty() {
        return size == 0;
    }

    // Метод для получения текущего размера очереди
    int getSize() {
        return size;
    }
};

// Класс для хранения статистики печати
class PrintStatistics {
private:
    PrintJob stats[100];  // Массив для хранения статистики
    int count;            // Количество напечатанных работ

public:
    // Конструктор
    PrintStatistics() : count(0) {}

    // Метод для добавления статистики о печати
    void addStat(const char* clientName) {
        if (count < 100) {
            strncpy_s(stats[count].clientName, clientName, 49);
            stats[count].clientName[49] = '\0'; // Гарантируем полное завершение строки
            stats[count].requestTime = time(nullptr); // Получаем текущее время
            count++;
        }
        else {
            cout << "Stat is full!" << endl;
        }
    }

    // Метод для отображения статистики печати
    void displayStats() {
        cout << "Printing statistics:" << endl;
        for (int i = 0; i < count; i++) {
            char buffer[26]; // Буфер для хранения времени
            ctime_s(buffer, sizeof(buffer), &stats[i].requestTime); // Используем ctime_s
            cout << "Client: " << stats[i].clientName << ", Time: " << buffer;
        }
    }
};

int main() {
    PrintQueue printQueue;         // Создаем очередь печати
    PrintStatistics printStats;    // Создаем очередь для статистики
    int choice;                   // Переменная выбора действия

    // Цикл работы программы
    do {
        cout << "1. Add a print request" << endl;
        cout << "2. Print the following request" << endl;
        cout << "3. Display printing statistics" << endl;
        cout << "0. Exit" << endl;
        cout << "Yer choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Client newClient; // Новый клиент
            cout << "Enter the client's name: ";
            cin >> newClient.name; // Считываем имя клиента
            cout << "Enter the priority (1-10): ";
            cin >> newClient.priority; // Считываем приоритет
            printQueue.enqueue(newClient); // Добавляем клиента в очередь
            break;
        }
        case 2: {
            if (!printQueue.isEmpty()) {
                Client clientToPrint = printQueue.dequeue(); // Извлекаем клиента для печати
                printStats.addStat(clientToPrint.name); // Добавляем в статистику
                cout << "Printed a request from a client: " << clientToPrint.name << endl;
            }
            else {
                cout << "No customers in the queue!" << endl;
            }
            break;
        }
        case 3:
            printStats.displayStats(); // Выводим статистику
            break;
        case 0:
            cout << "Exit." << endl; // Выход
            break;
        default:
            cout << "Wrong choice. Please try again." << endl;
            break;
        }
    } while (choice != 0); // Завершаем цикл по команде выхода

    return 0;
}