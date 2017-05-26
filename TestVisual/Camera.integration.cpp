#include "Camera.integration.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include <OpenGlFacade\RealOpenGL.hpp>
#include <OpenGlFacade\OpenGLWrapper.hpp>
#include <Fenestram\WindowManager.hpp>
#include <Fenestram\Window.hpp>
#include <OpenGl\BufferDataPointer.hpp>
#include <OpenGl\OpenGlContext.hpp>
#include <OpenGl\IBufferBuilder.hpp>
#include <OpenGl\IBufferDataBuilder.hpp>
#include <OpenGl\IShaderBuilder.hpp>
#include <OpenGl\ShaderSource.hpp>
#include <OpenGl\IProgramBuilder.hpp>
#include <OpenGl\IProgram.hpp>
#include <OpenGl\IVertexArray.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Camera.hpp"

void UsesCamera() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(1000, 1000), std::string("Draw Colored Triangle"));
	auto & context = window->GetContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;

	std::vector<glm::vec4> verts;
	verts.emplace_back(-0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.0f, 0.5f, 0.0f, 1.0f);

	std::vector<glm::vec4> colors;
	colors.emplace_back(1.0f, 0.0f, 0.0f, 1.0f);
	colors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
	colors.emplace_back(0.0f, 0.0f, 1.0f, 1.0f);

	OpenGL::BufferDataPointer vertsPointer(4, OpenGL::DataType::Float);
	OpenGL::BufferDataPointer colorPointer(4, OpenGL::DataType::Float);

	auto buf = context.NewBuffer([&](OpenGL::IBufferBuilder& b) {
		b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::ArrayBuffer)
			.UsedFor(OpenGL::BufferUsage::StaticDraw)
			.WithData([&](OpenGL::IBufferDataBuilder& db) {
			db.Data(glm::value_ptr(verts.front()), sizeof(glm::vec4), verts.size(), vertsPointer)
				.InterleavedWith(glm::value_ptr(colors.front()), sizeof(glm::vec4), colors.size(), colorPointer);
		});
	});

	auto vshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "layout(location = 0) in vec4 pos;" << std::endl;
		ss << "layout(location = 1) in vec4 color;" << std::endl;
		ss << "uniform mat4 view;" << std::endl;
		ss << "uniform mat4 projection;" << std::endl;
		ss << "out vec4 vColor;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "vColor = color;" << std::endl;
		ss << "\tgl_Position = projection * view * pos;" << std::endl;
		ss << "}" << std::endl;
		OpenGL::ShaderSource vsource(ss);

		sb.AddSource(vsource).Type(OpenGL::ShaderType::Vertex);
	});

	auto fshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "in vec4 vColor;" << std::endl;
		ss << "out vec4 color;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "\tcolor = vColor;" << std::endl;
		ss << "}" << std::endl;
		OpenGL::ShaderSource fsource(ss);

		sb.AddSource(fsource).Type(OpenGL::ShaderType::Fragment);
	});

	auto program = context.NewProgram([&](OpenGL::IProgramBuilder& pb) {
		pb.Attach(*vshader).Attach(*fshader);
	});

	vshader.release();
	fshader.release();

	glm::vec3 p(0.0f, 0.0f, 3.0f);
	glm::vec3 dir(0.0f, 0.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	TestVisual::Camera camera(p, dir, up, TestVisual::ProjectionMode::Orthographic);

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto color = program->AttributeVariable(std::string("color"));
	const auto projection = program->UniformVariable(std::string("projection"));
	const auto view = program->UniformVariable(std::string("view"));
	vao->Bind();
	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(color);
	vao->SetVertexAttributePointer(color, *buf, colorPointer);

	for (unsigned int i = 0; i < 100; i++) {
		program->SetUniform(projection, std::vector<glm::mat4>({ camera.ProjectionMatrix() }));
		program->SetUniform(view, std::vector<glm::mat4>({ camera.ViewMatrix() }));

		gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
		window->SwapBuffers();
		gl.Clear(std::vector<OpenGL::Buffers>({ OpenGL::Buffers::Color }));
		camera.Position(camera.Position() + glm::vec3(0.01f, -0.01f, 0.0f));
		Sleep(100);
	}

	glFlush();
	window->SwapBuffers();
	Sleep(1000);
}
