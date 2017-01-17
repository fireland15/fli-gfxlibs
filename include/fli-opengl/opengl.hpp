#pragma once

#include <map>

#include <GL\glew.h>
#include <GL\GL.h>

#include "context.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "program.hpp"

namespace opengl {

	class GL {
	private:

	public:
		GL(OpenGlContext context);

		VertexArray CreateVertexArray() {
			GLuint obj;
			glGenVertexArrays(1, &obj);
			return VertexArray(obj);
		}

		void DeleteVertexArray(VertexArray& vao) {
			GLuint obj = vao.Obj();
			glDeleteVertexArrays(1, &obj);
			vao.Obj(0);
		}

		Buffer CreateBuffer(Buffer::Targets target) {
			GLuint obj;
			glGenBuffers(1, &obj);
			return Buffer(obj, target);
		}

		void DeleteBuffer(Buffer& buffer) {
			GLuint obj = buffer.Obj();
			glDeleteBuffers(1, &obj);
			buffer.Obj(0);
		}

		Shader CreateShader(Shader::Type type) {
			GLuint obj = glCreateShader(type);
			return Shader(obj);
		}

		void DeleteShader(Shader& shader) {
			GLuint obj = shader.Obj();
			glDeleteShader(obj);
			shader.Obj(0);
		}

		Program CreateProgram() {
			GLuint obj = glCreateProgram();
			return Program(obj);
		}

		void DeleteProgram(Program& program) {
			GLuint obj = program.Obj();
			glDeleteProgram(obj);
			program.Obj(0);
		}
		
	};

}