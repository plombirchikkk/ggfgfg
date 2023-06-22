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
// Функция для поиска всех возможных проектов строительства железной дороги 
vector < vector < int >> findRailwayProjects(const vector<City>& cities) {
    vector < vector < int >> projects; // список проектов 

    int k = cities.size(); // количество городов 
    int halfK = k / 2;  // половина количества городов 

    vector<int> selected(halfK, 0); // список выбранных городов 
    vector<bool> mask(k, false); // булевский массив для генерации комбинаций 

    // Инициализация маски для первых halfK городов 
    for (int i = 0; i < halfK; ++i) {
        mask[i] = true;// отмечаем первые половину городов как выбранные 
    }

    // Перебор всех комбинаций городов 
    do {
        vector<int> project; // текущий проект 
        for (int i = 0; i < k; ++i) {
            if (mask[i]) { // если город находится в выбранных 
                project.push_back(i); // добавляем его в проект 
            }
        }
        // Если количество городов слева и справа одинаково, добавляем проект в список 
        if (countCities(cities, project) == 0) {
            projects.push_back(project);
        }
    } while (prev_permutation(mask.begin(), mask.end())); // генерируем новую комбинацию городов 

    // Сортировка проектов по стоимости
    sort(projects.begin(), projects.end(), [&](const vector<int>& p1, const vector<int>& p2) {
        return calculateCost(cities, p1) < calculateCost(cities, p2);
        });


    return projects;
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