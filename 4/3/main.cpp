// TestGraph.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//
#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


class Edge
{
public:
	int from, to, weight;
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge& E)
	{
		from = E.from;
		to = E.to;
		weight = E.weight;
	}
	int operator<(Edge& E)
	{
		return (weight < E.weight);
	}
	friend ostream& operator<<(ostream& s, Edge& e);
};

ostream& operator<<(ostream& s, Edge& e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}

void paintgraph(vector<vector<int> >& matrix, vector<int>& visited, int curr=0)
{	
	int color_counter = 1;
    visited[curr] = color_counter;

    for(int i = 0; i < matrix.size(); ++i)
    {
        if (visited[i] != 0)
            continue;
        for (auto el : matrix[i])
        {
            if (visited[el] != 0 && matrix[el][curr] != 0)
                continue;
            visited[el] = color_counter;
        }
        color_counter++;
    }
}

int main() {

	vector<vector<int> > mat =
	{
	    { 1, 1, 1, 1, 1, 1 },
	    { 1, 1, 1, 1, 1, 1 },
	    { 1, 1, 1, 1, 1, 1 },
	    { 1, 1, 1, 1, 1, 1 },
	    { 1, 1, 1, 1, 1, 1 },
	    { 1, 1, 1, 1, 1, 1 }
	};
    vector<int> visited (mat.size(), 0);

	paintgraph(mat, visited, 0);
	std::cout << "\nColor: ";
	for (int i = 0; i < 6; i++) std::cout << " ";

	return 0;
}
