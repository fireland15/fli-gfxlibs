#pragma once

#include <vector>

#include <glm\glm.hpp>

namespace opengl {

	class StaticMesh {
	public:
		StaticMesh(std::vector<glm::vec3> vertexPositions);

		void AddNormals(std::vector<glm::vec3> vertexNormals);

		void AddColors(std::vector<glm::vec3> vertexColors);

		void AddUVCoords(std::vector<glm::vec2> vertexTexCoords);

		void GenerateBuffers();

		void SetBuffers

	private:

	};

}