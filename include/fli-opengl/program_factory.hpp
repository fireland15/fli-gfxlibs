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

	namespace program_factory { 
		// Throws opengl::shader_compilation_error when compilation fails.
		up_Shader CreateVertexShader(ShaderSource source);
		
		// Throws opengl::shader_compilation_error when compilation fails.
		up_Shader CreateFragmentShader(ShaderSource source);

		// Throws opengl::program_link_error when program linking fails.
		up_Program CreateProgram(std::vector<up_Shader>& shaders);
	}

}
