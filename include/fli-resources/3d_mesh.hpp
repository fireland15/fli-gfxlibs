#pragma once

#include <vector>
#include <glm\glm.hpp>

#include "vertex.hpp"
#include "triangle.hpp"
#include "obj_file.hpp"

namespace gfx {
	namespace resources {

		template<typename TVertex>
		class Mesh {
		private:
			std::vector<TVertex> m_vertices;

		public:
			void Add(Triangle<TVertex> triangle) {
				for (unsigned int i = 0; i < 3; i++) {
					m_vertices.push_back(triangle.vertex[i]);
				}
			}

			TVertex* GetVertices() {
				return &m_vertices[0];
			}

			int GetSizeInBytes() {
				return m_vertices.size() * sizeof(TVertex);
			}

			static Mesh CreateMesh(ObjFile file) {

			}
		};

	}
}