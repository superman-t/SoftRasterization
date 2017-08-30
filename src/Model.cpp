#include "Model.h"
#include <fstream>
#include <sstream>
#include "TextureManager.h"

namespace SoftRender
{ 
	Model::Model(std::string path, Vec3f worldPos, Material m):path(path), pos(worldPos),material(m)
	{
		loadModel(path);
	}

	void Model::loadModel(string path)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs|aiProcess_GenNormals);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return ;
		}
 
		directory = path.substr(0, path.find_last_of('/'));

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
		std::vector<Texture> ambientTextures;
		std::vector<Texture> diffuseTextures;
		std::vector<Texture> specularTextures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			if (mesh->HasPositions())
				vertex.modelPos = Vec3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			if (mesh->HasNormals())
				vertex.normal = Vec3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
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
			if (face.mNumIndices != 3)
				std::cout << face.mNumIndices;
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if(mesh->mMaterialIndex > 0)
		{
			aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

			//环境光贴图
			std::vector<Texture> ambientMaps = loadMaterialTextures(mat, 
				aiTextureType_AMBIENT, "texture_ambient");
			ambientTextures.insert(ambientTextures.end(), ambientMaps.begin(), ambientMaps.end());


			//漫反射贴图
			std::vector<Texture> diffuseMaps = loadMaterialTextures(mat, 
				aiTextureType_DIFFUSE, "texture_diffuse");
			diffuseTextures.insert(diffuseTextures.end(), diffuseMaps.begin(), diffuseMaps.end());

			//镜面贴图
			vector<Texture> specularMaps = loadMaterialTextures(mat, 
				aiTextureType_SPECULAR, "texture_specular");
			specularTextures.insert(specularTextures.end(), specularMaps.begin(), specularMaps.end());
// 
// 			std::vector<Texture> normalMaps = loadMaterialTextures(material, 
// 				aiTextureType_HEIGHT, "texture_normal");
// 			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
// 
// 			std::vector<Texture> heightMaps = loadMaterialTextures(material, 
// 				aiTextureType_AMBIENT, "texture_height");
// 			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}
		return Mesh(vertices, indices, ambientTextures, diffuseTextures, specularTextures);
		//return Mesh(vertices, indices, std::make_shared<Texture>(texture));
	}

	vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		std::cout << typeName << " "<< mat->GetTextureCount(type) << std::endl;
		for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture;
			std::string path(str.C_Str());
			if (path.find("materials") != string::npos)
				path = path.substr(path.find("materials"), path.length());
			TextureFromFile(texture, path, directory);
			texture.type = typeName;
			texture.path = string(directory + "/" + path)  ;
			textures.push_back(texture);
		}
		return textures;
	}

	/*
	* 获取一个材质中的纹理
	*/
	unsigned int Model::TextureFromFile(Texture& texture, const string& path, const string& directory)
	{
		string filename = directory + "/" + path;
		std::cout << "texture " << filename << std::endl;
		TextureManager::getInstance()->LoadTexture(texture, filename);
		return 0;
	}


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
