#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicArray {
private:
    int *data;
    int size;

public:
    // Конструктор
    DynamicArray(int arrSize) {
        if (arrSize < 0) {
            throw invalid_argument("Размер массива не может быть отрицательным");
        }
        size = arrSize;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    // Сеттер
    void setValue(int index, int value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс " + to_string(index) + " выходит за границы массива");
        }
        if (value < -100 || value > 100) {
            throw invalid_argument("Значение " + to_string(value) + " выходит за пределы [-100, 100]");
        }
        data[index] = value;
    }

    // Геттер
    int getValue(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс " + to_string(index) + " выходит за границы массива");
        }
        return data[index];
    }

    // Функция вывода
    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Добавление значения в конец
    void addValue(int value) {
        if (value < -100 || value > 100) {
            throw invalid_argument("Значение " + to_string(value) + " выходит за пределы [-100, 100]");
        }
        int* newData = new int[size + 1];
        
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        newData[size] = value;
        
        delete[] data;
        data = newData;
        size += 1;
    }

    // Операция сложения массивов
    DynamicArray add(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 + val2;
        }
        
        return result;
    }

    // Операция вычитания массивов
    DynamicArray subtract(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 - val2;
        }
        
        return result;
    }

    // Геттер для размера
    int getSize() const {
        return size;
    }
};


class Func : public DynamicArray {
public:
    Func(int size) : DynamicArray(size) {}
    
    void printFunc() {
        cout << "Выполняется вычисление медианного значения" << endl;
    }

    void printMedian() {
        printFunc();
        double mediana;
        if (getSize() % 2 == 0) {
            mediana = (getValue(getSize() / 2 - 1) + getValue(getSize() / 2)) / 2.0;
        } else {
            mediana = getValue(getSize() / 2);
        }
        cout << "Медианное число: " << mediana << endl;
    }

    void printAverage() {
        if (getSize() == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        double average = 0.0;
        for (int i = 0; i < getSize(); i++) { 
            average += getValue(i);
        }
        cout << "Среднее значение равно: " << average / getSize() << endl;
    }

    void minValue() {
        int min_value = getValue(0);
        for (int i = 0; i < getSize(); i++){
            if(min_value >= getValue(i)){
                min_value = getValue(i);
            }
        }
        cout << "Минимальное значение равно " << min_value << endl;
    }

    void maxValue() {
        int max_value = getValue(0);
        for (int i = 0; i < getSize(); i++){
            if(max_value <= getValue(i)){
                max_value = getValue(i);
            }
        }
        cout << "Максимальное значение равно " << max_value << endl;
    }
};

int main() {
    try {
        // Тестирование класса
        cout << "Создание массива A размером 3:" << endl;
        DynamicArray arrA(3);
        arrA.setValue(0, 10);
        arrA.setValue(1, 20);
        arrA.setValue(2, 30);
        cout << "Массив A: ";
        arrA.print();

        cout << "\nСоздание массива B размером 5:" << endl;
        DynamicArray arrB(5);
        arrB.setValue(0, 5);
        arrB.setValue(1, 15);
        arrB.setValue(2, 25);
        arrB.setValue(3, 35);
        arrB.setValue(4, 45);
        cout << "Массив B: ";
        arrB.print();

        cout << "\nТестирование конструктора копирования:" << endl;
        DynamicArray arrC = arrA;
        cout << "Массив C (копия A): ";
        arrC.print();

        cout << "\nДобавление значения 40 в массив A:" << endl;
        arrA.addValue(40);
        cout << "Массив A после добавления: ";
        arrA.print();

        cout << "\nСложение массивов A и B:" << endl;
        DynamicArray sum = arrA.add(arrB);
        cout << "A + B: ";
        sum.print();

        cout << "\nВычитание массивов A и B:" << endl;
        DynamicArray diff = arrA.subtract(arrB);
        cout << "A - B: ";
        diff.print();

        cout << "\nТестирование исключений:" << endl;
        try {
            arrA.setValue(10, 50); // Неверный индекс
        } catch (const out_of_range& e) {
            cout << "Поймано исключение out_of_range: " << e.what() << endl;
        }
        
        try {
            arrA.setValue(0, 150); // Неверное значение
        } catch (const invalid_argument& e) {
            cout << "Поймано исключение invalid_argument: " << e.what() << endl;
        }
        
        // Тестирование класса Func с обработкой исключений
        cout << "\nТестирование класса Func:" << endl;
        Func funcArr(5);
        funcArr.setValue(0, 10);
        funcArr.setValue(1, 20);
        funcArr.setValue(2, 30);
        funcArr.setValue(3, 40);
        funcArr.setValue(4, 50);
        
        funcArr.printAverage();
        funcArr.printMedian();
        funcArr.minValue();
        funcArr.maxValue();

    } catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}