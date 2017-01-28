#include <iostream>
#include <functional>
#include <sstream>

#define _WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <fli-core\clock.hpp>
#include <fli-core\scene.hpp>
#include <fli-render\window.hpp>
#include <fli-opengl\context.hpp>
#include <fli-opengl\opengl.hpp>
#include <fli-opengl\buffer.hpp>
#include <fli-opengl\mesh_factory.hpp>
#include <fli-opengl\mesh_descriptor.hpp>
#include <fli-opengl\static_mesh.hpp>
#include <fli-opengl\vertex_attribute_descriptor.hpp>
#include <fli-opengl\program_factory.hpp>
#include <glm\glm.hpp>

opengl::GL gl;
opengl::OpenGlContext context;
opengl::Program program;
opengl::Shader vertexShader;
opengl::Shader fragmentShader;
opengl::MeshFactory meshFactory;
opengl::StaticMesh mesh;

std::string vertexSourceString =
"#version 430\n"\
"layout(location = 0) in vec3 position;\n"\
"layout(location = 3) in vec4 color;\n"\
"layout(location = 4) uniform vec4 ucolor;\n"\
"out vec4 vColor;\n"\
"void main() {\n"\
"gl_Position.xyz = position;\n"\
"gl_Position.w = 1.0;\n"\
"vColor = color + ucolor;\n"\
"}\n";

std::string fragmentSourceString =
"#version 430\n"\
"in vec4 vColor;\n"\
"out vec4 fColor;\n"\
"layout(location = 4) uniform vec4 ucolor;\n"\
"void main() {\n"\
"fColor = vColor;\n"\
"}\n";

glm::vec3 vertices[3] = {
	glm::vec3(-1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
};

glm::vec4 colors[3] = {
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
};

glm::vec4 color = glm::vec4(0.99f, 0.99f, 0.99f, 0.99f);
float dColor = 0.00005f;
opengl::UniformVariable& ucolor = opengl::UniformVariable();

bool Setup() {
	wglSwapIntervalEXT(0);

	opengl::ShaderSource vertexSource;
	vertexSource.AddSource(vertexSourceString);

	opengl::ShaderSource fragmentSource;
	fragmentSource.AddSource(fragmentSourceString);

	try {
		vertexShader = opengl::ProgramFactory::CreateVertexShader(vertexSource);
		fragmentShader = opengl::ProgramFactory::CreateFragmentShader(fragmentSource);
		program = opengl::ProgramFactory::CreateProgram({ vertexShader, fragmentShader });
	}
	catch (opengl::shader_compilation_exception ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
	catch (opengl::program_link_exception ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}

	const opengl::AttributeVariable& position = program.GetAttributeVariable("position");
	const opengl::AttributeVariable& color = program.GetAttributeVariable("color");
	ucolor = program.GetUniformVariable("ucolor");

	opengl::MeshDescriptor meshDesc;
	meshDesc.Vertices = std::vector<glm::vec3>(vertices, std::end(vertices));
	meshDesc.PositionVariable = position;

	opengl::VertexAttributeDescriptor colorDesc;
	colorDesc.pAttributes = &colors[0];
	colorDesc.Size = sizeof(colors);
	colorDesc.AttributeVariable = color;
	meshDesc.AttributeDescriptors.push_back(colorDesc);

	mesh = meshFactory.CreateStaticMesh(meshDesc);
	
	for (const opengl::AttributeVariable& var : program.AttributeVariables()) {
		std::cout << var.Name() << std::endl;
	}
}

void Render() {
	program.Use();

	if (color.x < 0.25f || color.x > 1.0f) {
		dColor *= -1;
	}

	color.x = color.x - dColor;
	color.y = color.y - dColor;
	color.z = color.z - dColor;

	program.SetUniform(ucolor, color);
	mesh.Render();
}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app-1", glm::uvec2(100, 100), glm::uvec2(300, 300));

	opengl::OpenGlContext* c = w.GetOpenGlContext();
	if (!Setup()) {
		return (-1);
	}

	gfx::core::Clock clock;
	gfx::core::Clock::Timepoint t = clock.Now();
	gfx::core::Clock::Duration d = clock.TimeFromEpoch(t);

	int i = 0;

	glClearColor(0.0f, 1.0f, 1.0f, 0.5f);

	while (i++, !w.ShouldClose()) {
		w.ProcessMessages();

		gl.Clear(opengl::GL::Buffers::Color | opengl::GL::Buffers::Depth);

		Render();
		c->SwapBuffer();

		d = clock.TimeFromNow(t);
		if (i % 1000 == 0) {
			double s = d.Seconds();
			std::stringstream ss;
			ss << "fps: " << 1.0 / s;
			SetWindowText(w.GetHWnd(), TEXT(ss.str().c_str()));
		}
		t = clock.Now();
	}

}