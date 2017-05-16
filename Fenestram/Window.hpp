#pragma once

struct GLFWwindow;
namespace OpenGL {
	class OpenGlContext;
	class OpenGLWrapper;
	class IOpenGL;
}

namespace Fenestram {

	class Window {
	public:
		Window(GLFWwindow* window);
		~Window();

		OpenGL::OpenGlContext& GetContext();

		bool ShouldClose() const;
		void ShouldClose(bool shouldClose);

		void SwapBuffers();

	private:
		GLFWwindow* _glfwWindow;

		OpenGL::IOpenGL* _gl;
		OpenGL::OpenGLWrapper* _glWrapper;
		OpenGL::OpenGlContext* _glContext;
		bool _shouldClose;
	};

}