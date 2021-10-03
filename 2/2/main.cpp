#include <iostream>
#include <queue>

using namespace std;

template <typename T>
void print_queue(T &q)
{
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}
int main()
{
    pair <string,int> book1("Book1", 4);
    pair <string,int> book2("Book1", 3);
    pair <string,int> book3("Book1", 5);
    pair <string,int> book4("Book1", 1);
    pair <string,int> book5("Book1", 8);

    vector<pair<string,int>> data;
    data.push_back(book1);
    data.push_back(book2);
    data.push_back(book3);
    data.push_back(book4);
    data.push_back(book5);

    auto cmp = [](int left, int right) { return (left ) < (right ); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);

    for(pair<string,int> n : data)
        q3.push(n.second);
    
    print_queue(q3);
}