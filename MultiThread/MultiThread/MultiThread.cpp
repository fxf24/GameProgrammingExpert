#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int number = 0;
mutex m1;

void Func1()
{
    for (int i = 0; i < 1000000; i++)
    {
        m1.lock();
        number = number + 1;
        m1.unlock();
    }
}

int main()
{
    // thread 할당
    thread* t1[100];

    Func1();
    Func1();

    for (int i = 0; i < 100; i++)
    {
        t1[i] = new thread(Func1);
    }

    Func1();
    Func1();
    Func1();

    //t1이 종료될때까지 대기
    for (int i = 0; i < 100; i++)
    {
        t1[i]->join();
    }
    cout << number << endl;
}

