#include <iostream>
#include <string>
#include <vector>

using namespace std;
int area[100][100] = { -1, };

//����� �ٴ� ���� �ְų� ���� ���� �� �κ� ���� �ְų�, �Ǵ� �ٸ� ��� ���� �־�� �մϴ�.
//���� ���� �� �κ��� ��� ���� �ְų�, �Ǵ� ���� �� �κ��� �ٸ� ���� ���ÿ� ����Ǿ� �־�� �մϴ�.
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    memset(area, -1, sizeof(area));

    for (auto iter = build_frame.begin(); iter != build_frame.end(); iter++)
    {
        int x = iter->at(0);
        int y = iter->at(1);
        int a = iter->at(2); // 0 r, 1 b
        int b = iter->at(3); // 0 delete, 1 add

        int left = x - 1;
        int right = x + 1;
        int down = y - 1;

        if (a)
        {
            if (left < 0 || right >= 100 || down < 0) continue;
            if (b)
            {
                

            }
            else
            {

            }
        }
        else
        {
            if (b)
            {
                if (y == 0)
                {
                    if (area[x][y] != 0)
                    {
                        area[x][y] = 0;
                        vector<int> temp;
                        temp.push_back(x);
                        temp.push_back(y);
                        temp.push_back(0);

                        answer.push_back(temp);
                    }
                }
                else if ()

            }
            else
            {

            }
        }
    }

    return answer;
}

int main()
{

    vector<vector<int>> build_frame = 
    {
        {1,0,0,1},
        {1,1,1,1},
        {2,1,0,1},
        {2,2,1,1},
        {5,0,0,1},
        {5,1,0,1},
        {4,2,1,1},
        {3,2,1,1},
    };
    solution(5,build_frame);

    return 0;
}
