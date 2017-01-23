#pragma once

#include <map>

#include "static_mesh.hpp"
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

		StaticMesh CreateStaticMesh(const MeshDescriptor& desc);

	private:

		
	};

}