#pragma once

#include <map>

#include "static_mesh.hpp"
#include "static_instanced_mesh.hpp"
#include "mesh_descriptor.hpp"
#include "opengl.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"

namespace opengl {

	class MeshFactory {
	public:
		MeshFactory() = default;
		MeshFactory(const MeshFactory& other) = delete;
		MeshFactory(MeshFactory&& other) = delete;
		MeshFactory operator=(const MeshFactory& other) = delete;
		MeshFactory operator=(MeshFactory&& other) = delete;

		static StaticMesh CreateStaticMesh(const MeshDescriptor& desc);

		static StaticInstancedMesh CreateStaticInstancedMesh(const MeshDescriptor& desc, std::vector<VertexAttributeDescriptor>& instancedAttributeDescriptor);

		static void ReleaseMesh(StaticMesh& mesh);

		static void ReleaseMesh(StaticInstancedMesh& mesh);
	
	private:

		
	};

}