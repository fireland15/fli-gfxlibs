#include "mesh_factory.hpp"

namespace opengl {

	void ConvertAttributeType(AttributeVariable::AttribType attribType, Buffer::DataType* type, Buffer::AttribSize* size) {
		switch (attribType) {
		case AttributeVariable::AttribType::Float:
			*type = Buffer::DataType::Float;
			*size = Buffer::AttribSize::One;
			break;
		case AttributeVariable::AttribType::Vec2f:
			*type = Buffer::DataType::Float;
			*size = Buffer::AttribSize::Two;
			break;
		case AttributeVariable::AttribType::Vec3f:
			*type = Buffer::DataType::Float;
			*size = Buffer::AttribSize::Three;
			break;
		case AttributeVariable::AttribType::Vec4f:
			*type = Buffer::DataType::Float;
			*size = Buffer::AttribSize::Four;
			break;
		case AttributeVariable::AttribType::Int:
			*type = Buffer::DataType::Int;
			*size = Buffer::AttribSize::One;
			break;
		case AttributeVariable::AttribType::Vec2i:
			*type = Buffer::DataType::Int;
			*size = Buffer::AttribSize::Two;
			break;
		case AttributeVariable::AttribType::Vec3i:
			*type = Buffer::DataType::Int;
			*size = Buffer::AttribSize::Three;
			break;
		case AttributeVariable::AttribType::Vec4i:
			*type = Buffer::DataType::Int;
			*size = Buffer::AttribSize::Four;
			break;
		case AttributeVariable::AttribType::UnsignedInt:
			*type = Buffer::DataType::UnsignedInt;
			*size = Buffer::AttribSize::One;
			break;
		case AttributeVariable::AttribType::Vec2u:
			*type = Buffer::DataType::UnsignedInt;
			*size = Buffer::AttribSize::Two;
			break;
		case AttributeVariable::AttribType::Vec3u:
			*type = Buffer::DataType::UnsignedInt;
			*size = Buffer::AttribSize::Three;
			break;
		case AttributeVariable::AttribType::Vec4u:
			*type = Buffer::DataType::UnsignedInt;
			*size = Buffer::AttribSize::Four;
			break;
		case AttributeVariable::AttribType::Double:
			*type = Buffer::DataType::Double;
			*size = Buffer::AttribSize::One;
			break;
		case AttributeVariable::AttribType::Vec2d:
			*type = Buffer::DataType::Double;
			*size = Buffer::AttribSize::Two;
			break;
		case AttributeVariable::AttribType::Vec3d:
			*type = Buffer::DataType::Double;
			*size = Buffer::AttribSize::Three;
			break;
		case AttributeVariable::AttribType::Vec4d:
			*type = Buffer::DataType::Double;
			*size = Buffer::AttribSize::Four;
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

	StaticMesh MeshFactory::CreateStaticMesh(const MeshDescriptor& desc) {
		unsigned int numVertices = (unsigned int)desc.Vertices.size();

		std::vector<Buffer> vertexBuffers;

		VertexArray vao = GL::CreateVertexArray();
		vao.Bind();

		Buffer vbo = GL::CreateBuffer(Buffer::Targets::ArrayBuffer);
		vbo.Bind();

		Buffer::DataDescriptor positionDesc;
		positionDesc.Type = Buffer::DataType::Float;
		positionDesc.Normalize = Buffer::Normalize::No;
		positionDesc.AttributeSize = Buffer::AttribSize::Three;
		positionDesc.Stride = 0;
		positionDesc.Offset = 0;

		Buffer::Descriptor vboDesc;
		vboDesc.DataDescriptions.push_back(positionDesc);
		vboDesc.pData = (void*)&(desc.Vertices[0]);
		vboDesc.Size = sizeof(glm::vec3) * desc.Vertices.size();
		vboDesc.Target = Buffer::Targets::ArrayBuffer;
		vboDesc.Usage = Buffer::Usages::StaticDraw;

		vbo.SetData(vboDesc);

		vao.EnableVertexAttribute(desc.PositionVariable);
		vao.SetVertexAttributePointer(desc.PositionVariable, positionDesc);

		vbo.Unbind();

		vertexBuffers.push_back(vbo);

		for (VertexAttributeDescriptor attribDesc : desc.AttributeDescriptors) {
			Buffer buffer = GL::CreateBuffer(Buffer::Targets::ArrayBuffer);
			buffer.Bind();

			Buffer::DataDescriptor dataDesc;
			ConvertAttributeType(attribDesc.AttributeVariable.Type(), &dataDesc.Type, &dataDesc.AttributeSize);
			dataDesc.Normalize = Buffer::Normalize::No;
			dataDesc.Offset = 0;
			dataDesc.Stride = 0;

			Buffer::Descriptor buffDesc;
			buffDesc.DataDescriptions.push_back(dataDesc);
			buffDesc.pData = attribDesc.pAttributes;
			buffDesc.Size = attribDesc.Size;
			buffDesc.Target = Buffer::Targets::ArrayBuffer;
			buffDesc.Usage = Buffer::Usages::StaticDraw;

			vbo.SetData(buffDesc);

			vao.EnableVertexAttribute(attribDesc.AttributeVariable);
			vao.SetVertexAttributePointer(attribDesc.AttributeVariable, dataDesc);

			buffer.Unbind();

			vertexBuffers.push_back(buffer);
		}

		return StaticMesh(numVertices, vao, vertexBuffers);
	}

	StaticInstancedMesh MeshFactory::CreateStaticInstancedMesh(const MeshDescriptor& desc, std::vector<VertexAttributeDescriptor>& instancedAttributeDescriptor) {
		unsigned int numVertices = (unsigned int)desc.Vertices.size();
	}

}