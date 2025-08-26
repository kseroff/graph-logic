#include <iostream>

using namespace std;


#include <iostream>
#include <list>
#include <queue>
using namespace std;

template<typename T>
class MyList {
public:
    class Iterator;
    MyList() : size(0), head(nullptr), tail(nullptr) {}
    ~MyList() { while (head != nullptr) pop_front(); }

    T GetSize() { return size; }
    T GetHead() { return head->data; }
    T GetTail() { return tail->data; }
    bool isEmpty() { return(head == nullptr); }
    void push_back(T data);
    void pop_front();
    void pop_back();
    T& operator[](const T index);
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }


private:

    template<typename T>
    struct Node {
        T data;
        Node* next;
        Node* pred;

        Node(T data = T(), Node* pNext = nullptr, Node* pPred = nullptr) {
            this->data = data;
            this->next = pNext;
            this->pred = pPred;
        }
    };
    int size;
    Node<T>* head;
    Node<T>* tail;
};
template<typename T>
class MyList<T>::Iterator
{
    Node<T>* ptr;
public:

    Iterator() : ptr(nullptr) {};
    Iterator(Node<T>* p) : ptr(p) {}
    Iterator& operator ++ ()
    {
        if (ptr)
        {
            ptr = ptr->next; //Может быть еще и здесь кинуть исключение
            return *this;
        }
    }
    Iterator& operator -- ()
    {
        if (ptr)
        {
            ptr = ptr->pred;
            return *this;
        }
        else
        {
            ptr = tail;
            return *this;
        }
    }
    T& operator * ()
    {
        if (ptr)
            return ptr->data;

    }
    bool operator != (const Iterator& it) { return ptr != it.ptr; }
    bool operator == (const Iterator& it) { return ptr == it.ptr; }
};
template<typename T>
void MyList<T>::push_back(T data)
{
    Node<T>* temp = new Node<T>(data);
    temp->next = 0;
    temp->data = data;
    temp->pred = tail;

    if (tail != nullptr)
        tail->next = temp;

    if (size == 0) {
        head = tail = temp;
    }
    else {
        tail = temp;
    }
    size++;
}
template<typename T>
void MyList<T>::pop_front()
{
    Node<T>* temp = head;
    head = head->next;
    delete temp;
    size--;
    (size == 0) ? head = tail = nullptr : head->pred = nullptr;
}
template<typename T>
void MyList<T>::pop_back()
{
    Node<T>* temp = tail;
    tail = tail->pred;
    delete temp;
    size--;
    (size == 0) ? head = tail = nullptr : tail->next = nullptr;
}
template<typename T>
T& MyList<T>::operator[](const T index)
{
    int counter_1 = 0, counter_2 = size;
    Node<T>* current_1 = this->head;
    Node<T>* current_2 = this->tail;
    while (current_1 != nullptr || current_2 != nullptr)
    {
        if (counter_1 == index)
            return current_1->data;
        if (counter_2 == index + 1)
            return current_2->data;

        current_1 = current_1->next;
        current_2 = current_2->pred;
        counter_2--;
        counter_1++;
    }
}


class Graph {
private:
    bool* visited;
    bool* visit;
    bool* v;
    /////////////////
    bool** adjMatrix;
    MyList<int>* adjLists;
    int numVertices;

public:

    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adjMatrix = new bool* [numVertices];
        visited = new bool[numVertices];

        adjLists = new MyList<int>[numVertices];
        visit = new bool[numVertices];

        v = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            visited[i] = false;
            visit[i] = false;
            v[i] = false;
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }
    }
    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[]visited;
        delete[]visit;
        delete[]v;
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
    void addEdge(int i, int j) {
        adjMatrix[i][j] = adjMatrix[j][i] = true;

        adjLists[i].push_back(j);
        adjLists[j].push_back(i);
    }

    void BFS_S(int start, int dest);
    void BFS(int start);
    void DFS_S(int st);
    void DFS(int v);

};
void Graph::BFS_S(int start, int dest)
{
    int* dist = new int[numVertices];
    int* pred = new int[numVertices];
    list<int> queue;

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;
    queue.push_back(start);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adjLists[u].GetSize(); i++) {
            if (visited[adjLists[u][i]] == false) {
                visited[adjLists[u][i]] = true;
                dist[adjLists[u][i]] = dist[u]++;
                pred[adjLists[u][i]] = u;
                queue.push_back(adjLists[u][i]);


                if (adjLists[u][i] == dest) {
                    
                    MyList<int> path;
                    path.push_back(dest);
                    cout << "\nПуть: ";
                    while (pred[dest] != -1) {
                        cout << pred[dest] << " ";
                        //path.push_back(pred[dest]);
                        dest = pred[dest];
                    }

                    //cout << "\nПуть: ";
                    //for (int i = path.GetSize() - 1; i >= 0; i--)
                    //    cout << path[i] << " ";


                    delete[]dist;
                    delete[]pred;
                    return;
                }
            }
        }
    }
    delete[]dist;
    delete[]pred;
}

void Graph::BFS(int start)
{
    MyList <int> q;
    q.push_back(start);
    visit[start] = true;

    while (!q.isEmpty()) {
        start = q.GetHead();
        cout << start << " ";
        q.pop_front();

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[start][i] == 1 && (!visit[i])) {
                q.push_back(i);
                visit[i] = true;
            }
        }
    }
}

void Graph::DFS_S(int start)
{
    visit[start] = true;
    cout << start << " ";

    for (auto i : adjLists[start])
        if (!visit[i])
            DFS(i);
}

void Graph::DFS(int start)
{
    visited[start] = true;
    cout << start << " ";

    for (int i = 0; i <= numVertices; i++)
        if ((adjMatrix[start][i] != 0) && (!visited[i]))
            DFS_S(i);
}

int main()
{
    setlocale(0, "");
    srand(time(0));

    int z = 7;
    Graph c(z);

    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < z; j++)
        {
            if (bool(rand() % 2))
                c.addEdge(i, j);
        }
    }
    cout << "Матрица смежности" << endl;
    c.toMatrix();
    int start, dest;

    cout << endl << "Стартовая вершина > "; cin >> start;
    cout << endl << "Конечная вершина > "; cin >> dest;

    cout << "Путь: " << endl;
    c.BFS_S(start,dest);


    return 0;
}

