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
### 스마트 포인터
* unique_ptr
	* 하나의 스마트 포인터만이 특정 객체를 소유할 수 있도록, 객체에 소유권 개념을 도입한 스마트 포인터입니다.
* shared_ptr
	* 하나의 특정 객체를 사용하는 스마트 포인터가 총 몇 개인지를 확인하는 스마트 포인터입니다.
	* use_count()를 이용하여 몇개의 스마트포인터가 사용하고 있는지 확인 가능.
	* reset()을 통해 해제할 수 있고, use_count()가 0 이되면 자동으로 메모리 해제.
* weak_ptr
	* 하나 이상의 shared_ptr 인스턴스가 소유하는 객체에 대한 접근을 제공하지만, 소유자의 수에는 포함되지 않는 스마트 포인터입니다.
	* 서로가 상대방을 가리키는 shared_ptr을 가지고 있다면, use_count가 절대 0이 되지 않으므로 메모리는 영원히 해제되지 않는다. 순환 참조(circular reference)
	* weak_ptr은 이러한 shared_ptr인스턴스 사이의 순환 참조를 제거하기 위해서 사용됩니다.

## Tree
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
* 행렬은 왼손좌표계, 행우선으로 사용할 것 이다.
* vertex * 4x4 matrix 를 할때, vertex 뒤의 두값은 고정되어 있다. 
* 3번째는 위치, 4번째는 동차라고 한다.
* 동차  
	* 0 - 노멀(법선)변환
	* 1 - 좌표변환

### 좌표
* 공간내에 원점(0, 0, 0)으로부터 멀어진 값
* 정점 : 중심점에서 멀어진 꼭지점 좌표값

### 벡터
* 방향, 크기를 나타내는 것
* 앞 좌표를 원점으로 생략하면 끝점값으로 표현
* 원점으로부터 좌표도 벡터로 표현이 가능
* 벡터의 스칼라곱
	* 스칼라 : 벡터의 길이, 크기, 물리량
	* v1 * 2
* 벡터와 벡터의 합연산
	* v1 + v2
	* ![](https://blog.kakaocdn.net/dn/bsDAHw/btqw1uJ6aSg/5NL7FmQ2mFk4ptFWDOLPUK/img.png)
* 내적
	* A · B = |A| |B| Cosθ
	* 결과값이 스칼라
* 외적
	* A x B = C
	* 결과값이 벡터
* 단위벡터 : 크기가 1인 벡터
	* 단위(방향) * 길이(길이) = 원하는 길이의 벡터

### 호도법
* 반지름과 호의 길이가 같을때 = 1 radian
* 360 == 2PI, 180 == PI
* 1 radian == 60
* radian 변환 90 * PI / 180

### 삼각함수
* 삼각함수(각도) -> return 삼각비
* 역삼각함수(삼각비) -> return 각도

### Object Pool
* 벡터, 리스트도 좋지만, 실행 중에 새로 추가, 삭제를 하는 것은 퍼포먼스에 영향을 줄 수 있다.
* 그래서 배열을 사용한다. 차라리 처음 만들때 메모리를 많이 사용하는 것 이 낫다.

### 공간
* X, Y, Z 를 보통 World Space라고 한다.
* 오브젝트의 X, Y, Z는 RIGHT, UP, Forward(Front) 등으로 부르며, Local Space라고 한다.
* ![](https://lh4.googleusercontent.com/XR_CmhGtmK4M5_izjpP5aJ3TKKH25fPmVL8vZZRa_ZOEdkfn58cpeggHOoxtjRNRiQQRqf7rSDU0rXXGmRnAo_k-vmJg7zce2Lv4zo7Q2YE-sg_ceexbKtO0teWLFZsHEqbOPadM)
* Model(Local) Space 는 Object Pivot이 Local 좌표계 상에서 원점에 존재하는 공간이다.
* World Space 는 Object를 공간 상에서 특정한 World로 이동 및 회전, Scale 된 좌표이다. 이는 Model Matrix로 변환이 이루어진다.
* View(Camera) Space는 World 상에서 놓여진 Object를 그것을 바라보는 카메라의 시점으로 옮긴 공간이다. View Matrix의 곱하기 연산으로 이뤄진다.
* Clip Space는 카메라의 Frustum 공간 밖, 즉 보여지는 공간 밖에 위치해 있어서 보여지지 않는 오브젝트를 걸러낸다. 그리고, 카메라의 뷰에 따라서 Perspective View, Orthogonal View를 적용한 상태로 만드는 변환 공간이다. 이 변환은 Projection Matrix 적용으로 이뤄진다.
* Clip Space에서 NDC(Normalized Device Coordinate) 공간을 따로 분리하기도 하는데, 이는 디바이스에서 사용하기 위순 Normalized 된 형태의 좌표계로 변환 시키는 연산이다. Vertex 값을 Homogeneous Coordinate의 w값으로 나눈다. (x, y, z, w) -> (x/w, y/w, z/w, 1). 이 연산은 최적화를 위해서 Cliping이 일어난 후에 발생한다.
* Screen Space는 Clip Space의 좌표들을 Screen 좌표계, 즉 화면에 보이는 공간으로 이동시키는 변환이다. Viewport Transformation 연산으로 이뤄진다.

### View Transformation
* 카메라로 표현한다.
* World space에서 camera space로 표현한다.
* Object의 모든 점들을 카메라 관점에서의 점으로 바꾼다.
* 카메라의 위치와 방향을 설정해야 하고, 카메라의 frame을 설정해야 한다.
* ![](https://blog.kakaocdn.net/dn/bQlEv9/btq107RaGuZ/KGHh9wvXqdG30bEjLW0BsK/img.png)
* Eye point : 카메라의 위치
* Look-at point : 타겟 물체의 위치
* Up vector : 카메라에 수직인 방향을 나타내는 벡터
* ![](https://blog.kakaocdn.net/dn/c7yHxT/btq11y8U8KV/vxEoQb4KxVlAyXB0XkOKJ0/img.png)

### NDC
* Normalized Device Coordinate
* (-1, -1) ~ (1, 1) 의 종횡비 1:1 비율을 가진 2차원 좌표계를 의미한다. 뷰 스페이스의 모든 3차원 좌표는 이 2차원 좌표계로 사영된다.

### Projection
* 컴퓨터 크래픽스에서의 projection은 주로 3D coordinate 를 2D screen coordinate로 매핑하는 것을 말한다.
* 그러나 실제로 하는 것은 3D -> 3D으로, 임의의 view volume을 canonical view volume으로 매핑하는 것이다.
* 차원이 낮아진다고 해서 물체의 깊이를 표현하는 z값이 필요없어지는 것은 아니다.
* 어떤 물체가 앞에있는지를 판단하는 depth test를 위해서 남아있다.
* Orthogonal Projection
	* 직육면체를 view volume으로 사용한다.
	* 이 view volume을 canonical view volume 으로 만든다.
	* 원근법을 표현하지 못한다.
	* 직육면체를 정육면체로 변환하는 것이기 때문에 결국 scaling과 translation의 조합이다.
	* ![](https://blog.kakaocdn.net/dn/bwRT78/btq1WK4kon0/RlLhRp2GyEVc2KDZFFyTgK/img.png)
* Perspective Projection
	* 원근감, 소실점이 있다.
	* viewing frustum을 canonical view volume으로 매핑하는 것이다.
	* ![](https://blog.kakaocdn.net/dn/bu3zrh/btq1XMm8s45/w7MaXCglHXwY9i8pT6f9g1/img.png)
	* ![](https://blog.kakaocdn.net/dn/rXCPi/btq13AfiXYn/8JMhrdOjelDQ9mzPmdQUpk/img.png)


### Viewport Transformation
* Viewport는 화면의 사각형 모양의 viewing region이다.
* ![](https://blog.kakaocdn.net/dn/UuhjK/btq18D9IB2Y/mZ7xMAPglOK8yj1JcaASZk/img.png)

### 법선벡터(Normal Vector)
* 법선벡터는 물체의 표면에서 수직으로 튀어나온 벡터이다.
* 종법선(Binormal) 벡터 :  법선에 수직인 벡터이다.
* 접선(Tangent) 벡터 : 법선과 종법선에 수직인 벡터로 법선과 종법선의 외적으로 구할수 있다. 

### 포워드, 디퍼드 렌더링
* 포워드 렌더링
	* 전통적인 렌더링 방식
	*  3D공간에 존재하는 폴리곤을 픽셀화 하여, 그 픽셀마다 쉐이딩과 라이팅 연산을 더하는 방식으로 묘사한다.
	*	장점 : 저사양에서도 잘 작동한다. 안티 앨리어스 처리를 하드웨어에서 지원. 오래된 방식이라 문제 해결책이 만들어져 있는 경우가 많다.
	*	단점 : 라이팅 연산이 느림. 복잡한 화면 구성하거나, 폴리곤이 많은 모델을 렌더링 걸기 불리한 방식. 그림자 처리가 어려움. 화면 깊이 값을 이용한 포스트 이펙트는 따로 처리해야함.
* 디퍼드 렌더링
	* 폴리곤을 픽셀화하여 포토샵의 레이어처럼 정보를 나누어 비디오 메모리에 저장한다. 여기에서 각종 쉐이더와 라이팅 효과를 거쳐 화면에 보여준다.
	* 장점 : 수많은 동적 라이팅을 실시간으로 보여줄 수 있다. 그림자도 손쉽게 그려줄 수 있다. 쉐이더를 간단하게 지원하고, 픽셀정보를 메모리에 저장하면서 생기는 여러가지 이점을 쓸 수 있다. 수많은 오브젝트와 복잡한 모델링을 표현할때 유리하다.
	* 단점 : 뒤에 그려지는 오브젝트 정보가 비디오 메모리에서 소실되기 때문에 알파가 빠지는 오브젝트를 표현할 수 없다. 요구하는 하드웨어 사양이 포워드 랜더링 방식보다 높고, 해상도가 올라갈수록 요구하는 비디오 메모리가 기하급수적으로 늘어난다. 안티앨리어스를 구현하기 까다롭다.

### 퐁 쉐이딩 (Phong Shading), PBR (Physically Based Rendering)
* 퐁 쉐이딩 (Phong Shading)
	* 포면의 점들간의 보간작업을 진행하는 테크닉을 가리키는 용어이다.
	* Ambient + Diffuse + Specular = Phong Reflection
		* Phong Reflection :빛의 양을 계산해 내는 작업.
	* 각 픽셀에 대한 노말벡터를 구하고, 이 노말벡터 값을 Phong reflection 모델에서 요구하는 노말벡터 값에 대입하여 빛의 세기를 얻을 수 있다.
* PBR (Physically Base Rendering)
	* 포면의 재질에 따른 빛의 반사가 물리적으로 어떻게 이루어지는지를 시뮬레이션해서 그래픽을 표현하는 기법
	* 물체의 거칠기(Roughness)에 따라 정반사와 난반사의 비율이 바뀌는데, 보통 표면이 거칠수록 난반사의 비율이 커지고 반대로 표면이 매끄러울수록(Glossiness) 정반사의 비율이 커진다.
	* Specular / Glossiness
		* 재질의 기본색 : Diffuse Texture
		* 재질의 반사광 : Specular Texture
		* 재질의 거칠기 : Glossiness Texture
	* Metalic / Roughness
		* 재질의 기본색 : Base Color Texture
		* 재질의 반사광 : Metallic Texture
		* 재질의 거칠기 : Roughness Texture

### 애니메이션
* 키프레임 애니메이션
	* 전체 애니메이션 중에서 중요한 몇개의 프레임에 애니메이션 키 값을 등록하고, 나머지들은 자동으로 생성하는 방법이다.
	* 중요 프레임의 사이에 있는 프레임들은 보간하여 자동으로 생선한다.
	* 회전은 사원수( Quaternion )를 이용한다.
* 스키닝 애니메이션
	* 스키닝이란 피부를 붙이는 작업이라고 말할 수 있다. 3차원 메쉬는 관절과 관절 사이가 사람과 달리 끊김 현상이 발생할 수 있는데, 이를 막는 기법을 스키닝이라고 한다. 마치 사람의 뼈 위에 피부가 있어서 관절부위가 보이지 않는 것처럼 말이다. 
	* V_world = V_local(메시의 로컬좌표) X M_world(메시의 월드행렬) X M_world의 역행렬(본의 월드의 역행렬) X M_Animation(본의 애니메이션 월드행렬) X W_0( 0번째 가중치값 )

### 대수학
* 사원수 (Quaternion)
	* 해밀턴이 정의한 3차원 공간에서 점을 표현하기위한 수
	* 기본적인 규칙 : i^2^ = j^2^ = k^2^ = ijk = -1
	* 분배법칙과 결합법칙은 성립하지만, 교환법칙은 성립하지 않는다.
* YawPitchRoll (오일러 회전)
	* 강체가 놓인 방향을 3차원 공간에서 표기하기 위해 도입한 3가지 각도이다.
	* Roll 은 X축을 기준으로 회전한 각도, Pitch는 Y축을 기준으로 회전한 각도, Yaw는 Z축을 기준으로 회전한 각도이다.
* 짐벌락
	* 한축의 회전이 다른 축과 겹쳐서 회전할 수 있는 축을 하나 잃어버리는 현상을 짐벌락이라고 한다.

### GPGPU
* General-Purpose computing on Graphics Processing Unit
* 그래픽 처리를 위한 보조 장치였던 GPU를 보완하여 컴퓨터의 중앙처리 장치인 CPU를 대신하여 모든 데이터 연산 및 처리를 하는 GPU상의 범용 계산 장치
* 컴퓨터 아키텍처를 변형하여 데이터에 스트림 프로세싱을 이용하여 고정도 연산을 그래픽 파이프라인에 연결하는 방식으로 CPU의 역할을 대신하는 방법이 지속적으로 연구 개발 중
* GPU 연산을 위한 하드웨어 요구사항
	* 프로그램 가능한 셰이더 - 더 많은 표현(렌즈 효과, 변위 매핑, 필드 깊이 등)
	* 데이터 자료형의 추가 - 모든 계산이 행렬식으로 처리되지는 않기 때문
* GPGPU API - CUDA
