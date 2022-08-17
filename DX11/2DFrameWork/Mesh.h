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
  
    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
    VertexType              vertexType;
    UINT                    byteWidth;

    
public:
    void* vertices;
    UINT                    vertexCount;
    UINT*                   indices;
    UINT                    indexCount;
    string                  file;
public:
    Mesh();
    Mesh(void* vertices, UINT vertexCount, UINT* indices,
        UINT indexCount, VertexType type);
    ~Mesh();

    void Set(); // binding
    void LoadFile(string file);
    void SaveFile(string file);
    UINT GetIndexCount() { return indexCount; }
    const Vector3& GetVertexPosition(UINT idx);
    void UpdateMesh();
};

