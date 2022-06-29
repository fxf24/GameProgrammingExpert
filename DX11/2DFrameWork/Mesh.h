#pragma once
class Mesh
{
    //정점(꼭지점),정점을 잇는 타입(선,점,면),

    //점들이 갖는멤버값
    //기준점에서부터의 좌표(상대좌표) x,y,z,w
    //색
    //텍스처 좌표 (uv)
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

