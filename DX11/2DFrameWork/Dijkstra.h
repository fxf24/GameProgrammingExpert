#pragma once

class DiNode
{
public:
	Vector3			pos;
	int				id;
	int				prev;
	map<int, float> linkedWay;
	float			cost;
	bool			find;
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

class Dijkstra
{
	//����� �Ÿ��θ� ���
public:
	unordered_map<int, DiNode> NodeList;
	
public:
	void AddNode(Vector3 pos);
	void PopNode(int id);
	void LinkNode(int id1, int id2);
	// ���� ������� ��ȯ
	int PickNode(Vector3 pos);
	bool PathFinding(vector<Vector3>& Way, int Start, int End);
};

