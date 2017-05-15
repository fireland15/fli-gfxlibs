#pragma once

namespace OpenGL {

	class AttributeVariable;
	class IBuffer;
	class BufferDataPointer;
	class Handle;

	class IVertexArray {
	public:
		virtual ~IVertexArray() { }
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void EnableVertexAttribute(const AttributeVariable& var) = 0;
		virtual void DisableVertexAttribute(const AttributeVariable& var) = 0;
		virtual void SetVertexAttributePointer(const AttributeVariable& var, IBuffer& buffer, const BufferDataPointer& ptr) = 0;
		virtual const OpenGL::Handle& Handle() = 0;
	};

}