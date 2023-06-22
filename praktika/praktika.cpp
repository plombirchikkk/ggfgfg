#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std;

////Структура для хранения координат города. 
struct City {
    int x;
    int y;
};

// Функция для подсчета количества городов слева и справа от железной дороги 
int countCities(const vector<City>& cities, const vector<int>& selected) {
    int leftCount = 0; // количество городов слева 
    int rightCount = 0; // количество городов справа  
    for (int i = 0; i < cities.size(); ++i) {
        // Если город находится в выбранных для железной дороги 
        if (find(selected.begin(), selected.end(), i) != selected.end()) {
            leftCount++; // увеличиваем счетчик городов слева 
        }
        else {
            rightCount++; // увеличиваем счетчик городов справа 
        }
    }
    // Возвращаем разницу между количеством городов слева и справа 
    return abs(leftCount - rightCount);
}

// Функция для вычисления стоимости строительства железной дороги между двумя городами 
int calculateCost(const vector<City>& cities, const vector<int>& selected) {
    int minX = cities[selected[0]].x; // минимальная координата X среди выбранных городов 
    int maxX = cities[selected[0]].x; // максимальная координата X среди выбранных городов 
    for (int i = 1; i < selected.size(); ++i) {
        int x = cities[selected[i]].x; // текущая координата X 
        // Находим минимальную и максимальную координаты X выбранных городов 
        if (x < minX) {
            minX = x;
        }
        if (x > maxX) {
            maxX = x;
        }
    }
    // Вычисляем длину железной дороги 
    int length = maxX - minX;
    return length;
}


int main() {
    setlocale(LC_ALL, "Russian");

    int k;
    cout << "Введите количество городов (четное число): ";
    cin >> k;
    // Проверка на четность числа городов
    if (k % 2 != 0) {
        cout << "Ошибка: количество городов должно быть четным." << endl;
        return 1; // Завершение программы с кодом ошибки
    }

    vector<City> cities(k);
    cout << "Введите координаты городов:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Город " << i + 1 << ":\n";
        cout << "  Координата X: ";
        cin >> cities[i].x;
        cout << "  Координата Y: ";
        cin >> cities[i].y;
    }

      return 0;
}