#pragma once
class Shader
{
    ID3D11InputLayout*      vertexLayout;
    ID3D11VertexShader*     vertexShader;
    ID3D11PixelShader*      pixelShader;
   
public:
    ID3D11GeometryShader*   geometryShader;
    VertexType              vertextype;
    string                  file;
    Shader();
    ~Shader();
    void LoadFile(string file, VertexType vertextype);
    void LoadGeometryFile(string file);
    void Set();
};
