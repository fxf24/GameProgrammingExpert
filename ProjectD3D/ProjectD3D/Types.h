#pragma once

//추상클래스 인터페이스
//혼자 객체로써 존재x 상속받는 클래스에서는 순수가상함수를 반드시 재정의
class Scene 
{
public:
	//순수가상함수 

	virtual ~Scene() {};

	//씬 초기화
	virtual void Init() = 0;
	//씬 갱신
	virtual void Update() = 0;
	//씬 출력
	virtual void Render() = 0;
};

//싱글톤 패턴
template <typename T>
class Singleton
{
public:
    virtual ~Singleton() {};
    static T* GetInstance()
    {
        static T* Instance = new T;
        return Instance;
    };
    void DeleteSingleton()
    {
        delete GetInstance();
    };
};