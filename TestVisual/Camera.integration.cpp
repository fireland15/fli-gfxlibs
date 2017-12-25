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
#include <Auxili\ObjFileParser.hpp>
#include <Auxili\ObjFileData.hpp>
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

	glm::vec3 p(0.0f, 0.1f, 3.0f);
	glm::vec3 dir(0.0f, 0.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	TestVisual::Camera camera(p, dir, up, TestVisual::ProjectionMode::Perspective);

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

	float angle = 0.0f;

	for (unsigned int i = 0; i < 3600; i++) {
		program->SetUniform(projection, std::vector<glm::mat4>({ camera.ProjectionMatrix() }));
		program->SetUniform(view, std::vector<glm::mat4>({ camera.ViewMatrix() }));

		gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
		window->SwapBuffers();
		gl.Clear(std::vector<OpenGL::Buffers>({ OpenGL::Buffers::Color }));

		angle += 0.2f;
		camera.Position(glm::vec3(10 * std::sinf(glm::radians(angle)), std::sinf(glm::radians(3 * angle)), 10 * std::cosf(glm::radians(angle))));
		camera.Direction(glm::normalize(-1.0f * camera.Position()));
	}
}

void UsesCameraWithObjBunny() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);
	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(1200, 1200), std::string("Use Camera With Bunny"));
	auto & context = window->GetContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;

	Auxili::ObjFileParser parser;
	std::fstream bunnyFile("../Assets/Models/bunny.obj");
	auto bunnyData = parser.Parse(bunnyFile);

	std::vector<glm::vec4> verts;
	std::vector<glm::vec3> normals;
	verts.reserve(bunnyData->Faces().size() * 3);
	normals.reserve(bunnyData->Faces().size() * 3);

	for (unsigned int i = 0; i < bunnyData->Faces().size(); i++) {
		auto & face = bunnyData->Faces()[i];
		glm::vec3 a = bunnyData->Vertices()[face[0].Vertex - 1];
		glm::vec3 b = bunnyData->Vertices()[face[1].Vertex - 1];
		glm::vec3 c = bunnyData->Vertices()[face[2].Vertex - 1];
		verts.emplace_back(glm::vec4(a, 1.0f));
		verts.emplace_back(glm::vec4(b, 1.0f));
		verts.emplace_back(glm::vec4(c, 1.0f));

		glm::vec3 n = glm::normalize(glm::cross((b - c), (b - a)));

		normals.emplace_back(n);
		normals.emplace_back(n);
		normals.emplace_back(n);
	}

	OpenGL::BufferDataPointer vertsPointer(4, OpenGL::DataType::Float);
	OpenGL::BufferDataPointer normsPointer(3, OpenGL::DataType::Float);

	auto buf = context.NewBuffer([&](OpenGL::IBufferBuilder& b) {
		b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::ArrayBuffer)
			.UsedFor(OpenGL::BufferUsage::StaticDraw)
			.WithData([&](OpenGL::IBufferDataBuilder& db) {
			db.Data(glm::value_ptr(verts.front()), sizeof(glm::vec4), verts.size(), vertsPointer)
				.And(glm::value_ptr(normals.front()), sizeof(glm::vec3), normals.size(), normsPointer);
		});
	});

	auto vshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "layout(location = 0) in vec4 pos;" << std::endl;
		ss << "layout(location = 1) in vec3 normal;" << std::endl;
		ss << "uniform mat4 view;" << std::endl;
		ss << "uniform mat4 projection;" << std::endl;
		ss << "const vec3 lightDir = vec3(0.0, 0.0, 1.0);" << std::endl;
		ss << "out vec4 vColor;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "\tgl_Position = projection * view * pos;" << std::endl;
		ss << "\tvec3 n = normalize(normal);" << std::endl;
		ss << "\tfloat intensity = dot(normalize(lightDir), normalize(view * vec4(normal, 0.0)).xyz);" << std::endl;
		ss << "\tif (intensity <= 0.0) {" << std::endl;
		ss << "\t\tvColor = vec4(1.0, 0.3, 0.3, 1.0);" << std::endl;
		ss << "\t}" << std::endl;
		ss << "\t else {" << std::endl;
		ss << "\t\tvColor = vec4(intensity * vec3(0.5, 0.5, 1.0), 1.0);" << std::endl;
		ss << "\t}" << std::endl;
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

	glm::vec3 p(0.0f, 3.0f, 5);
	glm::vec3 dir(0.0f, 0.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	TestVisual::Camera camera(p, dir, up, TestVisual::ProjectionMode::Perspective);

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto norm = program->AttributeVariable(std::string("normal"));
	const auto projection = program->UniformVariable(std::string("projection"));
	const auto view = program->UniformVariable(std::string("view"));
	vao->Bind();
	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(norm);
	vao->SetVertexAttributePointer(norm, *buf, normsPointer);

	float angle = 0.0f;

	gl.Enable(OpenGL::Capabilities::DepthTest);
	for (unsigned int i = 0; i < 7200; i++) {
		gl.Clear(std::vector<OpenGL::Buffers>({ OpenGL::Buffers::Color, OpenGL::Buffers::Depth }));
		program->SetUniform(projection, std::vector<glm::mat4>({ camera.ProjectionMatrix() }));
		program->SetUniform(view, std::vector<glm::mat4>({ camera.ViewMatrix() }));

		gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, verts.size());
		window->SwapBuffers();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		angle += 0.1f;
		if (i < 3600)
			camera.Position(glm::vec3(5 * std::sinf(glm::radians(angle)), -2.0f, 5 * std::cosf(glm::radians(angle))));
		else
			camera.Position(glm::vec3(5 * std::sinf(glm::radians(angle)), 2.0f, 5 * std::cosf(glm::radians(angle))));
		camera.Direction(glm::normalize(-1.0f * camera.Position()));
	}
}