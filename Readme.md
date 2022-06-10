# GameProgrammingExpert
### 포인터, OOP, 댕글링(자원), 모던(스마트 포인터) 

## 액세스
* 마이크로프로세서에서 액세스(access)는 저장장치의 데이터를 읽거나 쓰는 것을 말한다.
	* 포인터
	* 임의접근(Random Access) - 주소를 통해 한번에 찾아간다
* CPU는 메모리 주소를 통해 데이터에 임의접근 한다.
* 메모리 계층구조
	* 레지스터
	* 캐시
	* 메모리
	* 하드 디스크![구글 검](https://www.studytonight.com/computer-architecture/images/memory-heirarchy.png)
* 배열
	* 접근이 빠르다.
	* 삽입, 삭제가 느리다.
* 리스트
	* 접근이 느리다.
	* 삽입, 삭제가 빠르다.

## Memory Hieracrchy Byte Padding
### Cache
* cache에 필요한 데이터의 주소가 있다면, cache hit, 없으면 cache miss라고 한다.
* cache miss 가 적을 수록 성능이 향상된다.
### 바이트 패딩
* 구조체나 클래스의 멤버변수를 선언할때, 레지스터의 크기에 따라 패딩 바이트가 생성되게된다.
* 따라서 효율적으로 멤버변수를 선언해주면 패딩 바이트의 생성을 줄여, 불필요한 메모리 낭비를 줄일 수 있다.
	* ex) 64bit : int, int, char, char, double, short = 32byte
	![패딩바이트 구조1](https://blog.kakaocdn.net/dn/DricJ/btqUtXv0u1P/HevtSKMcIVm86xH1hqPokK/img.png)
						 double, int, int, char, char, short = 24byte
						 ![패딩 바이트를 최소화 할 수 있는 구조](https://blog.kakaocdn.net/dn/dqtfWm/btqUwy3kb9I/eVnfymjwPxxrKKMhL2toqk/img.png)

## C++
* Rvalue Lvalue
	*  R-value 는 값 그 자체를 이야기 한다.  수정할 수 없는 값들. ex) 임시객체, 상수(literal)
	*  L-value 는 주소 정보를 포함한 값들을 이야기 한다. 수정할 수 있는 값들. ex) 객체
* Rvalue reference
	* && 를 이용해 Rvalue 참조
* 이동생성자
	* &&를 매개변수 값으로 갖는다.
	* 메모리를 재할당 하지 않는다.
	* 얕은복사 후 원본의 소유권을 이전하는 방식으로 객체를 생성
### Tree
* 전위 순회 (Preorder)
	* Root -> Left -> Right 순으로 순회한다.
	* ![](https://t1.daumcdn.net/cfile/tistory/999E283D5AE877F614)
	* 1 2 4 8 9 5 10 11 3 6 12 13 7 14 15
* 중위 순회 (Inorder)
	* Left -> Root -> Right 순으로 순회한다.
	* ![](https://t1.daumcdn.net/cfile/tistory/99E18C365AE877F602)
	* 8 4 9 2 10 5 11 1 12 6 13 3 14 7 15
* 후위 순회 (Postorder)
	* Left -> Right -> Root 순으로 순회한다.
	* ![](https://t1.daumcdn.net/cfile/tistory/9924604B5AE877F609)
	* 8 9 4 10 11 5 2 12 13 6 14 15 7 3 1

## Computer Graphics
### 래스터 그래픽, 벡터 그래픽
* 래스터 그래픽
	* bmp, gif, jpg, png
	* 픽셀 데이터로 이미지를 저장한다.
* 벡터 그래픽 
	* svg
	* 점과 선 데이터로 이미지를 저장한다.

### 해상도
* 가로 방향 픽셀 수 X 세로 방향 픽셀 수
* 출력 대상이 디스플레이 이기 때문에 해상도의 범위를 벗어 날 수 없다.

### 픽셀
* 그래픽스의 최소 단위
* RGBA의 값을 담고 있다.
* 직사각형들로 이루어져 있다.

### 렌더링 파이프라인
* 정점, 선 데이터를 백버퍼(해상도 크기) 출력

### 행렬
* 행렬 곱을 통해 좌표를 변환해 준다.
	* 위치변환 (Translation) - 중심점이 원점에서 이동한 값
		* ![](http://www.opengl-tutorial.org/assets/images/tuto-3-matrix/translationMatrix.png)
	* 크기변환 (중심점 으로부터) (Scaling) - 정점이 중심정에서 멀어진 비율 값
		* ![](http://www.opengl-tutorial.org/assets/images/tuto-3-matrix/scalingMatrix.png)
	* 회전변환 (중심점 으로부터) (Rotation) - 원래 회전값에서 + a 값
		* ![{\displaystyle {\begin{pmatrix}\cos \theta &-\sin \theta \\\sin \theta &\cos \theta \end{pmatrix}}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/ab40477843fea7939707c800ffd3b668ee8ce685)


### 좌표
* 공간내에 원점(0, 0, 0)으로부터 멀어진 값
* 정점 : 중심점에서 멀어진 꼭지점 좌표값

### 벡터
* 방향, 크기를 나타내는 것
* 앞 좌표를 원점으로 생략하면 끝점값으로 표현
* 원점으로부터 좌표도 벡터로 표현이 가능
* 벡터의 스칼라곱
	* 스칼라 : 벡터의 길이, 크기
	* v1 * 2
* 벡터와 벡터의 합연산
	* v1 + v2
	* ![](https://blog.kakaocdn.net/dn/bsDAHw/btqw1uJ6aSg/5NL7FmQ2mFk4ptFWDOLPUK/img.png)
* 벡터의 내적, 외적
	* 내적 : 결과값이 스칼라
	* 
	* 외적 : 결과값이 벡터
