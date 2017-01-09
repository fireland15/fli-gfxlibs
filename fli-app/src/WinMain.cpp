#include <Windows.h>

#include <Window.h>
#include <glm.hpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdStr, int nCmdStr) {
	fli::gfx::render::Window w(std::string("Title"), glm::uvec2(100, 100), glm::uvec2(200, 200));

	w.Create(hInstance);
	w.Show();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}