#include <iostream>
#include <map>
#include <set>
using namespace std;

// �迭, ���Ḯ��Ʈ ��������

// Ʈ�� ��������

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
	TreeNode* Parent = nullptr;

	void Push(TreeNode* child)
	{
		if (child->value > value)
		{
			if (Rchild) Rchild->Push(child);
			else
			{
				Rchild = child;
				child->Parent = this;
			}
		}
		else if (child->value < value)
		{
			if (Lchild) Lchild->Push(child);
			else
			{
				Lchild = child;
				child->Parent = this;
			}
		}
	}

	TreeNode* Find(int data)
	{
		if (data == value) return this;
		else if (data > value)
		{
			if (!Rchild)
				Rchild->Find(data);
		}
		else if (data < value)
		{
			if (!Lchild)
				Lchild->Find(data);
		}

		return nullptr;
	}

	void PreOrder()
	{
		cout << value << "->";
		if (Lchild)
			Lchild->PreOrder();
		if (Rchild)
			Rchild->PreOrder();
	}
	void InOrder()
	{
		if (Lchild)
			Lchild->InOrder();
		cout << value << "->";
		if (Rchild)
			Rchild->InOrder();

	}
	void PostOrder()
	{
		if (Lchild)
			Lchild->PostOrder();
		if (Rchild)
			Rchild->PostOrder();
		cout << value << "->";
	}
};

class Tree
{
private:
	TreeNode* Root = nullptr;
	
public: 
	void Push(int data)
	{
		TreeNode* temp = new TreeNode();
		temp->value = data;
		if (!Root)
		{
			Root = temp;
		}
		else
		{
			Root->Push(temp);
		}
	}

	void Pop(int data)
	{
		TreeNode* iter = Root->Find(data);

		if (iter->Rchild && iter->Lchild)
		{
			if (iter->Parent->value > iter->value)
			{
				iter->Parent->Lchild = iter->Lchild;
				iter->Lchild->Parent = iter->Parent;
				iter->Lchild->Rchild = iter->Rchild;
				iter->Rchild->Parent = iter->Lchild;
				delete iter;
			}
			else if (iter->Parent->value < iter->value)
			{
				iter->Parent->Rchild = iter->Rchild;
				iter->Rchild->Parent = iter->Parent;
				iter->Rchild->Lchild = iter->Lchild;
				iter->Lchild->Parent = iter->Rchild;
				delete iter;
			}
		}
		else if (iter->Rchild)
		{
			if (iter->Parent->value > iter->value)
			{
				
				delete iter;
			}
			else if (iter->Parent->value < iter->value)
			{

				delete iter;
			}
		}
	}

public:
	void PrePrint()
	{
		if (Root)
			Root->PreOrder();
	}
	void InPrint()
	{
		if (Root)
			Root->InOrder();
	}
	void PostPrint()
	{
		if (Root)
			Root->PostOrder();
	}
};

int main()
{
	Tree a;

	while (1)
	{
		cout << "����:"; a.PrePrint(); cout << endl;
		cout << "����:"; a.InPrint(); cout << endl;
		cout << "����:"; a.PostPrint(); cout << endl;

		int Select;
		cout << "1. ���� 2. ����" << endl;
		cin >> Select;

		if (Select == 1)
		{
			int input;
			cout << "������ �����͸� �Է����ּ���:";
			cin >> input;
			a.Push(input);
		}
		else if (Select == 2)
		{
			int input;
			cout << "������ �����͸� �Է����ּ��� : ";
			cin >> input;
			a.Pop(input);
		}
	}

	return 0;
}