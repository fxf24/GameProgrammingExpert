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
		if (data == value)
		{
			return this;
		}
		else if (data > value)
		{
			if (Rchild)
			{
				return Rchild->Find(data);
			}
		}
		else if (data < value)
		{
			if (Lchild)
			{
				return Lchild->Find(data);
			}
		}

		return nullptr;
	}

	TreeNode* LowestRightSubNode()
	{
		TreeNode* iter = Rchild;

		while (1)
		{
			if (iter->Lchild)
				iter = iter->Lchild;
			else
			{
				if (iter->Parent->value > iter->value)
					iter->Parent->Lchild = nullptr;
				else if (iter->Parent->value < iter->value)
					iter->Parent->Rchild = nullptr;

				return iter;
			}
		}
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

		if (!iter)
		{
			cout << "�������� �ʴ� ��� �Դϴ�" << endl;
			return;
		}
		
		if (iter == Root)
		{
			TreeNode* LRSN = iter->LowestRightSubNode();
			if (LRSN)
			{
				LRSN->Lchild = iter->Lchild;
				if (iter->Lchild)
					iter->Lchild->Parent = LRSN;
				LRSN->Parent = iter->Parent;
				LRSN->Rchild = iter->Rchild;
				if (iter->Rchild)
					iter->Rchild->Parent = LRSN;
			}
			Root = LRSN;
			delete iter;
		}
		else if (!iter->Rchild && !iter->Lchild)
		{
			if (iter->Parent->value > iter->value)
			{
				iter->Parent->Lchild = nullptr;
				delete iter;
			}
			else if (iter->Parent->value < iter->value)
			{
				iter->Parent->Rchild = nullptr;
				delete iter;
			}
		}
		else if (iter->Rchild && iter->Lchild)
		{
			if (iter->Parent->value > iter->value)
			{
				TreeNode* LRSN = iter->LowestRightSubNode();
				iter->Parent->Lchild = LRSN;
				LRSN->Lchild = iter->Lchild;
				if (iter->Lchild)
					iter->Lchild->Parent = LRSN;
				LRSN->Parent = iter->Parent;
				LRSN->Rchild = iter->Rchild;
				if (iter->Rchild)
					iter->Rchild->Parent = LRSN;
				delete iter;
			}
			else if (iter->Parent->value < iter->value)
			{
				TreeNode* LRSN = iter->LowestRightSubNode();
				iter->Parent->Rchild = LRSN;
				LRSN->Lchild = iter->Lchild;
				if (iter->Lchild)
					iter->Lchild->Parent = LRSN;
				LRSN->Parent = iter->Parent;
				LRSN->Rchild = iter->Rchild;
				if (iter->Rchild)
					iter->Rchild->Parent = LRSN;
				delete iter;
			}
		}
		else if (iter->Rchild)
		{
			if (iter->Parent->value > iter->value)
			{
				iter->Parent->Lchild = iter->Rchild;
				iter->Rchild->Parent = iter->Parent;
				delete iter;
			}
			else if (iter->Parent->value < iter->value)
			{
				iter->Parent->Lchild = iter->Rchild;
				iter->Rchild->Parent = iter->Parent;
				delete iter;
			}
		}
		else if (iter->Lchild)
		{
			if (iter->Parent->value > iter->value)
			{
				iter->Parent->Lchild = iter->Lchild;
				iter->Lchild->Parent = iter->Parent;
				delete iter;
			}
			else if (iter->Parent->value < iter->value)
			{
				iter->Parent->Lchild = iter->Lchild;
				iter->Lchild->Parent = iter->Parent;
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