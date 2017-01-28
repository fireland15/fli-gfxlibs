#pragma once

#include <string>
#include <sstream>

#include "opengl.hpp"
#include "opengl_error.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "shader_source.hpp"
#include "exceptions.hpp"

namespace opengl {

	class ProgramFactory {
	public:
		// Throws opengl::shader_compilation_error when compilation fails.
		static Shader CreateVertexShader(ShaderSource source);
		
		// Throws opengl::shader_compilation_error when compilation fails.
		static Shader CreateFragmentShader(ShaderSource source);

		// Throws opengl::program_link_error when program linking fails.
		static Program CreateProgram(const std::vector<Shader>& shaders);
	};

}
