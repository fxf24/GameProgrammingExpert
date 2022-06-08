#include <iostream>
using namespace std;

template <typename T>
struct OnePathNode
{
	OnePathNode*	next = nullptr;
	T				value;
};

template <typename T>
struct TwoPathNode
{
	TwoPathNode* next;
	TwoPathNode* prev;
	T				value;
};

template <typename T>
class FowardList
{
private:
	OnePathNode<T>* head = nullptr;

public:
	T& Front() 
	{
		return *head;
	}
	OnePathNode<T>* Begin()
	{
		return head;
	}

	void PushFront(T data)
	{

		OnePathNode<T>* temp = new OnePathNode<T>;
		temp->value = data;

		if (head)
		{
			OnePathNode<T>* second = head;
			head = temp;
			head->next = second;
		}
		else
			head = temp;
	}

	T PopFront()
	{
		if (head)
		{
			OnePathNode<T>* temp = head;
			head = head->next;

			int num = temp->value;
			delete temp;
			return num;
		}

		return -1;
	}

	void PrintAll()
	{
		OnePathNode<T>* iter = head;
		while (1)
		{
			if (iter == nullptr) break;

			cout << iter->value << "->";

			iter = iter->next;
		}
	}
};


int main()
{
	FowardList<int> a;

	while (1)
	{
		a.PrintAll(); 
		cout << endl;

		int Select;
		cout << "1. »ðÀÔ 2. »èÁ¦" << endl;
		cin >> Select;
		if (Select == 1)
		{
			int input;
			cin >> input;
			a.PushFront(input);
		}
		else
		{
			cout << "Pop: " << a.PopFront() << endl;
		}
	}
	return 0;
}