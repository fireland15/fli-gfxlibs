#pragma once

#include <vector>

#include <GL\glew.h>
#include <GL\GL.h>

#include "shader_source.hpp"

namespace opengl {

	class Shader {
	public:
		enum Type : GLenum {
			Vertex					= GL_VERTEX_SHADER,
			TesselationControl		= GL_TESS_CONTROL_SHADER,
			TesselationEvaluation	= GL_TESS_EVALUATION_SHADER,
			Geometry				= GL_GEOMETRY_SHADER,
			Fragment				= GL_FRAGMENT_SHADER,
			Compute					= GL_COMPUTE_SHADER
		};

	private:
		Shader(GLuint obj);

		GLuint Obj();

		void Obj(GLuint);

		void SetSource();

	public:
		Shader();

		void SetSource(ShaderSource source);

		bool Compile();

		bool HasErrors();

		std::string GetErrors();

		friend class GL;
		friend class Program;

	private:
		GLuint m_obj;
		ShaderSource m_source;
		bool m_hasErrors;
		std::string m_errors;
	};

}