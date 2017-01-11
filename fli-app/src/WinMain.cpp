#define GLEW_STATIC

#include <Windows.h>

#include <Window.h>
#include <OpenGlContext.h>
#include <glm.hpp>

void Render() {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
	glEnd();
	glPopMatrix();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdStr, int nCmdStr) {
	fli::gfx::render::Window w(hInstance, "Title", glm::uvec2(100, 100), glm::uvec2(200, 200));
	w.Create(hInstance);
	fli::gfx::render::OpenGlContext context(w);

	while (!w.ShouldClose()) {
		w.ProcessMessages();
		Render();
		context.Present();
	}
	context.Present();

	PostQuitMessage(0);
}