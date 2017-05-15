#include "OpenGL.integration.hpp"
#include <glew.h>
#include <Window.hpp>

#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>

#include <OpenGLWrapper.hpp>
#include <WindowsWrapper.hpp>
#include <WinGdiWrapper.hpp>
#include <GlewProvider.hpp>
#include <WindowsGLProvider.hpp>
#include <WinUserWrapper.hpp>
#include <Win32Provider.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <RealOpenGL.hpp>

#include <IBufferBuilder.hpp>
#include <IBufferDataBuilder.hpp>
#include <BufferDataBuilder.hpp>
#include <IProgram.hpp>
#include <IProgramBuilder.hpp>
#include <IShader.hpp>
#include <Texture.hpp>
#include <IBuffer.hpp>
#include <IShaderBuilder.hpp>
#include <ShaderSource.hpp>
#include <IVertexArray.hpp>
#include <BufferRespecificationUpdateStrategy.hpp>
#include <BufferDataDescriptor.hpp>

void CreateOpenGLContext() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Create OpenGL Context"), glm::uvec2(0.0f, 0.0f), glm::uvec2(300, 300), win32);

	auto context = w.CreateOpenGLContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;
}

void DrawTriangle() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Draw Triangle"), glm::uvec2(0.0f, 0.0f), glm::uvec2(300, 300), win32);

	auto context = w.CreateOpenGLContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;

	std::vector<glm::vec4> verts;
	verts.emplace_back(-0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.0f, 0.5f, 0.0f, 1.0f);

	OpenGL::BufferDataPointer vertsPointer(4, OpenGL::DataType::Float);

	auto buf = context.NewBuffer([&](OpenGL::IBufferBuilder& b) {
		b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::ArrayBuffer)
			.UsedFor(OpenGL::BufferUsage::StaticDraw)
			.WithData([&](OpenGL::IBufferDataBuilder& db) {
				db.Data(glm::value_ptr(verts.front()), sizeof(glm::vec4), verts.size(), vertsPointer);
			});
	});

	auto vshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "layout(location = 0) in vec4 pos;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "\tgl_Position = pos;" << std::endl;
		ss << "}" << std::endl;
		OpenGL::ShaderSource vsource(ss);
		
		sb.AddSource(vsource).Type(OpenGL::ShaderType::Vertex);
	});
	
	auto fshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "out vec4 color;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "\tcolor = vec4(1, 0, 0, 1);" << std::endl;
		ss << "}" << std::endl;
		OpenGL::ShaderSource fsource(ss);

		sb.AddSource(fsource).Type(OpenGL::ShaderType::Fragment);
	});

	auto program = context.NewProgram([&](OpenGL::IProgramBuilder& pb) {
		pb.Attach(*vshader).Attach(*fshader);
	});

	vshader.release();
	fshader.release();

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	vao->Bind();
	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

	glFlush();
	context.SwapBuffer();
	Sleep(1000);
}

void DrawColoredTriangle() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Draw Colored Triangle"), glm::uvec2(0.0f, 0.0f), glm::uvec2(300, 300), win32);

	auto context = w.CreateOpenGLContext();
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
		ss << "out vec4 vColor;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "vColor = color;" << std::endl;
		ss << "\tgl_Position = pos;" << std::endl;
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

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto color = program->AttributeVariable(std::string("color"));
	vao->Bind();
	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(color);
	vao->SetVertexAttributePointer(color, *buf, colorPointer);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

	glFlush();
	context.SwapBuffer();
	Sleep(1000);
}

void UsesUniforms() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Draw Colored Triangle"), glm::uvec2(0.0f, 0.0f), glm::uvec2(300, 300), win32);

	auto context = w.CreateOpenGLContext();
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
		ss << "layout(location = 2) uniform vec4 translation;" << std::endl;
		ss << "out vec4 vColor;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "vColor = color;" << std::endl;
		ss << "\tgl_Position = pos + translation;" << std::endl;
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

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto color = program->AttributeVariable(std::string("color"));
	auto translation = program->UniformVariable(std::string("translation"));

	vao->Bind();
	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(color);
	vao->SetVertexAttributePointer(color, *buf, colorPointer);

	for (unsigned int i = 0; i < 60; i++) {
		glm::vec4 trans(0.0f, 0.0f + ((float)i * 0.01f), 0.0f, 0.0f);
		program->SetUniform(translation, trans);

		gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
		context.SwapBuffer();
		std::vector<OpenGL::Buffers> clearBufs;
		clearBufs.push_back(OpenGL::Buffers::Color);
		gl.Clear(clearBufs);
		Sleep(16);
	}
}

void UpdateBufferData() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Draw Colored Triangle"), glm::uvec2(0.0f, 0.0f), glm::uvec2(300, 300), win32);

	auto context = w.CreateOpenGLContext();
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

	auto vertBuf = context.NewBuffer([&](OpenGL::IBufferBuilder& b) {
		b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::ArrayBuffer)
			.UsedFor(OpenGL::BufferUsage::DynamicDraw)
			.WithData([&](OpenGL::IBufferDataBuilder& db) {
				db.Data(glm::value_ptr(verts.front()), sizeof(glm::vec4), verts.size(), vertsPointer);
			});
	});

	auto colorBuf = context.NewBuffer([&](OpenGL::IBufferBuilder& b) {
		b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::ArrayBuffer)
			.UsedFor(OpenGL::BufferUsage::DynamicDraw)
			.WithData([&](OpenGL::IBufferDataBuilder& db) {
				db.Data(glm::value_ptr(colors.front()), sizeof(glm::vec4), colors.size(), colorPointer);
			});
	});

	auto vshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "layout(location = 0) in vec4 pos;" << std::endl;
		ss << "layout(location = 1) in vec4 color;" << std::endl;
		ss << "layout(location = 2) uniform vec4 translation;" << std::endl;
		ss << "out vec4 vColor;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "vColor = color;" << std::endl;
		ss << "\tgl_Position = pos + translation;" << std::endl;
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

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto color = program->AttributeVariable(std::string("color"));

	vao->Bind();
	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *vertBuf, vertsPointer);
	vao->EnableVertexAttribute(color);
	vao->SetVertexAttributePointer(color, *colorBuf, colorPointer);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

	context.SwapBuffer();
	std::vector<OpenGL::Buffers> clearBufs;
	clearBufs.push_back(OpenGL::Buffers::Color);
	gl.Clear(clearBufs);

	Sleep(1000);

	srand(17);

	auto random = [](float lo, float hi) {
		return lo + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (hi - lo)));
	};

	std::vector<glm::vec4> updatedVerts = verts;
	for (unsigned int i = 0; i < 180; i++) {
		for (unsigned int j = 0; j < updatedVerts.size(); j++) {
			updatedVerts[j] += random(-0.01f, 0.01f);
		}

		OpenGL::BufferDataBuilder dataBuilder;
		dataBuilder.Data(glm::value_ptr(updatedVerts.front()), sizeof(glm::vec4), updatedVerts.size(), vertsPointer);
		auto updatedVertsData = dataBuilder.BuildData(OpenGL::BufferDataFormatter());

		vertBuf->Update(updatedVertsData, vertsPointer, OpenGL::BufferRespecificationUpdateStrategy(gl));

		gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
		context.SwapBuffer();
		gl.Clear(clearBufs);

		Sleep(16);
	}
}

void UsesTextures() {
	OpenGL::WindowsWrapper windows;
	OpenGL::WinUserWrapper winUser;
	OpenGL::GlewProvider glew;
	OpenGL::WinGdiWrapper gdi;
	OpenGL::WindowsGLProvider winGl;
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	OpenGL::Win32Provider win32(gl, glew, winGl, winUser, gdi, windows);

	Window::Window w((HINSTANCE)(GetModuleHandle(NULL)), std::string("Using Textures"), glm::uvec2(800.0f, 200.0f), glm::uvec2(600, 600), win32);

	auto context = w.CreateOpenGLContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;

	std::vector<glm::vec4> verts;
	verts.emplace_back(0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(-0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.0f, 0.5f, 0.0f, 1.0f);

	std::vector<glm::vec2> uvs;
	uvs.emplace_back(0.0f, 0.0f);
	uvs.emplace_back(1.0f, 0.0f);
	uvs.emplace_back(1.0f, 1.0f);

	OpenGL::BufferDataPointer vertsPointer(4, OpenGL::DataType::Float);
	OpenGL::BufferDataPointer uvPointer(2, OpenGL::DataType::Float);

	auto buf = context.NewBuffer([&](OpenGL::IBufferBuilder& b) {
		b.NewBuffer()
			.Targeting(OpenGL::BufferTarget::ArrayBuffer)
			.UsedFor(OpenGL::BufferUsage::StaticDraw)
			.WithData([&](OpenGL::IBufferDataBuilder& db) {
			db.Data(glm::value_ptr(verts.front()), sizeof(glm::vec4), verts.size(), vertsPointer)
				.And(glm::value_ptr(uvs.front()), sizeof(glm::vec2), uvs.size(), uvPointer);
		});
	});

	auto vshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "layout(location = 0) in vec4 pos;" << std::endl;
		ss << "layout(location = 1) in vec2 uv;" << std::endl;
		ss << "out vec2 texCoord;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "\ttexCoord = uv;" << std::endl;
		ss << "\tgl_Position = pos;" << std::endl;
		ss << "}" << std::endl;
		OpenGL::ShaderSource vsource(ss);

		sb.AddSource(vsource).Type(OpenGL::ShaderType::Vertex);
	});

	auto fshader = context.NewShader([&](OpenGL::IShaderBuilder& sb) {
		std::stringstream ss;
		ss << "#version 430" << std::endl;
		ss << "in vec2 texCoord;" << std::endl;
		ss << "out vec4 color;" << std::endl;
		ss << "uniform sampler2D ourTexture;" << std::endl;
		ss << "void main() {" << std::endl;
		ss << "\tcolor = texture(ourTexture, texCoord);" << std::endl;
		ss << "}" << std::endl;
		OpenGL::ShaderSource fsource(ss);

		sb.AddSource(fsource).Type(OpenGL::ShaderType::Fragment);
	});

	auto program = context.NewProgram([&](OpenGL::IProgramBuilder& pb) {
		pb.Attach(*vshader).Attach(*fshader);
	});

	vshader.release();
	fshader.release();

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto uv = program->AttributeVariable(std::string("uv"));
	auto texSampler = program->UniformVariable(std::string("ourTexture"));

	auto random = [](int lo, int hi) {
		return lo + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (hi - lo)));
	};

	unsigned int imageDim = 512;
	std::vector<unsigned char> image(imageDim * imageDim * 4);
	for (unsigned int i = 0; i < image.size(); i += 4) {
		image[i] = i / imageDim;
		image[i + 1] = 2 * i / (imageDim + 1);
		image[i + 2] = 3 * i / (imageDim + 3);
		image[i + 3] = 255;
	}

	vao->Bind();

	OpenGL::Texture tex(gl, std::move(gl.GenTexture()), OpenGL::TextureTarget::Texture2D);
	tex.Bind();
	gl.TexImage2D(OpenGL::TextureTarget::Texture2D, 0, OpenGL::TextureInternalFormat::RGBA, glm::ivec2(imageDim, imageDim), OpenGL::TexturePixelType::RGBA, OpenGL::DataType::Byte, image.data());
	tex.SetWrapS(OpenGL::TextureParameterValue::Repeat);
	tex.SetWrapT(OpenGL::TextureParameterValue::Repeat);
	tex.SetMagFilter(OpenGL::TextureParameterValue::Nearest);
	tex.SetMinFilter(OpenGL::TextureParameterValue::LinearMipmapLinear);
	gl.GenerateMipmap(OpenGL::TextureTarget::Texture2D);

	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(uv);
	vao->SetVertexAttributePointer(uv, *buf, uvPointer);

	realGl.ClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	context.SwapBuffer();

	tex.BindToSlot(0);
	program->SetUniform(texSampler, 0);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
	context.SwapBuffer();
	std::vector<OpenGL::Buffers> clearBufs;
	clearBufs.push_back(OpenGL::Buffers::Color);
	gl.Clear(clearBufs);
	Sleep(4000);
}
