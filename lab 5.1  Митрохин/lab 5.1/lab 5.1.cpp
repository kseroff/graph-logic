#include <iostream>
#include <set>
#include <iterator>
using namespace std;

class Graph {
private:

    bool** adjMatrix;
    int numVerticesM;
    int numVerticesS;
    set <int>* arr;

public:

    Graph(int numVertices)
    {
        this->numVerticesM = numVertices;
        this->numVerticesS = numVertices;
        adjMatrix = new bool* [numVertices];

        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }

        arr = new set<int>[numVertices];
    }
    ~Graph() {
        for (int i = 0; i < numVerticesM; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;

        delete[] arr;
    }
    void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;

        arr[i].insert(j);
        arr[j].insert(i);
    }

    void toMatrix() {
        for (int i = 0; i < numVerticesM; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVerticesM; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void toSpisok() {
        for (int i = 0; i < numVerticesS; i++)
        {
            cout << endl << "Вершина: " << i << "( ";
            for (auto it = arr[i].begin(); it != arr[i].end(); it++) {
                cout << *it << ", ";
            }
            cout << ")";
        }
    }

    void RemoveM(int pos)
    {
        bool** temp = new bool* [numVerticesM - 1];
        for (int i = 0; i < numVerticesM - 1; i++) {
            temp[i] = new bool[numVerticesM - 1];
            for (int j = 0; j < numVerticesM - 1; j++)
                temp[i][j] = false;
        }
        for (int i = 0; i < pos; i++)
            for (int j = 0; j < pos; j++)
                temp[i][j] = adjMatrix[i][j];
        for (int i = pos + 1; i < numVerticesM; i++)
            for (int j = 0; j < pos; j++)
                temp[i - 1][j] = adjMatrix[i][j];

        for (int i = 0; i < numVerticesM; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        numVerticesM--;

        adjMatrix = new bool* [numVerticesM];
        for (int i = 0; i < numVerticesM; i++) {
            adjMatrix[i] = new bool[numVerticesM];
            for (int j = 0; j < numVerticesM; j++)
                adjMatrix[i][j] = false;
        }

        for (int i = 0; i < numVerticesM; i++)
            for (int j = 0; j < numVerticesM; j++)
                adjMatrix[i][j] = temp[i][j];

        for (int i = 0; i < numVerticesM; i++)
            delete[] temp[i];
        delete[] temp;
    }
    void contractEdgeM(int v1, int v2) {
        for (int i = 0; i < numVerticesM; i++) {
            if (adjMatrix[v2][i] > 0) {
                adjMatrix[v1][i] = adjMatrix[v1][i] > 0 ? min(adjMatrix[v1][i], adjMatrix[v2][i]) : adjMatrix[v2][i];
                adjMatrix[v2][i] = 0;
            }
            if (adjMatrix[i][v2] > 0) {
                adjMatrix[i][v1] = adjMatrix[i][v1] > 0 ? min(adjMatrix[i][v1], adjMatrix[i][v2]) : adjMatrix[i][v2];
                adjMatrix[i][v2] = 0;
            }
            adjMatrix[v1][v2] = adjMatrix[v2][v1] = 0;
        }
        RemoveM(v2);
        adjMatrix[v1][v1] = 1;
    }

    void RemoveS(int pos) {
        set<int>* temp = new set<int>[numVerticesS - 1];

        for (int i = 0; i < pos; i++)
            temp[i] = arr[i];
        for (int i = pos + 1; i < numVerticesS; i++)
            temp[i - 1] = arr[i];
        delete[] arr;

        numVerticesS--;
        arr = new set<int>[numVerticesS];
        for (int i = 0; i < numVerticesS; i++)
            arr[i] = temp[i];
        delete[] temp;
    }
    void contractEdgeS(int v1, int v2) {
        for (auto it = arr[v2].begin(); it != arr[v2].end(); it++)
            arr[v1].insert(*it);
        RemoveS(v2);
        arr[v1].insert(v1);
        for (int i = 0; i < numVerticesS; i++) {
            for (auto it = arr[i].begin(); it != arr[i].end(); ) {
                if (*it == v2) {
                    it = arr[i].erase(it);
                }
                else {
                    ++it;
                }
            }
        }
    }

    void addVertexM() {
        bool** temp = new bool* [numVerticesM];
        for (int i = 0; i < numVerticesM; i++) {
            temp[i] = new bool[numVerticesM];
            for (int j = 0; j < numVerticesM; j++)
                temp[i][j] = false;
        }
        for (int i = 0; i < numVerticesM; i++)
            for (int j = 0; j < numVerticesM; j++)
                temp[i][j] = adjMatrix[i][j];

        for (int i = 0; i < numVerticesM; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;

        numVerticesM++;

        adjMatrix = new bool* [numVerticesM];
        for (int i = 0; i < numVerticesM; i++) {
            adjMatrix[i] = new bool[numVerticesM];
            for (int j = 0; j < numVerticesM; j++)
                adjMatrix[i][j] = false;
        }

        for (int i = 0; i < numVerticesM - 1; i++)
            for (int j = 0; j < numVerticesM - 1; j++)
                adjMatrix[i][j] = temp[i][j];

        for (int i = 0; i < numVerticesM-1; i++)
            delete[] temp[i];
        delete[] temp;
    }
    void splittingVertexM(int v) {
        addVertexM();
        for (int i = 0; i < numVerticesM; i++)
            if (!(i & 1)) swap(adjMatrix[numVerticesM - 1][i], adjMatrix[v][i]);

        adjMatrix[v][numVerticesM - 1] = adjMatrix[numVerticesM - 1][v] = 1;
    }

    void addVertexS() {
        set<int>* temp = new set<int>[numVerticesS];
        for (int i = 0; i < numVerticesS; i++)
            temp[i] = arr[i];
        delete[] arr;

        numVerticesS++;
        arr = new set<int>[numVerticesS];
        for (int i = 0; i < numVerticesS - 1; i++)
            arr[i] = temp[i];
        delete[] temp;
    }
    void splittingVertexS(int v) {

        addVertexS();

        for (auto it = arr[v].begin(); it != arr[v].end(); ) {
            if (!(*it & 1)) {
                arr[numVerticesS - 1].insert(*it);
                it = arr[v].erase(it);
            }
            else {
                ++it;
            }
        }

        arr[v].insert(numVerticesS - 1);
        arr[numVerticesS - 1].insert(v);

    }

};

int main()
{
    srand(time(NULL));
    setlocale(0, "");
    int z = 6;
    Graph c(z);

    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < z; j++)
        {
            if (bool(rand() % 2))
                c.addEdge(i, j);
        }
    }

    cout << endl << "Матрица смежности: \n";
    c.toMatrix();
    cout << endl << "Cписок смежности: \n";
    c.toSpisok();

    cout << endl << endl << "стягивания ребра графа(Матрица)"<<endl;
    c.contractEdgeM(2, 4);
    c.toMatrix();

    //cout << endl << endl << "расщеплениe вершины графа(Матрица)"<<endl;
    //c.splittingVertexM(0);
    //c.toMatrix();

    cout << endl << "стягивания ребра графа(Список)"<<endl;
    c.contractEdgeS(2, 4);
    c.toSpisok();

    //cout << endl << "расщеплениe вершины графа(Список)";
    //c.splittingVertexS(2);
    //c.toSpisok();

    return 0;
}
