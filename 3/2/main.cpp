#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

using namespace std;

#define big_number 100000
struct edge {
    int a, b, len;
    edge(int a, int b, int len)
    {
        this->a = a;
        this->b = b;
        this->len = len;
    }
    bool operator<(const edge& other)
    {
        return len < other.len;
    }
    bool operator>(const edge& other)
    {
        return len > other.len;
    }
};

class Ostov
{
    vector<edge> data;
    int x, y;
public:
    Ostov(vector<edge> data, int x, int y)
    {
        this->x = x; this->y = y;
        for (const edge& el : data)
        {
            this->data.push_back(el);
        }
    }
    int getX() { return x; }
    int getY() { return y; }
    vector<edge> getData() { return data; }
    void print()
    {
        for (const edge& el : data)
        {
            cout << el.a << '\t' << el.b << '\t' << el.len << endl;
        }
    }
};



int p[big_number];
int rk[big_number];

void init_dsu() {
    for (int i = 0; i < big_number; i++) {
        p[i] = i;
        rk[i] = 1;
    }
}

int get_root(int v) {
    if (p[v] == v) {
        return v;
    }
    else {
        return p[v] = get_root(p[v]);
    }
}

bool merge(int a, int b) {
    int ra = get_root(a), rb = get_root(b);

    if (ra == rb) {
        return false;
    }
    else {
        if (rk[ra] < rk[rb]) {
            p[ra] = rb;
        }
        else if (rk[rb] < rk[ra]) {
            p[rb] = ra;
        }
        else {
            p[ra] = rb;
            rk[rb]++;
        }

        return true;
    }
}

vector<int> DFS(Ostov min)
{
    vector<edge> minimal = min.getData();
    vector<vector<int>> ostovMat;
    
    for (int i = 0; i < min.getY(); i++)
    {
        ostovMat.push_back(vector<int>());
    }
    
    for (vector<int>& el : ostovMat)
    {
        for (int j = 0; j < min.getX(); j++)
        {
            el.push_back(0);
        }
    }

    for (const edge& el : minimal)
    {
        ostovMat[el.a][el.b] = el.len;
        ostovMat[el.b][el.a] = el.len;
    }

    vector <int> used(min.getX(), 0);
    vector<int> re;
    stack<int> Stack;
    int iter = 0;
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty())
    {                           // пока стек не пуст
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();

        if (used[node] == 2)
            continue;
        used[node] = 2; // отмечаем ее как посещенную
        iter++;
        for (int j = 0; j < min.getX(); j++)
        { // проверяем для нее все смежные вершины
            if (ostovMat[node][j] > 0 && used[j] != 2)
            {                  // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                used[j] = 1;   // отмечаем вершину как обнаруженную
            }
        }
        re.push_back(node);
    }
    std::cout << "\nVisited vertices ";
    for (int i = 0; i < min.getX(); i++)
        std::cout << used[i] << " ";
    for (int i = 0; i < min.getX(); i++)
        used[i] = 0;

    return re;
}

Ostov ostov(vector<vector<int>> mat)
{

    auto cmp = [](edge left, edge right) { return (left) > (right); };
    std::priority_queue<edge, std::vector<edge>, decltype(cmp)> edges(cmp);
    for (int i = 0; i < mat[1].capacity(); i++)
    {
        for (int j = 0 + i; j < mat.capacity(); j++)
        {
            if (mat[i][j] > 0)
                edges.push(edge(i, j, mat[i][j]));
        }
    }
    vector<edge> minimal;

    while (!edges.empty()) {
        if (merge(edges.top().a, edges.top().b))
            minimal.push_back(edges.top());
        edges.pop();
    }
    Ostov re(minimal, mat[1].capacity(), mat.capacity());
    return re;
}

int main()
{
    vector<vector<int>> mat =
    {
        {0, 1, 2, 0, 0, 0, 0},
        {1, 0, 2, 0, 0, 0, 0},
        {2, 2, 0, 4, 0, 0, 1},
        {0, 0, 4, 0, 1, 2, 2},
        {0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 2, 1, 0, 0},
        {0, 0, 1, 2, 0, 0, 0}
    };

    init_dsu();

    Ostov minimal = ostov(mat);

    minimal.print();

    vector<int> dfs = DFS(minimal);
    
    cout << endl << endl;
    for (int el : dfs)
    {
        cout << el << '\t';
    }

    return 0;
}