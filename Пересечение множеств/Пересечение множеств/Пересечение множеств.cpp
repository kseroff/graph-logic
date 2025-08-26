#include <iostream>
#include <set>
#include "Windows.h"
using namespace std;

void Peresech(set<int>* arr, int z) {
    set<int>end; // Конечный результат
    end = arr[0];
    set<int>::iterator it1;
    for (int i = 1; i < z; i++)
    {
        it1 = end.begin();
        set<int>::iterator it2 = arr[i].begin();

        while ((it1 != end.end()) && (it2 != arr[i].end())) {
            if (*it1 < *it2) {
                end.erase(it1++);
            }
            else if (*it2 < *it1) {
                ++it2;
            }
            else { // *it1 == *it2
                ++it1;
                ++it2;
            }
        }
    }
    end.erase(it1, end.end());
    cout << endl << "Результат: ";
    for (auto i : end)
        cout << i << " ";
}

int main()
{
    setlocale(LC_ALL,"");
    srand(time(NULL));
    for (;;) {
        int z, n;
        while (true) {
            system("cls");
            cout << "Введите кол-во множест: "; cin >> z;
            if (z >= 2) break;
            else { cout << "Ошибка. Число должно быть больше или равно 2\n"; }
            system("pause");
        }
        set<int>* arr = new set<int>[z]; // Наши множества
        // используем set чтобы не повторялись множества в них(одно и тоже число)
        system("cls");
        for (int m = 0; m < z; m++) {
            arr[m].erase(arr[m].begin(), arr[m].end()); // очистка списков для повтора
        }
        cout << "Количество множеств: " << z
            << "\n Выберете способ заполнения множеств: \n 1. Случайное заполнение \n" << " 2. Заполнить самому \n 3. Выход\n Введите: ";
        cin >> n;
        if (n == 1) {
            for (int i = 0; i < z; i++)
            {
                for (int j = 0; j < 2 + rand() % 8; j++)
                {
                    arr[i].insert(rand() % 20);
                }
                cout << endl << "Множество №" << i + 1 << ": " << endl;
                for (auto k : arr[i])
                    cout << k << " ";
            }
            Peresech(arr, z);
            cout << endl;
            system("pause");
        }
        if (n == 2) {
            system("cls");
            cout << "Заполните ваши множества\n";
            for (int i = 0; i < z; i++)
            {
                cout << endl << "Множество №" << i + 1 << "\nЧтобы остановить ввод введите *" << endl;
                string s;
                while (true) {
                    cin >> s;
                    if (s == "*") break;
                    else arr[i].insert(atoi(s.c_str()));
                }
            }
            Peresech(arr, z);
            cout << endl;
            system("pause");
        }
        if (n == 3) {
            exit(0);
        }
        delete[]arr;
    }
    return 0;
}

