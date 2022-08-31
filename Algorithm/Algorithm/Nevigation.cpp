#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int r[7][7] =
{
	{INT_MAX, 7, INT_MAX, INT_MAX, 3, 10, INT_MAX },
	{7, INT_MAX, 4, 10, 2, 6, INT_MAX },
	{INT_MAX, 4, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX },
	{INT_MAX, 10, 2, INT_MAX, INT_MAX, 9, 4 },
	{3, 2, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 5 },
	{10, 6, INT_MAX, 9, INT_MAX, INT_MAX, INT_MAX },
	{INT_MAX, INT_MAX, INT_MAX, 4, 5, INT_MAX, INT_MAX }
};

struct Road
{
	int before;
	int next;
	int cost;
	vector<int> route;
	Road(int b, int n, int c, vector<int> r) : before(b), next(n), cost(c) , route(r){}

	bool operator<(const Road r) const {
		return this->cost > r.cost;
	}
};

int cost[7] =
{
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX
};

int visited[7] = { 0, };
vector<int> answer;
void FindRoad(int s, int d)
{
	cost[s] = 0;

	priority_queue<Road> pq;
	
	visited[s] = 1;
	vector<int> route;
	route.push_back(s);
	for (int i = 0; i < 7; i++)
	{
		if (r[s][i] != INT_MAX)
		{
			pq.push(Road(s, i, r[s][i], route));
			cost[i] = r[s][i];
		}
	}

	while (!pq.empty())
	{
		Road rd = pq.top(); pq.pop();
		visited[rd.next] = 1;
		vector<int> rt = rd.route;
		rt.push_back(rd.next);

		for (int i = 0; i < 7; i++)
		{
			if (r[rd.next][i] != INT_MAX && !visited[i])
			{
				pq.push(Road(rd.next, i, rd.cost + r[rd.next][i], rt));
				
				if (cost[i] > rd.cost + r[rd.next][i])
				{
					cost[i] = rd.cost + r[rd.next][i];
					if (i == d)
					{
						rt.push_back(d);
						answer = rt;
					}
				}
			}
		}
	}

	for (auto a : answer)
	{
		cout << a << " ";
	}
	cout << endl;
}


int main()
{
	int s, d;
	cin >> s >> d;

	FindRoad(s, d);
	
	while (true);
	return 0;
}