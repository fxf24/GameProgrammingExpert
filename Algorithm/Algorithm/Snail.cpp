#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n, m;

	cin >> n >> m;

	vector<vector<int>> v(n, vector<int>(m, 0));

	int i = 0;
	int j = 0; 
	int num = 1;

	vector<pair<int, int>> dir = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};

	int dirI = 0;
	int max = n * m;
	while (true)
	{
		v[i][j] = num;
		num++;
		
		switch (dirI)
		{
		case 0:
			if (j + 1 < m && v[i][j + 1] == 0)
				j += dir[dirI].second;
			else
			{
				dirI++;
				i += dir[dirI].first;
			}
			break;
		case 1:
			if (i + 1 < n && v[i + 1][j] == 0)
				i += dir[dirI].first;
			else
			{
				dirI++;
				j += dir[dirI].second;
			}
			break;
		case 2:
			if (j - 1 >= 0 && v[i][j - 1] == 0)
				j += dir[dirI].second;
			else
			{
				dirI++;
				i += dir[dirI].first;
			}
			break;
		case 3:
			if (i - 1 >= 0 && v[i-1][j] == 0)
				i += dir[dirI].first;
			else
			{
				dirI = 0;
				j += dir[dirI].second;
			}
			break;
		}

		if (num > max)
		{
			break;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << v[i][j] << "\t";
		}
		cout << endl;
	}

	while (true)
	{

	}
	return 0;
}