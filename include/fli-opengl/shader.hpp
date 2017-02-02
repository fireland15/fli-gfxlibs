#pragma once

#include <vector>
#include <memory>

#include "opengl.hpp"
#include "shader_source.hpp"

namespace opengl {

	class Shader {
	private:

		void SetSource();

	public:

		/*************************************************************
		* Constructors
		**************************************************************/

		Shader(gl::ShaderType type);

		Shader(const Shader& other) = delete;

		Shader& operator=(const Shader& other) = delete;

		Shader(Shader&& other);

		Shader& operator=(Shader&& other);

		/*************************************************************
		* Destructor
		**************************************************************/

		~Shader();

		/*************************************************************
		* OpenGL Shader Methods
		**************************************************************/

		void SetSource(ShaderSource source);

		bool Compile();

		bool HasErrors();

		std::string GetErrors();

		friend class Program;

	private:
		GLuint m_obj;

		gl::ShaderType m_type;

		ShaderSource m_source;

		bool m_hasErrors;

		std::string m_errors;
	};

	typedef std::unique_ptr<Shader> up_Shader;

}