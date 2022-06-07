#include <iostream>
#include <forward_list> // 단방향 리스트
#include <list> // 양방향 리스트

using namespace std;

class A
{
private:
    int a = 3;
public:
    int GetA()
    {
        return a;
    }
};

int main()
{
    //list<int> Name;
    forward_list<int> Name;

    Name.push_front(3);
    Name.push_front(10);

    Name.front() = 5;

    cout << Name.front() << endl;
    //cout << Name.back() << endl;

    cout << *Name.begin() << endl;
    //cout << *(--Name.end()) << endl;
    cout << *(Name.end()) << endl;

    
    A a;

    // a.GetA() = 5;

    // front, back
    // 참조리턴 Lvalue
    //
    // begin, end
    // 반복자 리턴
    //


}

