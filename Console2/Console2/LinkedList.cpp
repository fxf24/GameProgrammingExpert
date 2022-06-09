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
	int size = 0;

public:
	T& Front() 
	{
		return *head;
	}
	OnePathNode<T>* Begin()
	{
		return head;
	}

	int Size()
	{
		return size;
	}

	void Insert(T data, int idx)
	{
		if (idx > size) return;
		if (idx == 0) { PushFront(data); return; }

		OnePathNode<T>* in = new OnePathNode<T>;
		in->value = data;

		if (head)
		{
			OnePathNode<T>* temp = head;

			for (int i = 0; i < idx-1; i++)
			{
				temp = temp->next;
			}

			in->next = temp->next;
			temp->next = in;
			size++;
		}
	}

	void Erase(int idx)
	{
		if (idx > size) return;
		if (idx == 0) { PopFront(); return;}

		if (head)
		{
			OnePathNode<T>* temp = head;
			
			for (int i = 0; i < idx - 1; i++)
			{
				temp = temp->next;
			}

			OnePathNode<T>* temp2 = temp->next;
			temp->next = temp->next->next;

			delete temp2;
			size--;
		}
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
			size++;
		}
		else
		{
			head = temp;
			size++;
		}
	}

	T PopFront()
	{
		if (head)
		{
			OnePathNode<T>* temp = head;
			head = head->next;

			int num = temp->value;
			delete temp;
			size--;
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
		cout << "1. 삽입 2. 삭제 3. 중간삽입 4. 중간삭제" << endl;
		cin >> Select;
		if (Select == 1)
		{
			int input;
			cin >> input;
			a.PushFront(input);
		}
		else if (Select == 2)
		{
			cout << "Pop: " << a.PopFront() << endl;
		}
		else if (Select == 3)
		{
			cout << "입력할 값: " ;
			int data;
			cin >> data;
			cout << "위치: ";
			int idx;
			cin >> idx;
			a.Insert(data, idx);
		}
		else
		{
			cout << "삭제할 위치: ";
			int input;
			cin >> input;
			a.Erase(input);
		}
	}
	return 0;
}