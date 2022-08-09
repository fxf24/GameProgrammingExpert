#include "stdafx.h"
#include "Main.h"


Main::Main()
{

}

Main::~Main()
{

}

void Main::Init()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Cam->Release();
    Grid->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Cam->RenderHierarchy();
    Grid->RenderHierarchy();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->RenderHierarchy();
    }

    //Cam->RenderHierarchy();
    ImGui::End();

    ImGui::Begin("AssimpImporter");

    if (GUI->FileImGui("AssimpImporter", "Importer",
        ".fbx,.obj,.x", "../Assets"))
    {
		file = ImGuiFileDialog::Instance()->GetCurrentFileName();
        string path = "../Assets/" + file;
        
        Assimp::Importer importer; //지역변수로 선언된 객체

        scene = importer.ReadFile
        (
			path,
            aiProcess_ConvertToLeftHanded
            | aiProcess_Triangulate
            | aiProcess_GenUVCoords
            | aiProcess_GenNormals
            | aiProcess_CalcTangentSpace
        );
        assert(scene != NULL and "Import Error");

        actor = Actor::Create(scene->mRootNode->mName.C_Str());
		actor->shader = RESOURCE->shaders.Load("4.cube.hlsl");
		actor->skeleton = new Skeleton();
		actor->boneIndex = 0;

		GameObject* offset = GameObject::Create("Offset");
		offset->shader = RESOURCE->shaders.Load("4.cube.hlsl");
		actor->AddBone(offset);

		ReadMaterial();

        ReadNode(offset, scene->mRootNode);
        
		{
			int tok = file.find_last_of(".");
			string checkPath = "../Contents/Skeleton/" + file.substr(0, tok);
			if (!PathFileExistsA(checkPath.c_str()))
			{
				CreateDirectoryA(checkPath.c_str(), NULL);
			}

			string filePath = file.substr(0, tok) + "/";
			actor->skeleton->file = filePath + file.substr(0, tok) + ".skel";
			actor->skeleton->SaveFile(actor->skeleton->file);
		}
		ReadMesh(offset, scene->mRootNode);
		
		
		List.push_back(actor);

		importer.FreeScene();
    }
    ImGui::End();

    Cam->Update();
    Grid->Update();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->Update();
    }
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    Cam->Set();
    Grid->Render();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->Render();
    }
}

void Main::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}

void Main::ReadMaterial()
{
	for (UINT i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* srcMtl = scene->mMaterials[i];
		Material* destMtl = new Material();
		aiColor3D tempColor;
		//이름 -키값
		destMtl->file = srcMtl->GetName().C_Str();
		//ambient
		srcMtl->Get(AI_MATKEY_COLOR_AMBIENT, tempColor);
		destMtl->ambient.x = tempColor.r;
		destMtl->ambient.y = tempColor.g;
		destMtl->ambient.z = tempColor.b;

		//diffuse
		srcMtl->Get(AI_MATKEY_COLOR_DIFFUSE, tempColor);
		destMtl->diffuse.x = tempColor.r;
		destMtl->diffuse.y = tempColor.g;
		destMtl->diffuse.z = tempColor.b;

		//specular
		srcMtl->Get(AI_MATKEY_COLOR_SPECULAR, tempColor);
		destMtl->specular.x = tempColor.r;
		destMtl->specular.y = tempColor.g;
		destMtl->specular.z = tempColor.b;

		//emissive
		srcMtl->Get(AI_MATKEY_COLOR_EMISSIVE, tempColor);
		destMtl->emissive.x = tempColor.r;
		destMtl->emissive.y = tempColor.g;
		destMtl->emissive.z = tempColor.b;

		//Shininess
		srcMtl->Get(AI_MATKEY_SHININESS, destMtl->shininess);
		//opacity
		srcMtl->Get(AI_MATKEY_OPACITY, destMtl->opacity);

		//Normal
		{
			aiString aifile;
			string TextureFile;
			aiReturn texFound;
			texFound = srcMtl->GetTexture(aiTextureType_NORMALS, 0, &aifile);
			TextureFile = aifile.C_Str();
			size_t index = TextureFile.find_last_of('/');
			TextureFile = TextureFile.substr(index + 1, TextureFile.length());

			//텍스쳐가 있다.
			if (texFound == AI_SUCCESS && file != "")
			{
				destMtl->ambient.w = 1.0f;
				destMtl->normalMap = make_shared<Texture>();

				size_t tok = file.find_last_of(".");
				string checkPath = "../Contents/Texture/" + file.substr(0, tok);
				if (!PathFileExistsA(checkPath.c_str()))
				{
					CreateDirectoryA(checkPath.c_str(), NULL);
				}
				string orgin = "../Assets/" + TextureFile;
				string copy = "../Contents/Texture/" + file.substr(0, tok) + "/" + TextureFile;
				bool isCheck = true;
				CopyFileA(orgin.c_str(), copy.c_str(), isCheck);

				destMtl->normalMap->LoadFile(file.substr(0, tok) + "/" + TextureFile);

			}
		}

		//Diffuse
		{
			aiString aifile;
			string TextureFile;
			aiReturn texFound;
			texFound = srcMtl->GetTexture(aiTextureType_DIFFUSE, 0, &aifile);
			TextureFile = aifile.C_Str();
			size_t index = TextureFile.find_last_of('/');
			TextureFile = TextureFile.substr(index + 1, TextureFile.length());

			//텍스쳐가 있다.
			if (texFound == AI_SUCCESS && file != "")
			{
				destMtl->diffuse.w = 1.0f;
				destMtl->diffuseMap = make_shared<Texture>();

				size_t tok = file.find_last_of(".");
				string checkPath = "../Contents/Texture/" + file.substr(0, tok);
				if (!PathFileExistsA(checkPath.c_str()))
				{
					CreateDirectoryA(checkPath.c_str(), NULL);
				}
				string orgin = "../Assets/" + TextureFile;
				string copy = "../Contents/Texture/" + file.substr(0, tok) + "/" + TextureFile;
				bool isCheck = true;
				CopyFileA(orgin.c_str(), copy.c_str(), isCheck);

				destMtl->diffuseMap->LoadFile(file.substr(0, tok) + "/" + TextureFile);

			}
		}

		//specular
		{
			aiString aifile;
			string TextureFile;
			aiReturn texFound;
			texFound = srcMtl->GetTexture(aiTextureType_SPECULAR, 0, &aifile);
			TextureFile = aifile.C_Str();
			size_t index = TextureFile.find_last_of('/');
			TextureFile = TextureFile.substr(index + 1, TextureFile.length());

			//텍스쳐가 있다.
			if (texFound == AI_SUCCESS && file != "")
			{
				destMtl->specular.w = 1.0f;
				destMtl->specularMap = make_shared<Texture>();

				size_t tok = file.find_last_of(".");
				string checkPath = "../Contents/Texture/" + file.substr(0, tok);
				if (!PathFileExistsA(checkPath.c_str()))
				{
					CreateDirectoryA(checkPath.c_str(), NULL);
				}
				string orgin = "../Assets/" + TextureFile;
				string copy = "../Contents/Texture/" + file.substr(0, tok) + "/" + TextureFile;
				bool isCheck = true;
				CopyFileA(orgin.c_str(), copy.c_str(), isCheck);

				destMtl->specularMap->LoadFile(file.substr(0, tok) + "/" + TextureFile);

			}
		}

		//emissive
		{
			aiString aifile;
			string TextureFile;
			aiReturn texFound;
			texFound = srcMtl->GetTexture(aiTextureType_SHININESS, 0, &aifile);
			TextureFile = aifile.C_Str();
			size_t index = TextureFile.find_last_of('/');
			TextureFile = TextureFile.substr(index + 1, TextureFile.length());

			//텍스쳐가 있다.
			if (texFound == AI_SUCCESS && file != "")
			{
				destMtl->emissive.w = 1.0f;
				destMtl->emissiveMap = make_shared<Texture>();

				size_t tok = file.find_last_of(".");
				string checkPath = "../Contents/Texture/" + file.substr(0, tok);
				if (!PathFileExistsA(checkPath.c_str()))
				{
					CreateDirectoryA(checkPath.c_str(), NULL);
				}
				string orgin = "../Assets/" + TextureFile;
				string copy = "../Contents/Texture/" + file.substr(0, tok) + "/" + TextureFile;
				bool isCheck = true;
				CopyFileA(orgin.c_str(), copy.c_str(), isCheck);

				destMtl->emissiveMap->LoadFile(file.substr(0, tok) + "/" + TextureFile);

			}
		}

		size_t tok = file.find_last_of(".");
		string checkPath = "../Contents/Material/" + file.substr(0, tok);
		if (!PathFileExistsA(checkPath.c_str()))
		{
			CreateDirectoryA(checkPath.c_str(), NULL);
		}

		string filePath = file.substr(0, tok) + "/";
		destMtl->file = filePath + destMtl->file + ".mtl";
		destMtl->SaveFile(destMtl->file);
	}
}

void Main::ReadNode(GameObject* dest, aiNode* src)
{
    Matrix tempMat = ToMatrix(src->mTransformation);
    Vector3 s, r, t; Quaternion q;
    tempMat.Decompose(s, q, t);
    r = Util::QuaternionToYawPtichRoll(q);
    dest->scale = s; dest->rotation = r; dest->SetLocalPos(t);

	actor->Update();
	//로컬로 향하는 행렬값 넣기
	actor->skeleton->bonesOffset[dest->boneIndex] = dest->W.Invert();

    //자식노드들로 재귀호출
    for (UINT i = 0; i < src->mNumChildren; i++)
    {
        GameObject* temp =
            GameObject::Create(src->mChildren[i]->mName.C_Str());
        dest->AddBone(temp);
        //temp->mesh = RESOURCE->meshes.Load("2.Sphere.mesh");
        temp->shader = RESOURCE->shaders.Load("4.cube.hlsl");
        ReadNode(temp, src->mChildren[i]);
    }

}

void Main::ReadMesh(GameObject* dest, aiNode* src)
{

	for (UINT i = 0; i < src->mNumMeshes; i++)
	{
		UINT index = src->mMeshes[i];
		aiMesh* srcMesh = scene->mMeshes[index];
		vector<VertexModel>		VertexList;
		vector<VertexWeights>	VertexWeights;
		vector<UINT> indexList;
		string mtlFile = scene->mMaterials[srcMesh->mMaterialIndex]->GetName().C_Str();
		string meshFile = src->mName.C_Str();
		int tok = file.find_last_of(".");
		string filePath = file.substr(0, tok) + "/";
		mtlFile = filePath + mtlFile + ".mtl";

		//1:1 대응 배열
		VertexList.resize(srcMesh->mNumVertices);
		VertexWeights.resize(srcMesh->mNumVertices);


		ReadBoneData(srcMesh, VertexWeights);

		for (UINT j = 0; j < VertexList.size(); j++)
		{
			memcpy(&VertexList[j].position, &srcMesh->mVertices[j], sizeof(Vector3));
			if (srcMesh->HasTextureCoords(0))
				memcpy(&VertexList[j].uv, &srcMesh->mTextureCoords[0][j], sizeof(Vector2));
			if (srcMesh->HasNormals())
				memcpy(&VertexList[j].normal, &srcMesh->mNormals[j], sizeof(Vector3));
			if (srcMesh->HasTangentsAndBitangents())
				memcpy(&VertexList[j].tangent, &srcMesh->mTangents[j], sizeof(Vector3));

			//본데이터가 있을때
			if (!VertexWeights.empty())
			{
				VertexWeights[j].Normalize();

				VertexList[j].indices.x = (float)VertexWeights[j].boneIdx[0];
				VertexList[j].indices.y = (float)VertexWeights[j].boneIdx[1];
				VertexList[j].indices.z = (float)VertexWeights[j].boneIdx[2];
				VertexList[j].indices.w = (float)VertexWeights[j].boneIdx[3];

				VertexList[j].weights.x = VertexWeights[j].boneWeights[0];
				VertexList[j].weights.y = VertexWeights[j].boneWeights[1];
				VertexList[j].weights.z = VertexWeights[j].boneWeights[2];
				VertexList[j].weights.w = VertexWeights[j].boneWeights[3];
			}

		}//정점 저장 끝
		UINT IndexCount = srcMesh->mNumFaces;
		for (UINT j = 0; j < IndexCount; j++)
		{
			aiFace& face = srcMesh->mFaces[j];
			for (UINT k = 0; k < face.mNumIndices; k++)
			{
				indexList.emplace_back(face.mIndices[k]);
			}
		}
		VertexModel* VertexArray = new VertexModel[VertexList.size()];
		copy(VertexList.begin(), VertexList.end(), stdext::checked_array_iterator<VertexModel*>(VertexArray, VertexList.size()));

		UINT* IndexArray = new UINT[indexList.size()];
		copy(indexList.begin(), indexList.end(), stdext::checked_array_iterator<UINT*>(IndexArray, indexList.size()));

		if (i == 0)
		{
			dest->mesh = make_shared<Mesh>(VertexArray, VertexList.size(),
				IndexArray, indexList.size(), VertexType::MODEL);
			dest->material = RESOURCE->materials.Load(mtlFile);

			{
				int tok = file.find_last_of(".");
				string checkPath = "../Contents/Mesh/" + file.substr(0, tok);
				if (!PathFileExistsA(checkPath.c_str()))
				{
					CreateDirectoryA(checkPath.c_str(), NULL);
				}

				string filePath = file.substr(0, tok) + "/";
				dest->mesh->file = filePath + meshFile + ".mesh";
				dest->mesh->SaveFile(dest->mesh->file);
			}

		}
		else
		{
			string Name = srcMesh->mName.C_Str() + string("MeshObject");
			GameObject* temp = GameObject::Create(Name);
			dest->AddChild(temp);
			temp->mesh = make_shared<Mesh>(VertexArray, VertexList.size(),
				IndexArray, indexList.size(), VertexType::MODEL);
			temp->shader = RESOURCE->shaders.Load("4.Model.hlsl");
			temp->material = RESOURCE->materials.Load(mtlFile);

			{
				int tok = file.find_last_of(".");
				string checkPath = "../Contents/Mesh/" + file.substr(0, tok);
				if (!PathFileExistsA(checkPath.c_str()))
				{
					CreateDirectoryA(checkPath.c_str(), NULL);
				}

				string filePath = file.substr(0, tok) + "/";
				temp->mesh->file = filePath + meshFile + ".mesh";
				temp->mesh->SaveFile(temp->mesh->file);
			}
		}
	}
	for (UINT i = 0; i < src->mNumChildren; i++)
	{
		ReadMesh(dest->children[src->mChildren[i]->mName.C_Str()],
			src->mChildren[i]);
	}
}

void Main::ReadBoneData(aiMesh* mesh, vector<VertexWeights>& vertexWeights)
{
	//메쉬가 가지고 있는 본 개수 만큼
	for (UINT i = 0; i < mesh->mNumBones; i++)
	{
		//현재본이 하이어라이키에서 몇번째 인덱스인가?
		string boneName = mesh->mBones[i]->mName.C_Str();
		int boneIndex = actor->Find(boneName)->boneIndex;
		for (UINT j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			UINT vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
			vertexWeights[vertexID].AddData(boneIndex, mesh->mBones[i]->mWeights[j].mWeight);
		}
	}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Game1");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();
    int wParam = (int)WIN->Run(main);
    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}