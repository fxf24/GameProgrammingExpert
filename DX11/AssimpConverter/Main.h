#pragma once


class Main : public Scene
{
private:
	Camera*			Cam;
	Actor*			Grid;
	vector<Actor*>	List;
	const aiScene*  scene;
	string			file;
	Actor*			actor;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	Matrix ToMatrix(aiMatrix4x4& value)
	{
		return Matrix
		(
			value.a1, value.b1, value.c1, value.d1,
			value.a2, value.b2, value.c2, value.d2,
			value.a3, value.b3, value.c3, value.d3,
			value.a4, value.b4, value.c4, value.d4
		);
	};
	void ReadMaterial();
	void ReadNode(GameObject* dest, aiNode* src);
	void ReadMesh(GameObject* dest, aiNode* src);
	void ReadBoneData(aiMesh* mesh, vector<class VertexWeights>& vertexWeights);
};


#define MAX_WEIGHTS 4
struct VertexWeights
{
	UINT	boneIdx[MAX_WEIGHTS];
	float	boneWeights[MAX_WEIGHTS];
	VertexWeights()
	{
		ZeroMemory(boneIdx, sizeof(UINT) * MAX_WEIGHTS);
		ZeroMemory(boneWeights, sizeof(float) * MAX_WEIGHTS);
	}
	void AddData(UINT boneId, float weight)
	{
		for (UINT i = 0; i < MAX_WEIGHTS; i++)
		{
			if (boneWeights[i] == 0.0f)
			{
				boneIdx[i] = boneId;
				boneWeights[i] = weight;
				return;
			}
		}
	}
	void Normalize()
	{
		float total = 0.0f;
		for (UINT i = 0; i < MAX_WEIGHTS; i++)
		{
			if (boneWeights[i] != 0.0f)
			{
				total += boneWeights[i];
			}
		}
		for (UINT i = 0; i < MAX_WEIGHTS; i++)
		{
			if (boneWeights[i] != 0.0f)
			{
				boneWeights[i] /= total;
			}
		}
	}
};