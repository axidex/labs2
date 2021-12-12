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

void paintgraph(vector<vector<int> >& matrix, vector <int>& color, int curr=0)
{
	
	set<int> neighbours;


	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();

		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < matrix.size(); next++)
			if (matrix[curr][next] >= 1 || !color[next])
			{
				if(color[next])
				{
					neighbours.insert(color[next]);
				}
				else
				{
				    q.push(next);
				}
			}

		
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
		    it=neighbours.find(color_counter);
			if(it==neighbours.end())
			{
				break;
			}
			color_counter++;
		} while (true);

		
		color[curr] = color_counter;
	}
}

int main() {

	vector<vector<int> > mat =
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

	vector<int> color(mat.size(), 0);
	paintgraph(mat, color, 0);
	std::cout << "\nColor: ";
	for (int i = 0; i < mat.size(); i++) std::cout << color[i] << " ";

	

	return 0;
}
