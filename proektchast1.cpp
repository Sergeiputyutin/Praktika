#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// функция для записи массива в файл
void saveToFile(const string& filename, const vector<int>& arr) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        outFile << arr[i] << " ";
    }
    outFile.close();
    cout << "Массив сохранен в файл: " << filename << endl;
}

// Шейкерная сортировка
void cocktailSort(vector<int>& arr, int& comparisons, int& swaps) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;
    comparisons = 0;
    swaps = 0;

    while (swapped) {
        swapped = false;

        // Проход слева направо
        for (int i = start; i < end; i++) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swaps++;
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Проход справа налево
        for (int i = end; i >= start; i--) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swaps++;
                swapped = true;
            }
        }

        start++;
    }
}


vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    vector<int> arr(size);
    srand(time(0)); // Инициализация генератора случайных чисел

    for (int i = 0; i < size; i++) {
        // Для больших диапазонов используем другой подход
        if (maxVal - minVal > RAND_MAX) {
            // Генерация через два вызова rand() для больших диапазонов
            long long range = (long long)maxVal - (long long)minVal + 1;
            long long randomValue = (long long)rand() * RAND_MAX + rand();
            arr[i] = minVal + (randomValue % range);
        }
        else {
            // Стандартный способ для небольших диапазонов
            arr[i] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    return arr;
}
void showAuthorsInfo() {
    cout << "====================================" << endl;
    cout << "       Шейкерная сортировка" << endl;
    cout << "====================================" << endl;
    cout << "Выполнили работу:" << endl;
    cout << "1. Хмельков Максим" << endl;
    cout << "2. Путютин Сергей" << endl;
    cout << "3. Соколов Олег" << endl;
    cout << "Группа: 24ВВВ1" << endl;
    cout << "Бригада: №2" << endl;
    cout << "====================================" << endl << endl;
}

int main() {
    setlocale(0, ""); // русский язык
    vector<int> arr;
    int choice;
    string inputFilename = "unsorted.txt";
    string outputFilename = "sorted.txt";

    showAuthorsInfo(); // Показываем информацию об авторах

    while (true) {
        cout << "\nМеню шейкерной сортировки:\n";
        cout << "1. Ввести массив вручную\n";
        cout << "2. Сгенерировать случайный массив\n";
        cout << "3. Отсортировать массив\n";
        cout << "4. Показать массив\n";
        cout << "5. Изменить имена файлов (по умолчанию: unsorted.txt, sorted.txt)\n";
        cout << "6. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "Введите количество элементов: ";
            cin >> n;
            arr.resize(n);
            cout << "Введите элементы: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            saveToFile(inputFilename, arr);
        }
        else if (choice == 2) {
            int size, minVal, maxVal;
            cout << "Введите размер массива: ";
            cin >> size;
            cout << "Введите минимальное значение: ";
            cin >> minVal;
            cout << "Введите максимальное значение: ";
            cin >> maxVal;

            if (minVal > maxVal) {
                cout << "Ошибка: минимальное значение больше максимального!" << endl;
                continue;
            }

            arr = generateRandomArray(size, minVal, maxVal);
            cout << "Массив успешно создан и сохранён в файл." << endl;
            saveToFile(inputFilename, arr);
        }
        else if (choice == 3) {
            if (arr.empty()) {
                cout << "Массив пуст!" << endl;
                continue;
            }

            int comparisons = 0, swaps = 0;

            // Измерение времени алгоритма
            clock_t start = clock();
            cocktailSort(arr, comparisons, swaps);
            clock_t end = clock();

            double time = (double)(end - start) / CLOCKS_PER_SEC; // секунды

            saveToFile(outputFilename, arr);
            cout << "Массив отсортирован и сохранен\n";
            cout << "Время сортировки: " << time << " секунд\n";
            cout << "Перестановок: " << swaps << endl;
        }
        else if (choice == 4) {
            if (arr.empty()) {
                cout << "Массив пуст!" << endl;
            }
            else {
                cout << "Текущий массив: ";
                for (int num : arr) cout << num << " ";
                cout << endl;
            }
        }
        else if (choice == 5) {
            cout << "Текущее имя файла для неотсортированного массива: " << inputFilename << endl;
            cout << "Введите новое имя файла: ";
            cin >> inputFilename;
            cout << "Текущее имя файла для отсортированного массива: " << outputFilename << endl;
            cout << "Введите новое имя файла: ";
            cin >> outputFilename;
            cout << "Имена файлов успешно изменены." << endl;
        }
        else if (choice == 6) {
            cout << "Выход из программы..." << endl;
            break;
        }
        else {
            cout << "Неверный выбор!" << endl;
            cin.clear();
            while (cin.get() != '\n'); // Очистка буфера ввода
        }
    }

    return 0;
}
