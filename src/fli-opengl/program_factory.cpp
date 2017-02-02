#include "program_factory.hpp"

namespace opengl {

	namespace program_factory {

		inline void CompileShader(Shader* shader, ShaderSource& source);

		// Throws opengl::shader_compilation_exception when compilation fails.
		void CompileShader(Shader* shader, ShaderSource& source) {
			shader->SetSource(source);
			if (!shader->Compile()) {
				std::stringstream ss;
				ss << "Compilation of shader failed." << std::endl;
				ss << "\t" << shader->GetErrors() << std::endl;
				throw shader_compilation_exception(ss.str());
			}
		}

		up_Shader CreateVertexShader(ShaderSource source) {
			up_Shader shader(new Shader(gl::ShaderType::Vertex));
			CompileShader(shader.get(), source);
			return shader;
		}

		up_Shader CreateFragmentShader(ShaderSource source) {
			up_Shader shader(new Shader(gl::ShaderType::Fragment));
			CompileShader(shader.get(), source);
			return shader;
		}

		up_Program CreateProgram(std::vector<up_Shader>& shaders) {
			up_Program program(new Program());

			for (up_Shader& shader : shaders) {
				program->Attach(std::move(shader));
			}

			if (!program->Link()) {
				std::stringstream ss;
				ss << "Program linking failed." << std::endl;
				ss << "\t" << program->GetErrors() << std::endl;

				program->DetachAndDeleteAllShaders();

				throw program_link_exception(ss.str());
			}

			program->DetachAndDeleteAllShaders();

			return program;
		}

	}

}