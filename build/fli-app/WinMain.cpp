#include <iostream>
#include <functional>
#include <sstream>

#define _WIN32_LEAN_AND_MEAN
#define GLEW_STATIC

#include <Windows.h>

#include <fli-core\clock.hpp>
#include <fli-core\scene.hpp>
#include <fli-render\window.hpp>
#include <fli-opengl\context.hpp>
#include <fli-opengl\opengl.hpp>
#include <fli-opengl\buffer.hpp>
#include <glm\glm.hpp>

opengl::VertexArray vao;
opengl::Buffer vbo;
opengl::GL gl;
opengl::OpenGlContext context;
opengl::Program program;
opengl::Shader vertexShader;
opengl::Shader fragmentShader;

std::string vertexSourceString =
"#version 330\n"\
"layout(location = 0) in vec3 position;\n"\
"void main() {\n"\
"gl_Position.xyz = position;\n"\
"gl_Position.w = 1.0;\n"\
"}\n";

std::string fragmentSourceString =
"#version 330\n"\
"out vec4 color;\n"\
"void main() {\n"\
"color = vec4(1,0,0,0.5);\n"\
"}\n";

glm::vec3 vertices[3] = {
	glm::vec3(-1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
};

void Setup(opengl::GL& gl) {
	wglSwapIntervalEXT(0);

	opengl::ShaderSource vertexSource;
	vertexSource.AddSource(vertexSourceString);
	std::cout << gl.GetErrors().ToString() << std::endl;

	opengl::ShaderSource fragmentSource;
	fragmentSource.AddSource(fragmentSourceString);
	std::cout << gl.GetErrors().ToString() << std::endl;

	vertexShader = gl.CreateShader(opengl::Shader::Type::Vertex);
	fragmentShader = gl.CreateShader(opengl::Shader::Type::Fragment);
	std::cout << gl.GetErrors().ToString() << std::endl;

	vertexShader.SetSource(vertexSource);
	fragmentShader.SetSource(fragmentSource);
	std::cout << gl.GetErrors().ToString() << std::endl;

	if (!vertexShader.Compile()) {
		std::cout << vertexShader.GetErrors() << std::endl;
		vbo.Unbind();
		vao.Unbind();
		gl.DeleteShader(vertexShader);
		gl.DeleteShader(fragmentShader);
		gl.DeleteBuffer(vbo);
		gl.DeleteVertexArray(vao);
		exit(-1);
	}
	std::cout << gl.GetErrors().ToString() << std::endl;

	if (!fragmentShader.Compile()) {
		std::cout << fragmentShader.GetErrors() << std::endl;
		vbo.Unbind();
		vao.Unbind();
		gl.DeleteShader(vertexShader);
		gl.DeleteShader(fragmentShader);
		gl.DeleteBuffer(vbo);
		gl.DeleteVertexArray(vao);
		exit(-1);
	}
	std::cout << gl.GetErrors().ToString() << std::endl;

	program = gl.CreateProgram();
	std::cout << gl.GetErrors().ToString() << std::endl;
	program.Attach(vertexShader);
	program.Attach(fragmentShader);
	std::cout << gl.GetErrors().ToString() << std::endl;

	if (!program.Link()) {
		std::cout << program.GetErrors() << std::endl;
		program.Detach(vertexShader);
		program.Detach(fragmentShader);
		vbo.Unbind();
		vao.Unbind();
		gl.DeleteShader(vertexShader);
		gl.DeleteShader(fragmentShader);
		gl.DeleteProgram(program);
		gl.DeleteBuffer(vbo);
		gl.DeleteVertexArray(vao);
		exit(-1);
	}

	program.Detach(vertexShader);
	program.Detach(fragmentShader);
	std::cout << gl.GetErrors().ToString() << std::endl;

	gl.DeleteShader(vertexShader);
	gl.DeleteShader(fragmentShader);
	std::cout << gl.GetErrors().ToString() << std::endl;

	opengl::AttributeVariable position = program.GetAttributeVariable("position");
	
	vao = gl.CreateVertexArray();
	std::cout << gl.GetErrors().ToString() << std::endl;
	vbo = gl.CreateBuffer(opengl::Buffer::Targets::ArrayBuffer);
	std::cout << gl.GetErrors().ToString() << std::endl;
	vao.Bind();
	vbo.Bind();

	opengl::Buffer::DataDescriptor dataDesc;
	dataDesc.Type = opengl::Buffer::DataType::Float;
	dataDesc.Normalize = opengl::Buffer::Normalize::No;
	dataDesc.AttributeSize = opengl::Buffer::AttribSize::Three;
	dataDesc.Stride = 0;
	dataDesc.Offset = 0;

	opengl::Buffer::Descriptor desc;
	desc.DataDescriptions.push_back(dataDesc);
	desc.pData = &vertices;
	desc.Size = sizeof(vertices);
	desc.Target = opengl::Buffer::Targets::ArrayBuffer;
	desc.Usage = opengl::Buffer::Usages::StaticDraw;

	vbo.SetData(desc);

	vao.EnableVertexAttribute(position);
	vao.SetVertexAttributePointer(position, dataDesc);

	vbo.Unbind();
	vao.Unbind();
}

void Render() {
	program.Use();
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao.Unbind();
}

int main() {
	std::cout.sync_with_stdio(false);
	HINSTANCE hInstance = GetModuleHandle(0);
	gfx::render::Window w(hInstance, "fli-app-1", glm::uvec2(100, 100), glm::uvec2(300, 300));

	opengl::OpenGlContext* c = w.GetOpenGlContext();
	Setup(gl);

	gfx::core::Clock clock;
	gfx::core::Clock::Timepoint t = clock.Now();
	gfx::core::Clock::Duration d = clock.TimeFromEpoch(t);

	int i = 0;

	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);

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