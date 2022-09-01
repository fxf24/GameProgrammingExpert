#include <iostream>
#include <map>
#include <queue>
using namespace std;

class DiNode
{
public:
	// Vector3 Pos;
	int id;
	int prev;
	map<int, float> linkedWay;
	float cost;
	bool find;
	void Reset()
	{
		prev = -1;
		cost = FLT_MAX;
		find = false;
	}
};

class DiNodeCompare
{
public:
	bool operator()(DiNode*& a, DiNode*& b)
	{
		return a->cost > b->cost;
	}
};

int main()
{
	DiNode nodes[7];
	for (int i = 0; i < 7; i++)
	{
		nodes[i].id = i;
	}

	nodes[0].linkedWay[4] = 3.0f;
	nodes[4].linkedWay[0] = 3.0f;
	nodes[0].linkedWay[1] = 7.0f;
	nodes[1].linkedWay[0] = 7.0f;
	nodes[0].linkedWay[5] = 10.0f;
	nodes[5].linkedWay[0] = 10.0f;

	nodes[4].linkedWay[1] = 2.0f;
	nodes[1].linkedWay[4] = 2.0f;
	nodes[4].linkedWay[6] = 5.0f;
	nodes[6].linkedWay[4] = 5.0f;

	nodes[6].linkedWay[3] = 4.0f;
	nodes[3].linkedWay[6] = 4.0f;

	nodes[5].linkedWay[1] = 6.0f;
	nodes[1].linkedWay[5] = 6.0f;
	nodes[5].linkedWay[3] = 9.0f;
	nodes[3].linkedWay[5] = 9.0f;

	nodes[2].linkedWay[1] = 4.0f;
	nodes[1].linkedWay[2] = 4.0f;

	nodes[3].linkedWay[1] = 10.0f;
	nodes[1].linkedWay[3] = 10.0f;
	nodes[3].linkedWay[2] = 2.0f;
	nodes[2].linkedWay[3] = 2.0f;

	while (1)
	{
		int start, end;
		cout << "출발노드:"; cin >> start;
		cout << "도착노드:"; cin >> end;

		for (int i = 0; i < 7; i++)
			nodes[i].Reset();

		nodes[start].cost = 0;

		priority_queue<DiNode*, vector<DiNode*>, DiNodeCompare> Q;

		Q.push(&nodes[start]);

		while (!Q.empty())
		{
			DiNode* top = Q.top();
			Q.pop();
			for (auto it = top->linkedWay.begin(); it != top->linkedWay.end(); it++)
			{
				if (nodes[it->first].cost > top->cost + it->second)
				{
					nodes[it->first].cost = top->cost + it->second;
					nodes[it->first].prev = top->id;
					if (not nodes[it->first].find)
					{
						Q.push(&nodes[it->first]);
						nodes[it->first].find = true;
					}
				}
			}
		}

		DiNode* iter = &nodes[end];
		while (1)
		{
			cout << iter->id << "->";
			iter = &nodes[iter->prev];
			if (iter == &nodes[start])
			{
				cout << iter->id << endl;
				break;
			}
		}
	}

}