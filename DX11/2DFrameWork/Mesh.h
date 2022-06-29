#pragma once
class Mesh
{
    //����(������),������ �մ� Ÿ��(��,��,��),

    //������ ���¸����
    //���������������� ��ǥ(�����ǥ) x,y,z,w
    //��
    //�ؽ�ó ��ǥ (uv)
    friend class GameObject;

private:
    ID3D11Buffer*           vertexBuffer;
    ID3D11Buffer*           indexBuffer;
    string                  file;
    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
    VertexType              vertexType;
    UINT                    byteWidth;

    UINT                    vertexCount;
    UINT                    indexCount;
    void*                   vertices;
    UINT*                   indices;
public:
    Mesh();
    ~Mesh();

    void Set(); // binding
    void LoadFile(string file);
    void SaveFile(string file);
};

