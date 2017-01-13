#include <iostream>
#include <functional>

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <fli-render\window.hpp>
#include <fli-render\opengl_context.hpp>
#include <glm\glm.hpp>

void Render() {
	glPushMatrix();
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
	glEnd();
	glPopMatrix();
}

void HandleMessages(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		std::cout << "Closing Window" << std::endl;
		break;
	case WM_DESTROY:
		std::cout << "Closing Window" << std::endl;
		break;
	default:
		break;
	}
}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app", glm::uvec2(100, 100), glm::uvec2(300, 300));

	gfx::render::OpenGlContext* c = w.GetOpenGlContext();
	std::function<void(UINT, WPARAM, LPARAM)>* func = new std::function<void(UINT, WPARAM, LPARAM)>(HandleMessages);
	w.SetMsgCallback(func);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while (!w.ShouldClose()) {
		w.ProcessMessages();
		Render();
		c->SwapBuffer();
	}

	delete func;
}