#include <iostream>
#include <map>
#include <set>
using namespace std;

// 배열, 연결리스트 선형구조

// 트리 비선형구조

class Coord
{
	int x;
	int y;
};

struct TreeNode
{
	int		  value;
	TreeNode* Lchild = nullptr;
	TreeNode* Rchild = nullptr;
	void Print()
	{
		cout << value << "->";
		if (Lchild)
			Lchild->Print();
		if (Rchild)
			Rchild->Print();
	}
};

class Tree
{
private:
	TreeNode* Root = nullptr;
	
public:
	void PrintAll()
	{
		if (Root)
			Root->Print();
	}
};

int main()
{
	map<Coord, int> a;
	set<Coord> b;

	

	return 0;
}