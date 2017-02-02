#pragma once

#include <map>
#include <iostream>

#include "static_mesh.hpp"
#include "static_instanced_mesh.hpp"
#include "mesh_descriptor.hpp"
#include "opengl.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"
#include "exceptions.hpp"

namespace opengl {

	namespace mesh_factory {

		StaticMesh* CreateStaticMesh(const MeshDescriptor& desc);

		StaticInstancedMesh* CreateStaticInstancedMesh(
			const MeshDescriptor& desc, 
			std::vector<VertexAttributeDescriptor>& instancedAttributeDescriptor);

	}

}