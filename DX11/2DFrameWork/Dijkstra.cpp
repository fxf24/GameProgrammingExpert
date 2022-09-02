#include "framework.h"

void Dijkstra::AddNode(Vector3 pos)
{
	DiNode temp;
	size_t id = NodeList.size();

	//리스트 내에 비어있는 인덱스가 있는지
	for (size_t i = 0; i < NodeList.size(); i++)
	{
		// i가 없는 인덱스
		if (NodeList.find(i) == NodeList.end())
		{
			id = i;
			break;
		}
	}

	temp.id = id;
	temp.pos = pos;
	NodeList[temp.id] = temp;
}

void Dijkstra::PopNode(int id)
{
	if (NodeList.find(id) != NodeList.end())
	{
		for (auto it = NodeList[id].linkedWay.begin(); it != NodeList[id].linkedWay.end(); it++)
		{
			NodeList[it->first].linkedWay.erase(id);
		}
		NodeList.erase(id);
	}
}


void Dijkstra::LinkNode(int id1, int id2)
{
	Vector3 Dis = NodeList[id1].pos - NodeList[id2].pos;

	NodeList[id1].linkedWay[id2] = Dis.Length();
	NodeList[id2].linkedWay[id1] = Dis.Length();
}

int Dijkstra::PickNode(Vector3 pos)
{
	int id = 0;
	float min = FLT_MAX;
	for (auto it = NodeList.begin(); it != NodeList.end(); it++)
	{
		Vector3 dis = it->second.pos - pos;
		if (min > dis.Length())
		{
			min = dis.Length();
			id = it->first;
		}
	}
	return id;
}

bool Dijkstra::PathFinding(vector<Vector3>& Way, int Start, int End)
{
	if (NodeList.find(Start) == NodeList.end() || NodeList.find(End) == NodeList.end())
		return false;
	for (auto it = NodeList.begin(); it != NodeList.end(); it++)
		it->second.Reset();
	NodeList[Start].cost = 0;

	priority_queue<DiNode*, vector<DiNode*>, DiNodeCompare> Q;

	Q.push(&NodeList[Start]);

	while (!Q.empty())
	{
		DiNode* top = Q.top();
		Q.pop();
		for (auto it = top->linkedWay.begin(); it != top->linkedWay.end(); it++)
		{
			if (NodeList[it->first].cost > top->cost + it->second)
			{
				NodeList[it->first].cost = top->cost + it->second;
				NodeList[it->first].prev = top->id;
				if (not NodeList[it->first].find)
				{
					Q.push(&NodeList[it->first]);
					NodeList[it->first].find = true;
				}
			}
		}
	}
	Way.clear();

	DiNode* iter = &NodeList[End];
	while (1)
	{
		Way.push_back(iter->pos);
		iter = &NodeList[iter->prev];
		if (iter == &NodeList[Start])
		{
			cout << iter->id << endl;
			break;
		}
	}

	return true;
}
