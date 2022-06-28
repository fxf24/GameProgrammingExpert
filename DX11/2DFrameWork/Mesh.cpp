#include "framework.h"
Mesh::Mesh()
    :vertices(nullptr), indices(nullptr)
    , vertexBuffer(nullptr), indexBuffer(nullptr)
{


    ////////////////////////////////////////////////////
    /*vertexType = VertexType::P;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;


    VertexP* Vertex;
    byteWidth = sizeof(VertexP);
    file = "0.Cube.mesh";

    vertexCount = 8;
    indexCount = 14;

    Vertex = new VertexP[vertexCount];
    indices = new UINT[indexCount];

    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    Vertex[0].position.z = 0.5f;

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    Vertex[1].position.z = 0.5f;

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.5f;
    Vertex[2].position.z = 0.5f;

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = 0.5f;
    Vertex[3].position.z = 0.5f;

    Vertex[4].position.x = -0.5f;
    Vertex[4].position.y = -0.5f;
    Vertex[4].position.z = -0.5f;

    Vertex[5].position.x = -0.5f;
    Vertex[5].position.y = 0.5f;
    Vertex[5].position.z = -0.5f;

    Vertex[6].position.x = 0.5f;
    Vertex[6].position.y = -0.5f;
    Vertex[6].position.z = -0.5f;

    Vertex[7].position.x = 0.5f;
    Vertex[7].position.y = 0.5f;
    Vertex[7].position.z = -0.5f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    indices[4] = 7;
    indices[5] = 1;

    indices[6] = 5;
    indices[7] = 0;
    indices[8] = 4;
    indices[9] = 2;
    indices[10] = 6;
    indices[11] = 7;

    indices[12] = 4;
    indices[13] = 5;*/
    

    ///////////////////////////////////////////////////

    vertexType = VertexType::PC;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;


    VertexPC* Vertex;
    byteWidth = sizeof(VertexPC);
    file = "1.Circle.mesh";
    vertexCount = 360;
    indexCount = 360 * 2;
    //3*2*3 의 인덱스
    Vertex = new VertexPC[vertexCount];
    indices = new UINT[indexCount];

    for (int i = 0; i < 360; i++)
    {
        Vertex[i].position = Vector3(cosf(i * TORADIAN), sinf(i * TORADIAN), 0);
        Vertex[i].color = Color(0, 1, 0);
        indices[i * 2] = i;
        indices[i * 2 + 1] = (i + 1) % 360;
    }

    //0,1,2,3 (빨간색)
    //Vertex[0].position = Vector3(-1, -1, -1);
    //Vertex[0].color = Color(1, 0, 0);
    //Vertex[1].position = Vector3(-1, 1, -1);
    //Vertex[1].color = Color(1, 0, 0);
    //Vertex[2].position = Vector3(1, 1, -1);
    //Vertex[2].color = Color(1, 0, 0);
    //Vertex[3].position = Vector3(1, -1, -1);
    //Vertex[3].color = Color(1, 0, 0);


    ////빨간색면
    //indices[0] = 0;
    //indices[1] = 1;
    //indices[2] = 2;

    //indices[3] = 2;
    //indices[4] = 3;
    //indices[5] = 0;

    ////4,5,6,7 (녹색)
    //Vertex[4].position = Vector3(1, -1, -1);
    //Vertex[4].color = Color(0, 1, 0);
    //Vertex[5].position = Vector3(1, 1, -1);
    //Vertex[5].color = Color(0, 1, 0);
    //Vertex[6].position = Vector3(1, 1, 1);
    //Vertex[6].color = Color(0, 1, 0);
    //Vertex[7].position = Vector3(1, -1, 1);
    //Vertex[7].color = Color(0, 1, 0);

    //indices[6] = 4;
    //indices[7] = 5;
    //indices[8] = 6;

    //indices[9] = 6;
    //indices[10] = 7;
    //indices[11] = 4;

    ////8,9,10,11 (파란색)
    //Vertex[8].position = Vector3(-1, 1, -1);
    //Vertex[8].color = Color(0, 0, 1);
    //Vertex[9].position = Vector3(-1, 1, 1);
    //Vertex[9].color = Color(0, 0, 1);
    //Vertex[10].position = Vector3(1, 1, 1);
    //Vertex[10].color = Color(0, 0, 1);
    //Vertex[11].position = Vector3(1, 1, -1);
    //Vertex[11].color = Color(0, 0, 1);

    //indices[0 + 12] = 8;
    //indices[1 + 12] = 9;
    //indices[2 + 12] = 10;

    //indices[3 + 12] = 10;
    //indices[4 + 12] = 11;
    //indices[5 + 12] = 8;

    ////12,13,14,15 (노란색)
    //Vertex[12].position = Vector3(-1, -1, -1);
    //Vertex[12].color = Color(1, 1, 0);
    //Vertex[13].position = Vector3(-1, -1, 1);
    //Vertex[13].color = Color(1, 1, 0);
    //Vertex[14].position = Vector3(1, -1, 1);
    //Vertex[14].color = Color(1, 1, 0);
    //Vertex[15].position = Vector3(1, -1, -1);
    //Vertex[15].color = Color(1, 1, 0);


    ////노란색
    //indices[18] = 13;
    //indices[19] = 12;
    //indices[20] = 14;

    //indices[21] = 15;
    //indices[22] = 14;
    //indices[23] = 12;

    ////16,17,18,19 (분홍색)
    //Vertex[16].position = Vector3(-1, -1, 1);
    //Vertex[16].color = Color(1, 0, 1);
    //Vertex[17].position = Vector3(-1, 1, 1);
    //Vertex[17].color = Color(1, 0, 1);
    //Vertex[18].position = Vector3(1, 1, 1);
    //Vertex[18].color = Color(1, 0, 1);
    //Vertex[19].position = Vector3(1, -1, 1);
    //Vertex[19].color = Color(1, 0, 1);


    ////분홍색면
    //indices[24] = 17;
    //indices[25] = 16;
    //indices[26] = 18;

    //indices[27] = 19;
    //indices[28] = 18;
    //indices[29] = 16;

    ////20,21,22,23 (하늘색)
    //Vertex[20].position = Vector3(-1, -1, -1);
    //Vertex[20].color = Color(0, 1, 1);
    //Vertex[21].position = Vector3(-1, 1, -1);
    //Vertex[21].color = Color(0, 1, 1);
    //Vertex[22].position = Vector3(-1, 1, 1);
    //Vertex[22].color = Color(0, 1, 1);
    //Vertex[23].position = Vector3(-1, -1, 1);
    //Vertex[23].color = Color(0, 1, 1);


    ////하늘색면
    //indices[30] = 21;
    //indices[31] = 20;
    //indices[32] = 22;

    //indices[33] = 23;
    //indices[34] = 22;
    //indices[35] = 20;


    vertices = (void*)Vertex;
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }
    //저장용
    SaveFile(file);
}


Mesh::~Mesh()
{
    switch (vertexType)
    {
    case VertexType::P:
        delete[](VertexP*)vertices;
        break;
    case VertexType::PC:
        delete[](VertexPC*)vertices;
        break;
    case VertexType::PCN:
        delete[](VertexPCN*)vertices;
        break;
    case VertexType::PTN:
        delete[](VertexPTN*)vertices;
        break;
    case VertexType::MODEL:
        delete[](VertexModel*)vertices;
        break;
    case VertexType::TERRAIN:
        delete[](VertexTerrain*)vertices;
        break;
    case VertexType::PT:
        delete[](VertexPT*)vertices;
        break;
    case VertexType::PS:
        delete[](VertexPS*)vertices;
        break;
    case VertexType::PSV:
        delete[](VertexPSV*)vertices;
        break;
    }
    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
    SafeDeleteArray(indices);
}

void Mesh::Set()
{
    UINT offset = 0;
    D3D->GetDC()->IASetVertexBuffers(0,
        1,
        &vertexBuffer,
        &byteWidth,
        &offset);
    D3D->GetDC()->IASetPrimitiveTopology
    (primitiveTopology);
    D3D->GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::LoadFile(string file)
{
    this->file = file;
    //읽기전
    switch (vertexType)
    {
    case VertexType::P:
        if (vertices)delete[](VertexP*)vertices;
        break;
    case VertexType::PC:
        if (vertices)delete[](VertexPC*)vertices;
        break;
    case VertexType::PCN:
        if (vertices)delete[](VertexPCN*)vertices;
        break;
    case VertexType::PTN:
        if (vertices)delete[](VertexPTN*)vertices;
        break;
    case VertexType::MODEL:
        if (vertices)delete[](VertexModel*)vertices;
        break;
    case VertexType::TERRAIN:
        if (vertices)delete[](VertexTerrain*)vertices;
        break;
    case VertexType::PT:
        if (vertices)delete[](VertexPT*)vertices;
        break;
    case VertexType::PS:
        if (vertices)delete[](VertexPS*)vertices;
        break;
    case VertexType::PSV:
        if (vertices)delete[](VertexPSV*)vertices;
        break;
    }

    BinaryReader in;
    wstring path = L"../Contents/Mesh/" + Util::ToWString(file);
    in.Open(path);

    vertexType = (VertexType)in.UInt();
    primitiveTopology = (D3D_PRIMITIVE_TOPOLOGY)in.UInt();
    byteWidth = in.UInt();
    vertexCount = in.UInt();
    indexCount = in.UInt();

    SafeDeleteArray(indices);
    indices = new UINT[indexCount];


    //읽고난후
    switch (vertexType)
    {
    case VertexType::P:
    {
        vertices = new VertexP[vertexCount];
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
        }
        break;
    }

    case VertexType::PC:
    {
        vertices = new VertexPC[vertexCount];
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
        }
        break;
    }
    case VertexType::PCN:
    {
        vertices = new VertexPCN[vertexCount];
        VertexPCN* vertex = (VertexPCN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
            vertex[i].normal = in.vector3();
        }
        break;
    }
    case VertexType::PTN:
    {
        vertices = new VertexPTN[vertexCount];
        VertexPTN* vertex = (VertexPTN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
        }
        break;
    }
    case VertexType::MODEL:
    {
        vertices = new VertexModel[vertexCount];
        VertexModel* vertex = (VertexModel*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
            vertex[i].tangent = in.vector3();
            vertex[i].indices = in.vector4();
            vertex[i].weights = in.vector4();
        }
        break;
    }
    case VertexType::TERRAIN:
    {
        vertices = new VertexTerrain[vertexCount];
        VertexTerrain* vertex = (VertexTerrain*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
            vertex[i].weights = in.Float();
        }
        break;
    }
    case VertexType::PT:
    {
        vertices = new VertexPT[vertexCount];
        VertexPT* vertex = (VertexPT*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
        }
        break;
    }
    case VertexType::PS:
    {
        vertices = new VertexPS[vertexCount];
        VertexPS* vertex = (VertexPS*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].size = in.vector2();
        }
        break;
    }
    case VertexType::PSV:
    {
        vertices = new VertexPSV[vertexCount];
        VertexPSV* vertex = (VertexPSV*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].size = in.vector2();
            vertex[i].velocity = in.vector3();
        }
        break;
    }
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        indices[i] = in.UInt();
    }
    in.Close();

    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }

}

void Mesh::SaveFile(string file)
{
    this->file = file;
    BinaryWriter out;
    wstring path = L"../Contents/Mesh/" + Util::ToWString(file);
    out.Open(path);

    out.UInt((UINT)vertexType);
    out.UInt((UINT)primitiveTopology);
    out.UInt(byteWidth);
    out.UInt(vertexCount);
    out.UInt(indexCount);

    switch (vertexType)
    {
    case VertexType::P:
    {
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
        }
        break;
    }

    case VertexType::PC:
    {
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
        }
        break;
    }
    case VertexType::PCN:
    {
        VertexPCN* vertex = (VertexPCN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
            out.vector3(vertex[i].normal);
        }
        break;
    }
    case VertexType::PTN:
    {
        VertexPTN* vertex = (VertexPTN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
        }
        break;
    }
    case VertexType::MODEL:
    {
        VertexModel* vertex = (VertexModel*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
            out.vector3(vertex[i].tangent);
            out.vector4(vertex[i].indices);
            out.vector4(vertex[i].weights);
        }
        break;
    }
    case VertexType::TERRAIN:
    {
        VertexTerrain* vertex = (VertexTerrain*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
            out.Float(vertex[i].weights);
        }
        break;
    }
    case VertexType::PT:
    {
        VertexPT* vertex = (VertexPT*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
        }
        break;
    }
    case VertexType::PS:
    {
        VertexPS* vertex = (VertexPS*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].size);
        }
        break;
    }
    case VertexType::PSV:
    {
        VertexPSV* vertex = (VertexPSV*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].size);
            out.vector3(vertex[i].velocity);
        }
        break;
    }
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        out.UInt(indices[i]);
    }
    out.Close();
}


