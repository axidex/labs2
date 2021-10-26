#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
vector<vector<int>> ostov (const vector<vector<int>> &vec) 
{
    for (int i = 0; i < vec[1].capacity(); i++)
    {
        for (int j = 0; j < vec.capacity(); j++)
        {
            int b = vec[i][j];
        }
    }
}
int main()
{
    // матрица смежности
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
    vector<vector<int>> zxc;
    vector<int> used(7, 0);
    //0 – вершина не посещена при поиске, 1 – помещена в структуру данных для вершин,
    //но не обработана, 2 – обработана, смежные вершины помещены в структуру данных
    //DFS – поиск в глубину
    stack<int> Stack;
    int iter = 0;
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty())
        {                           // пока стек не пуст
            int node = Stack.top(); // извлекаем вершину
            Stack.pop();
            std::cout << "\nDFS at vertex " << node << endl;
            if (used[node] == 2)
                continue;
            used[node] = 2; // отмечаем ее как посещенную
            iter++;
            for (int j = 0; j < 7; j++)
            { // проверяем для нее все смежные вершины
                if (mat[node][j] > 0 && used[j] != 2)
                {                  // если вершина смежная и не обнаружена
                    Stack.push(j); // добавляем ее в cтек
                    used[j] = 1;   // отмечаем вершину как обнаруженную
                }
            }
            std::cout << node << endl; // выводим номер вершины
        }
    std::cout << "\nVisited vertices";
    for (int i = 0; i < 7; i++)
        std::cout << used[i] << " ";
    for (int i = 0; i < 7; i++)
        used[i] = 0;
    queue<int> Queue;
    //BFS – поиск в ширину
    Queue.push(0); //в качестве начальной вершины используем 0.
    used[0] = 2;
    vector<int> dist(7, 10000); //расстояния до вершин от 0-й в числе ребер
    dist[0] = 0;
    iter = 0;
    while (!Queue.empty())
    {
        int node = Queue.front(); //извлекаем из очереди текущую вершину
        Queue.pop();
        //Здесь должна быть обработка текущей вершины.
        std::cout << "\nBFS at vertex " << node << endl;
        if (used[node] == 2)
            continue;
        used[node] = 2;
        iter++;
        for (int j = 0; j < 7; j++)
        { // проверяем для нее все смежные вершины
            if (mat[node][j] > 0 && used[j] != 2)
            {                  // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                used[j] = 1;   // отмечаем вершину как обнаруженную
                if (dist[j] > dist[node] + 1)
                    dist[j] = dist[node] + 1;
            }
        }
    }
    std::cout << "\nVisited vertices";
    for (int i = 0; i < 7; i++)
        std::cout << used[i] << " ";
    std::cout << "\nDistances";
    for (int i = 0; i < 7; i++)
        std::cout << dist[i] << " ";
    
    return 0;
}