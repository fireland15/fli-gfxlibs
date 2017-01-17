#pragma once

#include <GL\glew.h>
#include <GL\GL.h>

namespace opengl {

	class VertexArray {
	private:
		GLuint m_vao;

		VertexArray(GLuint obj);

		GLuint Obj();

		void Obj(GLuint);

	public:
		VertexArray();



		friend class GL;
	};

}