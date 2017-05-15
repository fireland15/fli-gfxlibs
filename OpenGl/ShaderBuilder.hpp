#pragma once

#include <memory>
#include <list>

#include "IShaderBuilder.hpp"
#include "ShaderSource.hpp"
#include "Handle.hpp"
#include <ShaderTypeEnum.hpp>

namespace OpenGL {

	class OpenGLWrapper;

	class ShaderBuilder : public IShaderBuilder {
	public:
		ShaderBuilder(OpenGLWrapper & gl);
		virtual ~ShaderBuilder() { }
		virtual IShaderBuilder & NewShader() override;
		virtual IShaderBuilder & Type(ShaderType type) override;
		virtual IShaderBuilder & AddSource(ShaderSource source) override;
		virtual IShaderBuilder & Compile() override;
		virtual std::unique_ptr<IShader> Build() override;
	private:
		OpenGLWrapper& _gl;

		std::unique_ptr<Handle> _handle;
		std::list<ShaderSource> _sources;
		ShaderType _type;
	};

}