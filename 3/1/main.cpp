#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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

    init_dsu();

    vector<edge> minimal;

    while (!edges.empty()) {
        if (merge(edges.top().a, edges.top().b))
            minimal.push_back(edges.top());
        edges.pop();
    }

    for (const edge& el : minimal)
    {
        cout << el.a << '\t' << el.b << '\t' << el.len << endl;
    }

    return 0;
}