#include <iostream>
#include <functional>

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <fli-core\clock.hpp>
#include <fli-render\window.hpp>
#include <fli-render\opengl_context.hpp>
#include <fli-render\simple_render_system.hpp>
#include <fli-render\opengl_error.hpp>
#include <fli-render\vertex_array_object.hpp>
#include <fli-render\vertex_buffer_object.hpp>
#include <fli-render\vertex_buffer_object_usage_enum.hpp>
#include <fli-utility\config_reader.hpp>
#include <fli-utility\logger_base.hpp>
#include <fli-utility\logger_simple.hpp>
#include <glm\glm.hpp>

gfx::render::VertexArrayObject* vao;
gfx::render::VertexBufferObject* vbo;

glm::vec3 vertices[3] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
};

void Setup() {
	vao = new gfx::render::VertexArrayObject();
	vbo = new gfx::render::VertexBufferObject(gfx::render::eVertexBufferObjectTarget::ArrayBuffer);
	gfx::render::VertexBufferObjectDataDescriptor dataDesc;
	dataDesc.DataType = gfx::render::eBufferDataType::Float;
	dataDesc.ShouldNormalize = gfx::render::eNormalize::ShouldNotNormalize;
	dataDesc.Size = sizeof(vertices);
	dataDesc.Offset = 0;
	dataDesc.Stride = 0;
	gfx::render::VertexBufferObjectDescriptor desc;
	desc.AddData(dataDesc);

	vao->AttachBuffer(*vbo, desc);
}

void Render() {

}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app-1", glm::uvec2(100, 100), glm::uvec2(300, 300));

	gfx::render::OpenGlContext* c = w.GetOpenGlContext();

	gfx::core::Clock clock;
	gfx::core::Clock::Timepoint t = clock.Now();
	gfx::core::Clock::Duration d = clock.TimeFromEpoch(t);

	Setup();

	gfx::render::OpenGlError err = OpenGlCheckErrors();
	if (err.IsError()) {
		std::cout << err.ToString() << std::endl;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	int i = 0;
	gfx::core::Scene scene;

	while (i++, !w.ShouldClose()) {
		w.ProcessMessages();

		Render();

		d = clock.TimeFromNow(t);
		if (i % 1000 == 0) {
			float s = d.Seconds();
			//std::cout << 1000 / s << std::endl;
		}
		t = clock.Now();
	}

}