#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale> // Для setlocale

using namespace std;

// Функция для записи массива в файл
void saveToFile(const string& filename, const vector<int>& arr) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка при открытии файла " << filename << endl;
        return;
    }
    for (int num : arr) {
        outFile << num << " ";
    }
    outFile.close();
    cout << "Массив сохранён в файл: " << filename << endl;
}

// Шейкерная сортировка
void cocktailSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        // Проход слева направо
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

// Генерация случайного массива в заданном диапазоне
vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    vector<int> arr(size);
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
    return arr;
}

int main() {
    // Устанавливаем локаль для поддержки русского языка
    setlocale(LC_ALL, "Russian");

    vector<int> arr;
    int choice;

    do {
        cout << "\n=== Меню шейкерной сортировки ===\n";
        cout << "1. Ввести массив вручную\n";
        cout << "2. Сгенерировать случайный массив\n";
        cout << "3. Отсортировать массив и сохранить в файлы\n";
        cout << "4. Вывести текущий массив\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
    switch (choice) {
        case 1: {
            int n, num;
            cout << "Введите количество элементов: ";
            cin >> n;
            arr.clear();
            cout << "Введите элементы: ";
            for (int i = 0; i < n; ++i) {
                cin >> num;
                arr.push_back(num);
            }
            saveToFile("unsorted.txt", arr);
            break;
        }
        case 2: {
            int size, minVal, maxVal;
            cout << "Введите размер массива: ";
            cin >> size;
            cout << "Введите минимальное значение: ";
            cin >> minVal;
            cout << "Введите максимальное значение: ";
            cin >> maxVal;
            arr = generateRandomArray(size, minVal, maxVal);
            cout << "Сгенерированный массив: ";
            for (int num : arr) cout << num << " ";
            cout << endl;
            saveToFile("unsorted.txt", arr);
            break;
        }
        case 3: {
            if (arr.empty()) {
                cout << "Массив пуст! Сначала введите или сгенерируйте его.\n";
            }
            else {
                vector<int> sortedArr = arr;
                cocktailSort(sortedArr);
                saveToFile("sorted.txt", sortedArr);
                cout << "Исходный массив сохранён в unsorted.txt\n";
                cout << "Отсортированный массив сохранён в sorted.txt\n";
            }
            break;
        }
        case 4: {
            if (arr.empty()) {
                cout << "Массив пуст!\n";
            }
            else {
                cout << "Текущий массив: ";
                for (int num : arr) cout << num << " ";
                cout << endl;
            }
            break;
        }
        case 5: {
            cout << "Выход...\n";
            break;
        }
        default: {
            cout << "Неверный выбор!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
    } while (choice != 5);

    return 0;
}
