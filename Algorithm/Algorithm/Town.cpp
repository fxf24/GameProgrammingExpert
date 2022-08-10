#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


class Answer
{
public:
	int answer(ifstream& fin)
	{
		int answer = 1;

		vector<vector<int>> v(60001, vector<int>(0,0));
		int visited[60001] = { 0, };
		while (!fin.eof())
		{
			int num;
			fin >> num;

			for (int i = 0; i < num; i++)
			{
				int n;
				fin >> n;
				int m;
				fin >> m;
				for (int j = 0; j < m; j++)
				{
					int k;
					fin >> k;
					v[n].push_back(k);
					//cout << v[n][j] << " ";
				}
				//cout << endl;
			}
		}
		fin.close();

		queue<pair<int, int>> q;
		for (int i = 0; i < v[1].size(); i++)
		{
			q.push( make_pair(1, v[1][i]));
			visited[v[1][i]] = 1;
		}
		visited[1] = 1;
		while (!q.empty())
		{
			pair<int, int> p = q.front();
			q.pop();
			answer++;

			for (int i = 0; i < v[p.second].size(); i++)
			{
				if (!visited[v[p.second][i]])
				{
					q.push(make_pair(p.second, v[p.second][i]));
					visited[v[p.second][i]] = 1;
				}
			}
		}

		return answer;
	}
};
int main()
{
	Answer a;
	ifstream fin1;
	fin1.open("./마을1.txt");

	if (fin1.fail())
	{
		cout << "error : fin1" << endl;
	}

	ifstream fin2;
	fin2.open("./마을2.txt");
	if (fin2.fail())
	{
		cout << "error : fin2" << endl;
	}

	int answer1 = a.answer(fin1);
	int answer2 = a.answer(fin2);

	cout << answer1 << endl;
	cout << answer2 << endl;

	while (true)
	{
	}
	return 0;
}