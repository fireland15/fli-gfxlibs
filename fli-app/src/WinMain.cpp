#define GLEW_STATIC

#include <Windows.h>

#include <Window.h>
#include <OpenGlContext.h>
#include <glm.hpp>

float theta = 0.0f;

void Render() {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(theta, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
	glEnd();
	glPopMatrix();

	theta += 0.05f;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdStr, int nCmdStr) {
	fli::gfx::render::Window w(hInstance, "Title", glm::uvec2(100, 100), glm::uvec2(200, 200));
	fli::gfx::render::OpenGlContext* context = w.GetOpenGlContext();

	while (!w.ShouldClose()) {
		w.ProcessMessages();
		Render();
		context->Present();
	}

	PostQuitMessage(0);
}