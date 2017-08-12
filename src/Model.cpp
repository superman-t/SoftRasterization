#pragma once
#include "Model.h"
#include <fstream>
#include <sstream>

namespace SoftRender
{
	Model::Model(std::string path, Vec3f& worldPos, Material m):material(m),path(path), pos(worldPos)
	{
		loadModel(path+".obj");
	}

	//only obj file
	void Model::loadModel(std::string path)
	{
		float x, y, z;
		char dummy;
		std::ifstream is (path);
		std::string data;
		std::vector<Vec4f> normalBuffer, posBuffer;
		std::vector<Vec2f> uvBuffer;
		std::vector<Index> indexBuffer;
		
		while (std::getline (is, data)) {
			if (data.length () < 2) continue;
			if (data.find("mtllib") != std::string::npos){
				int begin = data.find_first_of(" ")+1;
				texturename = data.substr(begin);
				texturename = texturename.replace(texturename.find_last_of("."), 4, ".bmp");
				
			}
			std::istringstream iss (data);
			std::string token;
			if (data[1] == 't' && data[0] == 'v') { // load uv. "vt -0.05 0.0972793"
				iss >> token >> x >> y;
				uvBuffer.push_back (Vec2f(x, y));
			} else if (data[1] == 'n' && data[0] == 'v') { // load normal. "vn -0.981591 -0.162468 0.100411"
				iss >> token >> x >> y >> z;
				normalBuffer.push_back (Vec4f(x, y, z));
			} else if (data[0] == 'v') { // load postion. "v -0.983024 -0.156077 0.0964607"
				iss >> token >> x >> y >> z;
				posBuffer.push_back (Vec4f(x, y, z));
			} else if (data[0] == 'f') { // load index. keep in mind that uv/normal index are optional.
				Index index = { { -1 } };
				if (data.find ("//") != std::string::npos) { // pos//normal, no uv. "f 181//176 182//182 209//208"
					iss >> token >> index.pos[0] >> dummy >> dummy >> index.normal[0] >>
						index.pos[1] >> dummy >> dummy >> index.normal[1] >>
						index.pos[2] >> dummy >> dummy >> index.normal[2];
				} else {
					size_t count = 0, pos = data.find ('/');
					while (pos != std::string::npos) { count++; pos = data.find ('/', pos + 1); }
					if (count == 6) { // "f 181/292/176 182/250/182 209/210/208"
						iss >> token >> index.pos[0] >> dummy >> index.uv[0] >> dummy >> index.normal[0] >>
							index.pos[1] >> dummy >> index.uv[1] >> dummy >> index.normal[1] >>
							index.pos[2] >> dummy >> index.uv[2] >> dummy >> index.normal[2];
					} else if (count == 3) { // pos/uv, no normal. "f 181/176 182/182 209/208"
						iss >> token >> index.pos[0] >> dummy >> index.uv[0] >> index.pos[1] >> dummy >> index.uv[1] >> index.pos[2] >> dummy >> index.uv[2];
					}
				}
				//std::cout << index.pos[0] << index.pos[1] << index.pos[2] 
				//<< index.uv[0] << index.uv[0] << index.uv[0]<<  std::endl;

				indexBuffer.push_back (index);
			}
		} // end parsing
		if (!texturename.empty()) // load texture only if the model has uv data.
			LoadBmp (texture, "res/"+texturename);
		setupMesh(uvBuffer, normalBuffer, posBuffer, indexBuffer);
	} // obj is a text base model format

	void Model::setupMesh(std::vector<Vec2f>& uvBuffer, std::vector<Vec4f>& normalBuffer, std::vector<Vec4f>& posBuffer,
		std::vector<Index>& indexBuffer)
	{
		//set up mesh
		for (auto &index : indexBuffer) {
			std::vector<Vertex> vertexs;
			std::vector<unsigned short> indices;
			for (int i = 0; i < 3; i++) {
				Vertex vertex;
				if ( posBuffer.size() >0 ) vertex.pos =posBuffer[(index.pos[i]-1)%posBuffer.size()];
				if ( uvBuffer.size() > 0) vertex.uv = uvBuffer[(index.uv[i]-1)%uvBuffer.size()];
				//vertex.normal = normalBuffer.size()>0 ? normalBuffer[index.normal[i]%normalBuffer.size()] : Vec4f();
				vertexs.push_back(vertex);
				indices.push_back(i);
			} 
			meshes.push_back(Mesh(vertexs, indices, std::make_shared<Texture>(texture)));
		}
	}

}
