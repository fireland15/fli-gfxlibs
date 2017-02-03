#include "mesh_factory.hpp"

namespace opengl {

	namespace mesh_factory {

		void ConvertAttributeType(AttributeVariable::AttribType attribType, gl::BufferDataType* type, gl::BufferAttribSize* size) {
			switch (attribType) {
			case AttributeVariable::AttribType::Float:
				*type = gl::BufferDataType::Float;
				*size = gl::BufferAttribSize::One;
				break;
			case AttributeVariable::AttribType::Vec2f:
				*type = gl::BufferDataType::Float;
				*size = gl::BufferAttribSize::Two;
				break;
			case AttributeVariable::AttribType::Vec3f:
				*type = gl::BufferDataType::Float;
				*size = gl::BufferAttribSize::Three;
				break;
			case AttributeVariable::AttribType::Vec4f:
				*type = gl::BufferDataType::Float;
				*size = gl::BufferAttribSize::Four;
				break;
			case AttributeVariable::AttribType::Int:
				*type = gl::BufferDataType::Int;
				*size = gl::BufferAttribSize::One;
				break;
			case AttributeVariable::AttribType::Vec2i:
				*type = gl::BufferDataType::Int;
				*size = gl::BufferAttribSize::Two;
				break;
			case AttributeVariable::AttribType::Vec3i:
				*type = gl::BufferDataType::Int;
				*size = gl::BufferAttribSize::Three;
				break;
			case AttributeVariable::AttribType::Vec4i:
				*type = gl::BufferDataType::Int;
				*size = gl::BufferAttribSize::Four;
				break;
			case AttributeVariable::AttribType::UnsignedInt:
				*type = gl::BufferDataType::UnsignedInt;
				*size = gl::BufferAttribSize::One;
				break;
			case AttributeVariable::AttribType::Vec2u:
				*type = gl::BufferDataType::UnsignedInt;
				*size = gl::BufferAttribSize::Two;
				break;
			case AttributeVariable::AttribType::Vec3u:
				*type = gl::BufferDataType::UnsignedInt;
				*size = gl::BufferAttribSize::Three;
				break;
			case AttributeVariable::AttribType::Vec4u:
				*type = gl::BufferDataType::UnsignedInt;
				*size = gl::BufferAttribSize::Four;
				break;
			case AttributeVariable::AttribType::Double:
				*type = gl::BufferDataType::Double;
				*size = gl::BufferAttribSize::One;
				break;
			case AttributeVariable::AttribType::Vec2d:
				*type = gl::BufferDataType::Double;
				*size = gl::BufferAttribSize::Two;
				break;
			case AttributeVariable::AttribType::Vec3d:
				*type = gl::BufferDataType::Double;
				*size = gl::BufferAttribSize::Three;
				break;
			case AttributeVariable::AttribType::Vec4d:
				*type = gl::BufferDataType::Double;
				*size = gl::BufferAttribSize::Four;
				break;
			case AttributeVariable::AttribType::Mat2f:
			case AttributeVariable::AttribType::Mat3f:
			case AttributeVariable::AttribType::Mat4f:
			case AttributeVariable::AttribType::Mat2x3f:
			case AttributeVariable::AttribType::Mat2x4f:
			case AttributeVariable::AttribType::Mat3x2f:
			case AttributeVariable::AttribType::Mat3x4f:
			case AttributeVariable::AttribType::Mat4x2f:
			case AttributeVariable::AttribType::Mat4x3f:
			case AttributeVariable::AttribType::Mat2d:
			case AttributeVariable::AttribType::Mat3d:
			case AttributeVariable::AttribType::Mat4d:
			case AttributeVariable::AttribType::Mat2x3d:
			case AttributeVariable::AttribType::Mat2x4d:
			case AttributeVariable::AttribType::Mat3x2d:
			case AttributeVariable::AttribType::Mat3x4d:
			case AttributeVariable::AttribType::Mat4x2d:
			case AttributeVariable::AttribType::Mat4x3d:
				throw std::exception("Matrix vertex attributes are not supported");
				break;
			}
		}

		StaticMesh* CreateStaticMesh(const MeshDescriptor& desc) {
			unsigned int numVertices = (unsigned int)desc.Vertices.size();

			std::vector<up_Buffer> vertexBuffers;

			up_VertexArray vao(new VertexArray());
			if (!vao->IsValid()) {
				throw objection_creation_exception("Failed to create a valid VertexArray.");
			}
			vao->Bind();

			BufferDataDescriptor positionDesc;
			positionDesc.Type = gl::BufferDataType::Float;
			positionDesc.Normalize = gl::Normalize::No;
			positionDesc.AttributeSize = gl::BufferAttribSize::Three;
			positionDesc.Stride = 0;
			positionDesc.Offset = 0;

			BufferDescriptor vboDesc;
			vboDesc.DataDescriptions.push_back(positionDesc);
			vboDesc.Target = gl::BufferTarget::ArrayBuffer;
			vboDesc.Usage = gl::BufferUsage::StaticDraw;

			up_Buffer vbo(new Buffer(vboDesc));
			if (!vbo->IsValid()) {
				throw objection_creation_exception("Failed to create a valid Buffer.");
			}
			vbo->Bind();

			vbo->SetData((void*)glm::value_ptr(desc.Vertices[0]), sizeof(glm::vec3) * desc.Vertices.size());

			vao->EnableVertexAttribute(desc.PositionVariable);
			vao->SetVertexAttributePointer(desc.PositionVariable, positionDesc);

			vbo->Unbind();

			vertexBuffers.push_back(std::move(vbo));

			for (VertexAttributeDescriptor attribDesc : desc.AttributeDescriptors) {
				BufferDataDescriptor dataDesc;
				ConvertAttributeType(attribDesc.AttributeVariable.Type(), &dataDesc.Type, &dataDesc.AttributeSize);
				dataDesc.Normalize = gl::Normalize::No;
				dataDesc.Offset = 0;
				dataDesc.Stride = 0;

				BufferDescriptor buffDesc;
				buffDesc.DataDescriptions.push_back(dataDesc);
				buffDesc.Target = gl::BufferTarget::ArrayBuffer;
				buffDesc.Usage = gl::BufferUsage::StaticDraw;

				up_Buffer buffer(new Buffer(buffDesc));
				if (!buffer->IsValid()) {
					throw objection_creation_exception("Failed to create a valid Buffer.");
				}
				buffer->Bind();

				buffer->SetData(attribDesc.pAttributes, attribDesc.Size);

				vao->EnableVertexAttribute(attribDesc.AttributeVariable);
				vao->SetVertexAttributePointer(attribDesc.AttributeVariable, dataDesc);

				buffer->Unbind();

				vertexBuffers.push_back(std::move(buffer));
			}

			vao->Unbind();

			return new StaticMesh(numVertices, std::move(vao), std::move(vertexBuffers));
		}

		StaticInstancedMesh* CreateStaticInstancedMesh(
			const MeshDescriptor& desc,
			std::vector<VertexAttributeDescriptor>& instancedAttributeDescriptors) {

			unsigned int numVertices = (unsigned int)desc.Vertices.size();

			std::vector<up_Buffer> vertexBuffers;
			std::map<AttributeVariable, up_Buffer, AttributeComparator> instanceBuffers;

			up_VertexArray vao(new VertexArray());
			if (!vao->IsValid()) {
				throw objection_creation_exception("Failed to create a valid VertexArray.");
			}
			vao->Bind();

			BufferDataDescriptor positionDesc;
			positionDesc.Type = gl::BufferDataType::Float;
			positionDesc.Normalize = gl::Normalize::No;
			positionDesc.AttributeSize = gl::BufferAttribSize::Three;
			positionDesc.Stride = 0;
			positionDesc.Offset = 0;

			BufferDescriptor vboDesc;
			vboDesc.DataDescriptions.push_back(positionDesc);
			vboDesc.Target = gl::BufferTarget::ArrayBuffer;
			vboDesc.Usage = gl::BufferUsage::StaticDraw;

			up_Buffer vbo(new Buffer(vboDesc));
			if (!vbo->IsValid()) {
				throw objection_creation_exception("Failed to create a valid Buffer.");
			}
			vbo->Bind();

			vbo->SetData((void*)glm::value_ptr(desc.Vertices[0]), sizeof(glm::vec3) * desc.Vertices.size());

			vao->EnableVertexAttribute(desc.PositionVariable);
			vao->SetVertexAttributePointer(desc.PositionVariable, positionDesc);

			vbo->Unbind();

			vertexBuffers.push_back(std::move(vbo));

			for (VertexAttributeDescriptor attribDesc : desc.AttributeDescriptors) {
				BufferDataDescriptor dataDesc;
				ConvertAttributeType(attribDesc.AttributeVariable.Type(), &dataDesc.Type, &dataDesc.AttributeSize);
				dataDesc.Normalize = gl::Normalize::No;
				dataDesc.Offset = 0;
				dataDesc.Stride = 0;

				BufferDescriptor buffDesc;
				buffDesc.DataDescriptions.push_back(dataDesc);
				buffDesc.Target = gl::BufferTarget::ArrayBuffer;
				buffDesc.Usage = gl::BufferUsage::StaticDraw;

				up_Buffer buffer(new Buffer(buffDesc));
				if (!buffer->IsValid()) {
					throw objection_creation_exception("Failed to create a valid Buffer.");
				}
				buffer->Bind();

				buffer->SetData(attribDesc.pAttributes, attribDesc.Size);

				vao->EnableVertexAttribute(attribDesc.AttributeVariable);
				vao->SetVertexAttributePointer(attribDesc.AttributeVariable, dataDesc);

				buffer->Unbind();

				vertexBuffers.push_back(std::move(buffer));
			}

			for (VertexAttributeDescriptor attribDesc : instancedAttributeDescriptors) {
				BufferDataDescriptor dataDesc;
				ConvertAttributeType(attribDesc.AttributeVariable.Type(), &dataDesc.Type, &dataDesc.AttributeSize);
				dataDesc.Normalize = gl::Normalize::No;
				dataDesc.Offset = 0;
				dataDesc.Stride = 0;

				BufferDescriptor buffDesc;
				buffDesc.DataDescriptions.push_back(dataDesc);
				buffDesc.Target = gl::BufferTarget::ArrayBuffer;
				buffDesc.Usage = gl::BufferUsage::DynamicDraw;

				up_Buffer buffer(new Buffer(buffDesc));
				if (!buffer->IsValid()) {
					throw objection_creation_exception("Failed to create a valid Buffer.");
				}
				buffer->Bind();
				
				vao->EnableVertexAttribute(attribDesc.AttributeVariable);
				vao->SetVertexAttributePointer(attribDesc.AttributeVariable, dataDesc);
				vao->SetVertexAttributeDivisor(attribDesc.AttributeVariable, 1);

				buffer->Unbind();

				instanceBuffers.insert(std::move(std::make_pair(attribDesc.AttributeVariable, std::move(buffer))));
			}

			vao->Unbind();

			return new StaticInstancedMesh(numVertices, std::move(vao), std::move(vertexBuffers), std::move(instanceBuffers));
		}

	}
}