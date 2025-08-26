#include <iostream>
using namespace std;

class Graph {
private:

    bool** adjMatrix;
    int numVertices;

public:

    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adjMatrix = new bool* [numVertices];

        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }

    }
    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }

    void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }
    void toMatrix() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    bool** GetMatrix() { return adjMatrix; }
    int GetSize() { return numVertices; }
};

void UnionGraph(bool** Matrix1, int size1, bool** Matrix2, int size2) {
    int maxsize, minsize;
    if (size1 >= size2) {
        maxsize = size1;
        minsize = size2;
    }
    else {
        maxsize = size2;
        minsize = size1;
    }

    bool** MaxMatrix = new bool* [maxsize];
    for (int i = 0; i < maxsize; i++) {
        MaxMatrix[i] = new bool[maxsize];
        for (int j = 0; j < maxsize; j++)
            MaxMatrix[i][j] = false;
    }
    bool** MinMatrix = new bool* [minsize];
    for (int i = 0; i < minsize; i++) {
        MinMatrix[i] = new bool[minsize];
        for (int j = 0; j < minsize; j++)
            MinMatrix[i][j] = false;
    }

    if (size1 >= size2) {
        MaxMatrix = Matrix1;
        MinMatrix = Matrix2;
    }
    else {
        MaxMatrix = Matrix2;
        MinMatrix = Matrix1;
    }

    for (int i = 0; i < minsize; i++)
    {
        for (int j = 0; j < minsize; j++)
        {
            MaxMatrix[i][j] = MaxMatrix[i][j] + MinMatrix[i][j];
        }
    }
    for (int i = 0; i < maxsize; i++) {
        cout << i << " : ";
        for (int j = 0; j < maxsize; j++) {
            cout << MaxMatrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < maxsize; i++)
        delete[] MaxMatrix[i];
    delete[] MaxMatrix;
    for (int i = 0; i < minsize; i++)
        delete[] MinMatrix[i];
    delete[] MinMatrix;
}
void IntersectionCraph(bool** Matrix1, int size1, bool** Matrix2, int size2) {
    int maxsize, minsize;
    if (size1 >= size2) {
        maxsize = size1;
        minsize = size2;
    }
    else {
        maxsize = size2;
        minsize = size1;
    }

    bool** MaxMatrix = new bool* [maxsize];
    for (int i = 0; i < maxsize; i++) {
        MaxMatrix[i] = new bool[maxsize];
        for (int j = 0; j < maxsize; j++)
            MaxMatrix[i][j] = false;
    }
    bool** MinMatrix = new bool* [minsize];
    for (int i = 0; i < minsize; i++) {
        MinMatrix[i] = new bool[minsize];
        for (int j = 0; j < minsize; j++)
            MinMatrix[i][j] = false;
    }

    if (size1 >= size2) {
        MaxMatrix = Matrix1;
        MinMatrix = Matrix2;
    }
    else {
        MaxMatrix = Matrix2;
        MinMatrix = Matrix1;
    }

    for (int i = 0; i < minsize; i++)
        for (int j = 0; j < minsize; j++)
            MinMatrix[i][j] = (MinMatrix[i][j] == 1 && MaxMatrix[i][j] == 1) ? 1 : 0;


    for (int i = 0; i < minsize; i++) {
        cout << i << " : ";
        for (int j = 0; j < minsize; j++) {
            cout << MinMatrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < maxsize; i++)
        delete[] MaxMatrix[i];
    delete[] MaxMatrix;
    for (int i = 0; i < minsize; i++)
        delete[] MinMatrix[i];
    delete[] MinMatrix;
}
void RingSumGraph(bool** Matrix1, int size1, bool** Matrix2, int size2) {
    int maxsize, minsize;
    if (size1 >= size2) {
        maxsize = size1;
        minsize = size2;
    }
    else {
        maxsize = size2;
        minsize = size1;
    }

    bool** MaxMatrix = new bool* [maxsize];
    for (int i = 0; i < maxsize; i++) {
        MaxMatrix[i] = new bool[maxsize];
        for (int j = 0; j < maxsize; j++)
            MaxMatrix[i][j] = false;
    }
    bool** MinMatrix = new bool* [minsize];
    for (int i = 0; i < minsize; i++) {
        MinMatrix[i] = new bool[minsize];
        for (int j = 0; j < minsize; j++)
            MinMatrix[i][j] = false;
    }

    if (size1 >= size2) {
        MaxMatrix = Matrix1;
        MinMatrix = Matrix2;
    }
    else {
        MaxMatrix = Matrix2;
        MinMatrix = Matrix1;
    }

    for (int i = 0; i < minsize; i++)
        for (int j = 0; j < minsize; j++)
            MaxMatrix[i][j] = ((MinMatrix[i][j] == 1 && MaxMatrix[i][j] == 1) || (MinMatrix[i][j] == 0 && MaxMatrix[i][j] == 0)) ? 0 : 1;

    for (int i = 0; i < maxsize; i++)
    {
        MaxMatrix[maxsize - 1][i] = 0;
        MaxMatrix[i][maxsize - 1] = 0;
    }

    for (int i = 0; i < maxsize; i++) {
        cout << i << " : ";
        for (int j = 0; j < maxsize; j++) {
            cout << MaxMatrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < maxsize; i++)
        delete[] MaxMatrix[i];
    delete[] MaxMatrix;
    for (int i = 0; i < minsize; i++)
        delete[] MinMatrix[i];
    delete[] MinMatrix;
}
void CartesianProduct(bool** Matrix1, int size1, bool** Matrix2, int size2) {

    bool** Matrix = new bool* [size1 * size2];
    for (int i = 0; i < size1 * size2; i++) {
        Matrix[i] = new bool[size1 * size2];
        for (int j = 0; j < size1 * size2; j++) {
            Matrix[i][j] = false;
        }
    }

    int a = 0, b = 0;
    for (int i = 0; i < size1; i++) {
        for (int k = 0; k < size2; k++) {
            b = 0;
            for (int j = 0; j < size1; j++) {
                for (int l = 0; l < size2; l++) {

                    if (i == j)
                        Matrix[a][b] = Matrix2[k][l];
                    if (k == l)
                        Matrix[a][b] = Matrix1[i][j];
                    if (i != j && k != l)
                        Matrix[a][b] = 0;
                    b++;
                }
            }
            a++;
        }
    }

    for (int i = 0; i < size1 * size2; i++) {
        cout << i << " : ";
        for (int j = 0; j < size1 * size2; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < size1 * size2; i++) {
        delete[] Matrix[i];
    }
    delete[] Matrix;
}

int main(void)
{
    srand(time(NULL));
    setlocale(0, "");
    int z = 6, x = 5;
    Graph c1(z);
    Graph c2(x);

    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < z; j++)
        {
            if (bool(rand() % 2))
                c1.addEdge(i, j);
        }
    }
    for (int i = 0; i < x; i++)
    {
        for (int j = i + 1; j < x; j++)
        {
            if (bool(rand() % 2))
                c2.addEdge(i, j);
        }
    }


    cout << endl << "Матрица смежности(1): \n";
    c1.toMatrix();
    cout << endl << "Матрица смежности(1): \n";
    c2.toMatrix();

    cout << endl << "Объединение графов"<<endl;
    UnionGraph(c1.GetMatrix(), c1.GetSize(), c2.GetMatrix(), c2.GetSize());

    //cout << endl << "Пересечение графов" << endl;
    //IntersectionCraph(c1.GetMatrix(), c1.GetSize(), c2.GetMatrix(), c2.GetSize());

    //cout << endl << "Кольцевая сумма графов" << endl;
    //RingSumGraph(c1.GetMatrix(), c1.GetSize(), c2.GetMatrix(), c2.GetSize());

    //cout << endl << "Декартово произведение графов графов" << endl;
    //CartesianProduct(c1.GetMatrix(), c1.GetSize(), c2.GetMatrix(), c2.GetSize());

    cin.get();
    return 0;
}

