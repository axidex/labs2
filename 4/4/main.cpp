#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;


bool hamilton(vector<vector<int> >& mat,  vector <bool>& visited, vector <int>& path, int curr,bool flag = true) 
{
	path.push_back(curr);
	
	if(path.size()==mat.size())
	{
		
        bool re = flag ? true : (mat[curr][path[0]] > 0) ? true : false;
        if (re)
            return re;
	}

	visited[curr] = true;

	for(int i=0;i<mat.size();i++)
	{
		if (mat[curr][i]>0 && !visited[i])
		{
			if (hamilton(mat,visited,path,i,flag)) 
			{
				return true;
			}
		}
	}



	visited[curr] = false;
	path.pop_back();
	return false;
}

int main() 
{
	
	vector<vector<int> > mat=
	{
		{ 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 0 },
		{ 0, 1, 0, 1, 1, 0 },
		{ 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 0 }
	};
	vector<bool> visited(6, 0);
	vector<int> path;

	cout << "\nHamilton: " << hamilton(mat, visited, path, 0, 0);

	char c1; cin >> c1;

	char c; std::cin >> c;
	return 0;
}
