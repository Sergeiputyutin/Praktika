#include <iostream>
#include <vector>

using namespace std;

void cocktailSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        // Проход слева направо (как в пузырьковой сортировке)
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;  // Если обменов не было, массив отсортирован

        swapped = false;
        end--;  // Уменьшаем правую границу

        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        start++;  // Увеличиваем левую границу
    }
}

int main() {
    vector<int> arr = { 5, 1, 4, 2, 8, 0, 2 };

    cout << "До сортировки: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    cocktailSort(arr);

    cout << "После сортировки: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}