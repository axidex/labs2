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
    friend ostream& operator<<(ostream& os, const edge& e)
    {
        os <<  e.a << '\t' << e.b << '\t' << e.len ;
        return os;
    }
};

int p[big_number]; // множество вершин изначально
int rk[big_number]; // глубина вершин относительно корня

void init_dsu() {       // Система непересекающихся множеств P[] - корни. Каждая вершина изначально является корнем
    for (int i = 0; i < big_number; i++) {
        p[i] = i;  // Каждая вершина изначально является корнем
        rk[i] = 1; //Глубина каждой вершины в дереве
    }
}

// Пусть нам нужно объединить множества с корнями a и b. Просто присвоим p[a]=b, тем самым подвесив всё дерево a к корню дерева b

int get_root(int v) { // геттер корня вершины
    if (p[v] == v) {
        return v; // Ретерним корень если нашли
    }
    else {
        return p[v] = get_root(p[v]); // переподвешиваю вершины на прямую к корню 
    }
}   
                                
bool merge(int a, int b) {      // возвращаемое значение обозначает, находились ли до вызова функции a и b в разных деревьях
    int ra = get_root(a), rb = get_root(b);     // a и b - любые вершины в деревьях

    if (ra == rb) { // проверка на один и тот же корень
        return false;
    }
    else {
        if (rk[ra] < rk[rb]) { // при объединении подвешивать дерево с меньшей глубиной к корню дерева с большей глубиной
            p[ra] = rb; // если глубина ra меньше rb
        }
        else if (rk[rb] < rk[ra]) {
            p[rb] = ra; //если глубина rb меньше ra
        }
        else {               // Если оба дерева имеют одинаковую глубину, неважно, какое из них подвешивать
            p[ra] = rb; // Если не важно какое делаю как в 1 случае(могу и как во 2ом)
            rk[rb]++;   //  При одинаковой глубине глубина нового дерева увеличивается на 1
        }

        return true;
    }
}
vector<edge> ostov(vector<vector<int>> mat) // минимальный остов - это дерево графа, которое имеет минимальную сумму весов входящих в него ребер и при этом имеет пути во все его вершины
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
        if (merge(edges.top().a, edges.top().b)) // беру первую грань и проверяю, на принадлежность их к разным деревьям в первом случае всегда будет true 
                                                // т.к. изначально все вершины в разнхы деревьях
            minimal.push_back(edges.top()); // если условие выполнилось то заносим вершину в наш минимальный остов
                                            // условие нарушится в том случае если несколько вершин будут вести в одну точку(вершину) и именно тогда будет остов не минимальным
        edges.pop(); // итерируемся по граням
    }
    return minimal;
}
template<class T>
void print(const vector<T> minimal)
{
    for (const T& el : minimal)
    {
        cout << el << endl;
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

    init_dsu();

    vector<edge> minimal = ostov(mat);

    

    return 0;
}