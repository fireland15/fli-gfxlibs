#include "UserInputMapper.integration.hpp"

#include "UserInputMapper.hpp"
#include <sstream>
#include <list>
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <Fenestram\Window.hpp>
#include <Fenestram\WindowManager.hpp>
#include <OpenGl\OpenGlContext.hpp>
#include <OpenGl\BufferDataPointer.hpp>
#include <OpenGl\IBuffer.hpp>
#include <OpenGl\IShader.hpp>
#include <OpenGl\IBufferBuilder.hpp>
#include <OpenGl\IShaderBuilder.hpp>
#include <OpenGl\IProgram.hpp>
#include <OpenGl\IProgramBuilder.hpp>
#include <OpenGl\ShaderSource.hpp>
#include <OpenGl\IBufferDataBuilder.hpp>
#include <OpenGl\IVertexArray.hpp>
#include <OpenGlFacade\RealOpenGL.hpp>
#include <OpenGlFacade\OpenGLWrapper.hpp>
#include "Camera.hpp"

void TokenizesFile() {
	std::stringstream ss;
	ss << "a --> func();\n";
	ss << "b --> func2(arg);\n";
	ss << "c --> func3(1...0);\n";
	Tokenizer t;
	auto list = t.Tokenize(ss);
	for (auto & l : list) {
		std::cout << l.ToString() << std::endl;
	}
}

void ParsesTokens() {
	std::vector<Token> tokens;
	tokens.emplace_back(Tokens::Identifier, std::string("a"));
	tokens.emplace_back(Tokens::MapOperator);
	tokens.emplace_back(Tokens::Identifier, std::string("func"));
	tokens.emplace_back(Tokens::OpenParen);
	tokens.emplace_back(Tokens::CloseParen);
	tokens.emplace_back(Tokens::NewLine);
	tokens.emplace_back(Tokens::MapOperator);
	tokens.emplace_back(Tokens::Identifier, std::string("func2"));
	tokens.emplace_back(Tokens::OpenParen);
	tokens.emplace_back(Tokens::Number, std::string("123"));
	tokens.emplace_back(Tokens::CloseParen);
	tokens.emplace_back(Tokens::NewLine);
	tokens.emplace_back(Tokens::Identifier, std::string("b"));
	tokens.emplace_back(Tokens::MapOperator);
	tokens.emplace_back(Tokens::Identifier, std::string("func3"));
	tokens.emplace_back(Tokens::OpenParen);
	tokens.emplace_back(Tokens::Number, std::string("123"));
	tokens.emplace_back(Tokens::Comma);
	tokens.emplace_back(Tokens::Number, std::string("456"));
	tokens.emplace_back(Tokens::CloseParen);
	tokens.emplace_back(Tokens::NewLine);

	Parser p;
	p.AddMethod(std::string("func"), []() { std::cout << "func" << std::endl; });
	p.AddMethod(std::string("func2"), [](float f) { std::cout << "func2: " << f << std::endl; });
	p.AddMethod(std::string("func3"), [](float f1, float f2) { std::cout << "func3: " << f1 << ", " << f2 << std::endl; });
	auto map = p.Parse(tokens);


	map.Invoke(UserEvents::a);
	map.Invoke(UserEvents::b);
}

void ParsesTokensFromFile() {
	std::fstream f("Scripts/UserInputMapping.txt");
	Tokenizer t;
	auto tokens = t.Tokenize(f);
	Parser p;
	p.AddMethod(std::string("moveup"), [](float f) { std::cout << "Moving up by " << f << " units" << std::endl; });
	p.AddMethod(std::string("movedown"), [](float f) { std::cout << "Moving down by " << f << " units" << std::endl; });
	p.AddMethod(std::string("pause"), []() { std::cout << "Pausing" << std::endl; });
	p.AddMethod(std::string("resume"), []() { std::cout << "Resuming" << std::endl; });
	auto map = p.Parse(tokens);

	map.Invoke(UserEvents::w);
	map.Invoke(UserEvents::p);
	map.Invoke(UserEvents::o);
	map.Invoke(UserEvents::s);
}

void VisualTest() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(1000, 1000), std::string("Draw Colored Triangle"));
	window->SetKeyCallback([](int key, int scancode, int action, int mods) { std::cout << (char)key << " pressed" << std::endl; });
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

	glm::vec3 p(0.0f, 0.0f, 10.0f);
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

	for (unsigned int i = 0; i < 3600; i++) {
		program->SetUniform(projection, std::vector<glm::mat4>({ camera.ProjectionMatrix() }));
		program->SetUniform(view, std::vector<glm::mat4>({ camera.ViewMatrix() }));

		gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
		window->SwapBuffers();
		gl.Clear(std::vector<OpenGL::Buffers>({ OpenGL::Buffers::Color }));

		window->PollEvents();
	}

}
