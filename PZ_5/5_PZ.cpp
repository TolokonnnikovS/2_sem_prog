#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

// Предварительное объявление классов
class ArrTxt;
class ArrCSV;

class DynamicArray {
protected:
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

    // Оператор присваивания
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Деструктор
    virtual ~DynamicArray() {
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

    // Функция вывода в консоль
    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Виртуальная функция для вывода в файл
    virtual void printToFile() = 0;

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

    // Геттер для размера
    int getSize() const {
        return size;
    }

protected:
    // Функция для получения текущей даты и времени в формате для имени файла
    string getCurrentDateTime() {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        tm localTime = *localtime(&time);
        
        stringstream ss;
        ss << put_time(&localTime, "%Y-%m-%d_%H-%M-%S");
        return ss.str();
    }
};

// Класс для вывода в TXT файл
class ArrTxt : public DynamicArray {
public:
    ArrTxt(int arrSize) : DynamicArray(arrSize) {}
    
    ArrTxt(const DynamicArray& other) : DynamicArray(other) {}
    
    void printToFile() override {
        string filename = getCurrentDateTime() + ".txt";
        ofstream file(filename);
        
        if (file.is_open()) {
            file << "Dynamic Array (TXT format):" << endl;
            file << "Size: " << size << endl;
            file << "Elements: ";
            for (int i = 0; i < size; i++) {
                file << data[i];
                if (i < size - 1) file << " ";
            }
            file << endl;
            file.close();
            cout << "Данные сохранены в файл: " << filename << endl;
        } else {
            cout << "Ошибка: не удалось создать файл " << filename << endl;
        }
    }
    
    // Операция сложения массивов
    ArrTxt* add(const DynamicArray& other) {
        int maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrTxt* result = new ArrTxt(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            result->setValue(i, val1 + val2);
        }
        
        return result;
    }

    // Операция вычитания массивов
    ArrTxt* subtract(const DynamicArray& other) {
        int maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrTxt* result = new ArrTxt(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            result->setValue(i, val1 - val2);
        }
        
        return result;
    }
};

// Класс для вывода в CSV файл
class ArrCSV : public DynamicArray {
public:
    ArrCSV(int arrSize) : DynamicArray(arrSize) {}
    
    ArrCSV(const DynamicArray& other) : DynamicArray(other) {}
    
    void printToFile() override {
        string filename = getCurrentDateTime() + ".csv";
        ofstream file(filename);
        
        if (file.is_open()) {
            file << "Index,Value" << endl;
            for (int i = 0; i < size; i++) {
                file << i << "," << data[i] << endl;
            }
            file.close();
            cout << "Данные сохранены в файл: " << filename << endl;
        } else {
            cout << "Ошибка: не удалось создать файл " << filename << endl;
        }
    }
    
    // Операция сложения массивов
    ArrCSV* add(const DynamicArray& other) {
        int maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrCSV* result = new ArrCSV(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            result->setValue(i, val1 + val2);
        }
        
        return result;
    }

    // Операция вычитания массивов
    ArrCSV* subtract(const DynamicArray& other) {
        int maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrCSV* result = new ArrCSV(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.getSize()) ? other.getValue(i) : 0;
            result->setValue(i, val1 - val2);
        }
        
        return result;
    }
};

// Функция для демонстрации полиморфизма
void saveArrayToFile(DynamicArray& array) {
    array.printToFile();
}

int main() {
    // Тестирование базового функционала
    cout << "Создание массива ArrTxt размером 3:" << endl;
    ArrTxt arrTxt(3);
    arrTxt.setValue(0, 10);
    arrTxt.setValue(1, 20);
    arrTxt.setValue(2, 30);
    cout << "Массив ArrTxt: ";
    arrTxt.print();
    arrTxt.printToFile();

    cout << "\nСоздание массива ArrCSV размером 4:" << endl;
    ArrCSV arrCSV(4);
    arrCSV.setValue(0, 5);
    arrCSV.setValue(1, 15);
    arrCSV.setValue(2, 25);
    arrCSV.setValue(3, 35);
    cout << "Массив ArrCSV: ";
    arrCSV.print();
    arrCSV.printToFile();

    cout << "\nДобавление значения в ArrTxt:" << endl;
    arrTxt.addValue(40);
    cout << "ArrTxt после добавления: ";
    arrTxt.print();
    arrTxt.printToFile();

    cout << "\nДемонстрация полиморфизма:" << endl;
    DynamicArray* arrays[2];
    arrays[0] = new ArrTxt(2);
    arrays[0]->setValue(0, 100);
    arrays[0]->setValue(1, 200);
    
    arrays[1] = new ArrCSV(2);
    arrays[1]->setValue(0, 50);
    arrays[1]->setValue(1, 150);

    for (int i = 0; i < 2; i++) {
        cout << "Массив " << i + 1 << ": ";
        arrays[i]->print();
        saveArrayToFile(*arrays[i]);
        delete arrays[i];
    }

    cout << "\nТестирование операций с массивами:" << endl;
    ArrTxt arr1(3);
    arr1.setValue(0, 1);
    arr1.setValue(1, 2);
    arr1.setValue(2, 3);

    ArrCSV arr2(3);
    arr2.setValue(0, 4);
    arr2.setValue(1, 5);
    arr2.setValue(2, 6);

    ArrTxt* sum = arr1.add(arr2);
    cout << "Сумма массивов: ";
    sum->print();
    sum->printToFile();
    delete sum;

    ArrCSV* sum2 = arr2.add(arr1);
    cout << "Сумма массивов (CSV): ";
    sum2->print();
    sum2->printToFile();
    delete sum2;

    cout << "\nТестирование обработки ошибок:" << endl;
    arrTxt.setValue(10, 50); // Неверный индекс
    arrTxt.setValue(0, 150); // Неверное значение

    return 0;
}