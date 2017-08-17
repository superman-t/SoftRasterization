#include "Model.h"
#include <fstream>
#include <sstream>

namespace SoftRender
{
	Model::Model(std::string path, Vec3f worldPos, Material m):material(m),path(path), pos(worldPos)
	{
		loadModel(path);
	}

	void Model::loadModel(string path)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate|aiProcess_GenNormals);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return ;
		}

		directory = path.substr(0, path.find_last_of('/'));
		texturename = path.replace(path.find_last_of("."), 4, ".bmp");
		LoadTexture(texture, texturename);

		processNode(scene->mRootNode, scene);
	}



	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			if (mesh->HasPositions())
				vertex.pos = Vec4f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			if (mesh->HasNormals())
				vertex.normal = Vec4f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			if (mesh->mTextureCoords[0])
			{
				vertex.uv = Vec2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}else
			{
				vertex.uv = Vec2f();
			}
			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if(mesh->mMaterialIndex > 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material, 
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material, 
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, std::make_shared<Texture>(texture));
	}

	vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture;
// 			texture.id = TextureFromFile(str.C_Str(), directory);
// 			texture.type = typeName;
// 			texture.path = str;
			textures.push_back(texture);
		}
		return textures;
	}

	/*
	* 获取一个材质中的纹理
	*/
	bool Model::processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr, 
		const aiTextureType textureType, std::vector<Texture>& textures)
	{
		textures.clear();

		if (!matPtr 
			|| !sceneObjPtr )
		{
			return false;
		}
		if (matPtr->GetTextureCount(textureType) <= 0)
		{
			return true;
		}
		for (size_t i = 0; i < matPtr->GetTextureCount(textureType); ++i)
		{
			Texture text;
			aiString textPath;
			aiReturn retStatus = matPtr->GetTexture(textureType, i, &textPath);
			if (retStatus != aiReturn_SUCCESS 
				|| textPath.length == 0)
			{
				std::cerr << "Warning, load texture type=" << textureType
					<< "index= " << i << " failed with return value= "
					<< retStatus << std::endl;
				continue;
			}
			std::string absolutePath = directory + "/" + textPath.C_Str();
// 			LoadedTextMapType::const_iterator it = this->loadedTextureMap.find(absolutePath);
// 			if (it == this->loadedTextureMap.end()) // 检查是否已经加载过了
// 			{
// 				GLuint textId = TextureHelper::load2DTexture(absolutePath.c_str());
// 				text.id = textId;
// 				text.path = absolutePath;
// 				text.type = textureType;
// 				textures.push_back(text);
// 				loadedTextureMap[absolutePath] = text;
// 			}
// 			else
// 			{
// 				textures.push_back(it->second);
// 			}
		}
		return true;
	}

}
