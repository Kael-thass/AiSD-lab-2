#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class CircularBuffer {
private:
    T* data;
    int head;
    int tail;
    int count;
    int capacity;

public:
    CircularBuffer(int size) {
        capacity = size;
        data = new T[capacity];
        head = 0;
        tail = 0;
        count = 0;
    }

    ~CircularBuffer() {
        delete[] data;
    }

    void push(const T& value) {
        if (isFull()) {
            throw overflow_error("Буфер заполнен");
        }
        data[tail] = value;
        tail = (tail + 1) % capacity;
        count++;
    }

    T pop() {
        if (isEmpty()) {
            throw underflow_error("Буфер пуст");
        }
        T value = data[head];
        head = (head + 1) % capacity;
        count--;
        return value;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "--- Тест для типа int ---" << endl;
    CircularBuffer<int> intBuf(3);

    intBuf.push(10);
    intBuf.push(20);
    intBuf.push(30);

    cout << "Буфер полон: " << (intBuf.isFull() ? "Да" : "Нет") << endl;

    try {
        intBuf.push(40);
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    cout << "Достаем элементы: ";
    while (!intBuf.isEmpty()) {
        cout << intBuf.pop() << " ";
    }
    cout << endl;

    cout << "\n--- Тест для типа double ---" << endl;
    CircularBuffer<double> doubleBuf(2);

    doubleBuf.push(3.14);
    doubleBuf.push(2.71);

    cout << "Достаем элементы: ";
    cout << doubleBuf.pop() << ", " << doubleBuf.pop() << endl;

    return 0;
}
