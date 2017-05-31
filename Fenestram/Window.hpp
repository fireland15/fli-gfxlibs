#pragma once

#include <functional>

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

		void SetKeyCallback(std::function<void(int, int, int, int)> callback);
		void PollEvents();

		void SwapBuffers();

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		GLFWwindow* _glfwWindow;

		OpenGL::IOpenGL* _gl;
		OpenGL::OpenGLWrapper* _glWrapper;
		OpenGL::OpenGlContext* _glContext;
		bool _shouldClose;
		std::function<void(int, int, int, int)> _keyCallback;
	};

}