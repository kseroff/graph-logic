#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
#define INF 0x3f3f3f3f // бесконечность
ofstream fout("cppstudio.txt");

class Graph {
private:

    int** G; // матрица смежности
    int V; //кол-во вершин
public:
    //конструктор
    Graph(int V)
    {
        this->V = V;
        G = new int* [V];
        for (int i = 0; i < V; i++) {
            G[i] = new int[V];
            for (int j = 0; j < V; j++)
                G[i][j] = 0;
        }
    }
    //Деструктор(освобождение памяти)
    ~Graph() {
        for (int i = 0; i < V; i++)
            delete[] G[i];
        delete[] G;
    }
    //добавление
    void addEdge(int i, int j, int w) {
        G[i][j] = G[j][i] = w;
    }
    //вывод на экран матрицы
    void toString() {
        for (int i = 0; i < V; i++) {
            cout << i << " : ";
            for (int j = 0; j < V; j++) {
                cout << setw(5) << G[i][j] << " ";
                fout << setw(5) << G[i][j] << " ";
            }
            cout << endl;
            fout << endl;
        }
    }
    //алгоритм Прима
    void Prima();
    //алгоритм дейстра(из 10 лабораторной)
    void Dijkstra(int st);
};

void Graph::Prima() {
    Graph Gr(V); // в этот граф запишется наше дерево(иначе сжатый граф по условия алгоритма)
    int edge; // количество ребер
    edge = 0; // установила количество ребер равным 0

    // создать массив для отслеживания выбранной вершины
    // selected(выбранный) станет true, в противном случае false
    int* selected = new int[V];

    // изначально установить выбранное значение false (заполнение всего массива false)
    memset(selected, 0, (V * 2) * 2);

    // количество egde в минимальном связующем дереве будет
    // всегда меньше, чем (V -1), где V - количество вершин в графе

    // выберите 0-ю вершину и сделайте ее истинной
    selected[0] = true;

    int x, y;  // строка, номер столбца

    // печать по краю и весу
    cout << "Связь" << " : " << "Вес" << endl;
    while (edge < V - 1) {

        //Для каждой вершины в множестве S нашла все смежные вершины
         // вычислила расстояние от вершины , выбранной на шаге 1.
         // если вершина уже находится в наборе S, отбросываю ее в противном случае
         //выбираю другую вершину, ближайшую к выбранной вершине на шаге 1.

        int min = INF; x = 0; y = 0;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j]) { // не выбрано и есть край
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        Gr.addEdge(x, y, G[x][y]); // добавляем путь в наш граф.
        cout << x << " - " << y << " :  " << G[x][y] << endl;
        fout << x << " - " << y << " :  " << G[x][y] << endl;
        selected[y] = true;
        edge++;
    }
    //сложность n^2+e
    delete[] selected;

    int st;
    cout << endl << "Введите стартовую вершину: "; cin >> st;
    fout << endl << "Cтартовая вершина: " << st << endl;
    cout << endl;
    Gr.Dijkstra(st);
}

void Graph::Dijkstra(int st)
{
    int* distance = new int[V];
    bool* visited = new bool[V];
    int count, index;

    for (int i = 0; i < V; i++)
        distance[i] = INT_MAX, visited[i] = false;

    distance[st] = 0;

    for (count = 0; count < V - 1; count++)
    {
        int min = INT_MAX;
        for (int i = 0; i < V; i++)
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i]; index = i;
            }

        int u = index;
        visited[u] = true;
        for (int i = 0; i < V; i++)
            if (!visited[i] && G[u][i] && distance[u] != INT_MAX && distance[u] + G[u][i] < distance[i])
                distance[i] = distance[u] + G[u][i];
    }

    for (int i = 0; i < V; i++)
        if (distance[i] != INT_MAX) {
            cout << st << " > " << i << " = " << distance[i] << endl;
            fout << st << " > " << i << " = " << distance[i] << endl;
        }
        else {
            cout << st << " > " << i << " = " << "маршрут недоступен" << endl;
            fout << st << " > " << i << " = " << "маршрут недоступен" << endl;
        }
    delete[] distance;
    delete[] visited;
}

int main() {
    /*
    { 0, 9, 75, 0, 0 },
    { 9, 0, 95, 19, 42 },
    { 75, 95, 0, 51, 66 },
    { 0, 19, 51, 0, 31 },
    { 0, 42, 66, 31, 0 }

    c.addEdge(0 ,1, 9);
    c.addEdge(0, 2, 75);
    c.addEdge(1, 2, 95);
    c.addEdge(1, 3, 19);
    c.addEdge(1, 4, 42);
    c.addEdge(2, 3, 51);
    c.addEdge(2, 4, 66);
    c.addEdge(3, 4, 31);
    */
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int z = 5;
    cout << "Введите кол-во вершин графа: "; cin >> z;
    Graph c(z);

    string s;
    while (true) {
        system("cls");
        cout << "|------------------------|" << endl
            << "|  Количество вершин: " << z << "  |" << endl
            << "|------------------------|" << endl
            << "|          Меню          |" << endl
            << "|------------------------|" << endl
            << "| 1)Случайное заполнение |" << endl
            << "|------------------------|" << endl
            << "| 2)Заполнить самому     |" << endl
            << "|------------------------|" << endl
            << "| 3)Выход                |" << endl
            << "|------------------------|" << endl;

        cout << "       Введите: ";
        cin >> s;
        string q1, q2, q3;
        switch (atoi(s.c_str()))
        {
        case 1:
            system("cls");

            for (int i = 0; i < z; i++)
            {
                for (int j = i + 1; j < z; j++)
                {
                    if (bool(rand() % 2)) {
                        c.addEdge(i, j, rand() % 100);
                    }
                }
            }
            cout << "-----------------" << endl << "Матрица смежности: \n";
            fout << endl << "-----------------" << endl << "Матрица смежности: \n";
            c.toString();
            cout << endl << "-----------------" << endl << "Ответ: \n";
            fout << endl << "-----------------" << endl << "Ответ: \n";
            c.Prima();

            system("pause");
            break;
        case 2:
            system("cls");
            while (1) {
                system("cls");
                cout << "Для выхода введите *" << endl;
                cout << "Введите 1-вершину: "; cin >> q1;
                if (q1 == "*") break;
                cout << "Введите 2-вершину: "; cin >> q2;
                if (q1 == "*") break;
                cout << "Введите Вес ребра: "; cin >> q3;
                if (q1 == "*") break;
                c.addEdge(atoi(q1.c_str()), atoi(q2.c_str()), atoi(q3.c_str()));
                cout << endl;
                c.toString();
                system("pause");
            }
            system("cls");
            cout << "-----------------" << endl << "Матрица смежности: \n";
            fout << endl << "-----------------" << endl << "Матрица смежности: \n";
            c.toString();
            cout << endl << "-----------------" << endl << "Ответ: \n";
            fout << endl << "-----------------" << endl << "Ответ: \n";
            c.Prima();

            system("pause");
            break;
        case 3:
            exit(0);
            break;
        }
        system("cls");
    }

    fout.close();
    return 0;
}