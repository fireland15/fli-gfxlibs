#pragma once

#include <memory>

#include "IVertexArray.hpp"

#include <Handle.hpp>

namespace OpenGL {

	class OpenGLWrapper;

	class VertexArray : public IVertexArray {
	public:
		VertexArray(OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle);
		virtual ~VertexArray() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void EnableVertexAttribute(const AttributeVariable& var) override;
		virtual void DisableVertexAttribute(const AttributeVariable& var) override;
		virtual void SetVertexAttributePointer(const AttributeVariable& var, IBuffer& buffer, const BufferDataPointer& ptr) override;
		virtual const OpenGL::Handle& Handle() override;

	private:
		OpenGLWrapper& _gl;
		std::unique_ptr<OpenGL::Handle> _handle;
	};

}