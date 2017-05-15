#pragma once

#include "ITexture.hpp"
#include <memory>
#include <TextureTargetEnum.hpp>

namespace OpenGL {

	class OpenGLWrapper;

	class Texture : public ITexture {
	public:
		Texture(OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle, TextureTarget target);
		virtual ~Texture() { }
		virtual const OpenGL::Handle & Handle() override;
		virtual TextureTarget Target() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetWrapS(TextureParameterValue value) override;
		virtual void SetWrapT(TextureParameterValue value) override;
		virtual void SetMagFilter(TextureParameterValue value) override;
		virtual void SetMinFilter(TextureParameterValue value) override;
		virtual void BindToSlot(unsigned int slot) override;

	private:
		OpenGLWrapper& _gl;
		std::unique_ptr<OpenGL::Handle> _handle;
		TextureTarget _target;
	};

}