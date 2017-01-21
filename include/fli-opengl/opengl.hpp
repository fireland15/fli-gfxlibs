#pragma once

#include <map>

#include <glew\glew.h>
#include <GL\GL.h>

#include "context.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "opengl_error.hpp"

namespace opengl {

	class GL {
	private:

	public:
		enum Buffers : GLbitfield {
			Color			= GL_COLOR_BUFFER_BIT,
			Depth			= GL_DEPTH_BUFFER_BIT,
			Accumulation	= GL_ACCUM_BUFFER_BIT,
			Stencil			= GL_STENCIL_BUFFER_BIT
		};

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

		OpenGlError GetErrors() {
			return OpenGlError((OpenGlError::Error)glGetError());
		}

		void ClearColor(glm::vec4 color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void Clear(GLbitfield buffers) {
			glClear(buffers);
		}
		
	};

}