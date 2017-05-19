#pragma once

#include <vector>
#include <glm\glm.hpp>

namespace Auxili {

	class ObjFileData {
	public:
		struct VertexIndices {
			int Vertex;
			int Normal;
			int TexCoord;
		};

		struct Face {
			VertexIndices& operator[](unsigned int index);
		private:
			VertexIndices _v[3];
		};

		ObjFileData();
		void AddVertex(glm::vec3& v);
		void AddNormal(glm::vec3& n);
		void AddTexCoord(glm::vec2& t);
		void AddFace(Face& f);

		std::vector<glm::vec3> & Vertices();
		std::vector<glm::vec3> & Normals();
		std::vector<glm::vec2> & TexCoords();
		std::vector<Face> & Faces();

	private:
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec3> _normals;
		std::vector<glm::vec2> _texCoords;
		std::vector<Face> _faces;
	};

}