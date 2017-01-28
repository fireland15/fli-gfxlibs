#include "program_factory.hpp"

namespace opengl {

	inline void CompileShader(Shader& shader, ShaderSource& source);

	inline void CleanShaders(Program& program, const std::vector<Shader>& shaders);

	inline void DetachShaders(Program& program, const std::vector<Shader>& shaders);

	inline void DeleteShaders(const std::vector<Shader>& shaders);

	// Throws opengl::shader_compilation_exception when compilation fails.
	void CompileShader(Shader& shader, ShaderSource& source) {
		shader.SetSource(source);
		if (!shader.Compile()) {
			std::stringstream ss; 
			ss << "Compilation of shader failed." << std::endl;
			ss << "\t" << shader.GetErrors() << std::endl;
			GL::DeleteShader(shader);
			throw shader_compilation_exception(ss.str());
		}
	}

	void CleanShaders(Program& program, const std::vector<Shader>& shaders) {
		DetachShaders(program, shaders);
		DeleteShaders(shaders);
	}

	void DetachShaders(Program& program, const std::vector<Shader>& shaders) {
		for (Shader shader : shaders) {
			program.Detach(shader);
		}
	}

	void DeleteShaders(const std::vector<Shader>& shaders) {
		for (Shader shader : shaders) {
			GL::DeleteShader(shader);
		}
	}

	Shader ProgramFactory::CreateVertexShader(ShaderSource source) {
		Shader shader = GL::CreateShader(Shader::Type::Vertex);
		CompileShader(shader, source);
		return shader;
	}

	Shader ProgramFactory::CreateFragmentShader(ShaderSource source) {
		Shader shader = GL::CreateShader(Shader::Type::Fragment);
		CompileShader(shader, source);
		return shader;
	}

	Program ProgramFactory::CreateProgram(const std::vector<Shader>& shaders) {
		Program program = GL::CreateProgram();

		for (Shader shader : shaders) {
			program.Attach(shader);
		}

		if (!program.Link()) {
			std::stringstream ss;
			ss << "Program linking failed." << std::endl;
			ss << "\t" << program.GetErrors() << std::endl;

			CleanShaders(program, shaders);

			GL::DeleteProgram(program);

			throw program_link_exception(ss.str());
		}

		CleanShaders(program, shaders);

		return program;
	}

}