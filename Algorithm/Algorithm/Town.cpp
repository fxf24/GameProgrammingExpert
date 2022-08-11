#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
#include <string>
using namespace std;


class Answer
{
public:
	int answer(string name)
	{
		ifstream fin;
		fin.open(name);

		int answer = 1;

		vector<vector<int>> v(60001, vector<int>(0,0));
		int visited[60001] = { 0, };

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

	int answer1 = a.answer("./마을1.txt");
	chrono::system_clock::time_point start = std::chrono::system_clock::now();
	int answer2 = a.answer("./마을2.txt");

	cout << answer1 << endl;
	cout << answer2 << endl;
	chrono::duration<double>sec = std::chrono::system_clock::now() - start;
	cout << sec.count() << "seconds"<< endl;

	while (true)
	{
	}
	return 0;
}