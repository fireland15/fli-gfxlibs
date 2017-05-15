#pragma once

#include <list>
#include <functional>

#include "IProgramBuilder.hpp"

#include "IProgram.hpp"

namespace OpenGL {

	class IShader;
	class OpenGLWrapper;

	class ProgramBuilder : public IProgramBuilder {
	public:
		ProgramBuilder(OpenGLWrapper& gl);
		virtual ~ProgramBuilder();
		virtual IProgramBuilder& NewProgram();
		virtual IProgramBuilder& Attach(IShader& shader);
		virtual std::unique_ptr<IProgram> Build();

	private:
		OpenGLWrapper& _gl;
		std::list<std::reference_wrapper<IShader>> _shaders;
	};

}