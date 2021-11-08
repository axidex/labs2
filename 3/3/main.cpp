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
    friend ostream& operator<<(ostream& os, Ostov ost)
    {
        for (const edge& el : ost.getData())
        {
            os << el.a << '\t' << el.b << '\t' << el.len << endl;
        }
        return os;
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

vector<vector<int>> toMat(Ostov min)
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
    return ostovMat;
}

vector<int> Dijkstra(int entry, const vector<vector<int>>& mat)
{
    if (mat[0].capacity() < mat[0].size()) return vector<int>(mat[0].size(), -1);
    int size = mat[0].size();
    vector<int> distances(size, big_number);
    distances[entry] = 0;
    vector<int> used(size, 0);
    auto cmp = [](edge left, edge right) { return (left) > (right); };
    std::priority_queue<edge, std::vector<edge>, decltype(cmp)> q(cmp);

    for (int i = 0; i < size; ++i)
    {
        if (mat[entry][i] != 0)
        {
            q.push(edge(entry, i, mat[entry][i]));
            distances[i] = mat[entry][i];
            used[entry] = 2;
        }
    }
    while (!q.empty())
    {
        edge tmp = q.top();
        q.pop();
        int num = tmp.b;

        for (int i = 0; i < size; ++i)
        {
            if (mat[num][i] != 0 && distances[num] + mat[num][i] < distances[i])
            {
                if (used[i] != 2)
                    q.push(edge(num, i, mat[num][i]));
                distances[i] = distances[num] + mat[num][i];
            }
        }
        used[num] = 2;
    }
    return distances;

}

int main()
{
    vector<vector<int>> mat =
    {
        { 0, 6, 5, 6, 7, 5, 8, 8, 2 },
        { 6, 0, 2, 5, 1, 4, 4, 3, 2 },
        { 5, 2, 0, 0, 6, 7, 5, 4, 2 },
        { 6, 5, 0, 0, 2, 4, 1, 7, 4 },
        { 7, 1, 6, 2, 0, 8, 0, 9, 5 },
        { 5, 4, 7, 4, 8, 0, 9, 8, 0 },
        { 8, 4, 5, 1, 0, 9, 0, 7, 5 },
        { 8, 3, 4, 7, 9, 8, 7, 0, 7 },
        { 2, 2, 2, 4, 5, 0, 5, 7, 0 },
    };

    init_dsu();

    Ostov minimal = ostov(mat);

    minimal.print();

    vector<vector<int>> ostovMat = toMat(minimal);

    cout << endl << endl;
    for (auto ve : ostovMat)
    {
        for (auto el : ve)
        {
            cout << el << '\t';
        }
        cout << endl;
    }
    cout << endl << endl << endl;
    vector<int> paths = Dijkstra(4, ostovMat);

    for (int el : paths)
    {
        cout << el << "\t";
    }

    return 0;
}