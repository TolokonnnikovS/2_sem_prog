#include <iostream>
using namespace std;

class DynamicArray {
private:
    int *data;
    int size;

public:
    // Конструктор
    DynamicArray(int arrSize) {
        if (arrSize < 0) {
            cout << "Ошибка: размер не может быть отрицательным" << endl;
            size = 0;
            data = nullptr;
            return;
        }
        size = arrSize;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0; // Инициализируем нулями вместо случайных значений
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
        if (0 <= index && index < size) {
            if (-100 <= value && value <= 100) {
                data[index] = value;
            } else {
                cout << "Ошибка: значение " << value << " выходит за пределы [-100, 100]" << endl;
            }
        } else {
            cout << "Ошибка: индекс " << index << " выходит за границы массива" << endl;
        }
    }

    // Геттер
    int getValue(int index) const {
        if (0 <= index && index < size) {
            return data[index];
        } else {
            cout << "Ошибка: индекс " << index << " выходит за границы массива" << endl;
            return 0;
        }
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
        if (-100 <= value && value <= 100) {
            int* newData = new int[size + 1];
            
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            
            newData[size] = value;
            
            delete[] data;
            data = newData;
            size += 1;
        } else {
            cout << "Ошибка: значение " << value << " выходит за пределы [-100, 100]" << endl;
        }
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


class Func {
public:
    static void printFunc() {
        cout << "Выполняется вычисление медианного значения" << endl;
    }

    static void printMedian(const DynamicArray& arr) {
        printFunc();
        int size = arr.getSize();  // используем геттер
        if (size == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        
        double mediana;
        if (size % 2 == 0) {
            mediana = (arr.getValue(size / 2 - 1) + arr.getValue(size / 2)) / 2.0;
        } else {
            mediana = arr.getValue(size / 2);
        }
        cout << "Медианное число: " << mediana << endl;
    }

    static void printAverage(const DynamicArray& arr) {
        int size = arr.getSize();  // используем геттер
        if (size == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        double average = 0.0;
        for (int i = 0; i < size; i++) { 
            average += arr.getValue(i);  // используем геттер
        }
        cout << "Среднее значение равно: " << average / size << endl;
    }

    static void minValue(const DynamicArray& arr) {
        int size = arr.getSize();  // используем геттер
        if (size == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        int min_value = arr.getValue(0);  // используем геттер
        for (int i = 1; i < size; i++) {  // начинаем с 1
            if (min_value > arr.getValue(i)) {
                min_value = arr.getValue(i);
            }
        }
        cout << "Минимальное значение равно " << min_value << endl;
    }

    static void maxValue(const DynamicArray& arr) {
        int size = arr.getSize();  // используем геттер
        if (size == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        int max_value = arr.getValue(0);  // используем геттер
        for (int i = 1; i < size; i++) {  // начинаем с 1
            if (max_value < arr.getValue(i)) {
                max_value = arr.getValue(i);
            }
        }
        cout << "Максимальное значение равно " << max_value << endl;
    }
};

int main() {
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

    cout << "\nТестирование обработки ошибок:" << endl;
    arrA.setValue(10, 50); // Неверный индекс
    arrA.setValue(0, 150); // Неверное значение


    cout << "\n=== АНАЛИЗ МАССИВОВ ===" << endl;
    
    cout << "\nАнализ массива A:" << endl;
    Func::printMedian(arrA);
    Func::printAverage(arrA);
    Func::minValue(arrA);
    Func::maxValue(arrA);
    
    cout << "\nАнализ массива B:" << endl;
    Func::printMedian(arrB);
    Func::printAverage(arrB);
    Func::minValue(arrB);
    Func::maxValue(arrB);
    
    cout << "\nАнализ массива C:" << endl;
    Func::printMedian(arrC);
    Func::printAverage(arrC);
    Func::minValue(arrC);
    Func::maxValue(arrC);

    return 0;
}