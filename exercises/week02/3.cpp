#include <iostream>
using namespace std;

class MyVector {
private:
    int* data;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;

        int* newData = new int[capacity];

        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;

        data = newData;
    }

public:
    MyVector() {
        capacity = 2;
        size = 0;
        data = new int[capacity];
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize();
        }

        data[size] = value;
        size++;
    }

    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    int at(int index) {
        if (index < 0 || index >= size) {
            cout << "Index khong hop le!\n";
            return -1;
        }

        return data[index];
    }

    int getSize() {
        return size;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MyVector v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    v.print();

    v.pop_back();

    v.print();

    cout << "Phan tu tai index 1 = " << v.at(1);

    return 0;
}