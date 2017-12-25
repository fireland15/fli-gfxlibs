#include "OpenGL.integration.hpp"
#include <glew.h>
#include <Fenestram/WindowManager.hpp>
#include <Fenestram/Window.hpp>

#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>

#include <OpenGLWrapper.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <RealOpenGL.hpp>
#include <OpenGl/OpenGlContext.hpp>

#include <IBufferBuilder.hpp>
#include <IBufferDataBuilder.hpp>
#include <BufferDataBuilder.hpp>
#include <IProgram.hpp>
#include <IProgramBuilder.hpp>
#include <IShader.hpp>
#include <ITexture.hpp>
#include <ITextureBuilder.hpp>
#include <IBuffer.hpp>
#include <IShaderBuilder.hpp>
#include <ShaderSource.hpp>
#include <IVertexArray.hpp>
#include <BufferRespecificationUpdateStrategy.hpp>
#include <BufferDataDescriptor.hpp>

#include <Auxili\ImageData.hpp>
#include <Auxili\PngImageLoader.hpp>
#include <Auxili\BmpImageLoader.hpp>
#include <Auxili\FileIOException.hpp>

void CreateOpenGLContext() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(300, 300), std::string("Create OpenGL Context"));
	auto & context = window->GetContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;
}

void DrawTriangle() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(300, 300), std::string("Draw Triangle"));
	auto & context = window->GetContext();
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
	window->SwapBuffers();
	Sleep(1000);
}

void DrawColoredTriangle() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(300, 300), std::string("Draw Colored Triangle"));
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
	window->SwapBuffers();
	Sleep(1000);
}

void UsesUniforms() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(300, 300), std::string("Use Uniforms"));
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
		window->SwapBuffers();
		std::vector<OpenGL::Buffers> clearBufs;
		clearBufs.push_back(OpenGL::Buffers::Color);
		gl.Clear(clearBufs);
		Sleep(16);
	}
}

void UpdateBufferData() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(300, 300), std::string("Update Buffer Data"));
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

	window->SwapBuffers();
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
		window->SwapBuffers();
		gl.Clear(clearBufs);

		Sleep(16);
	}
}

void UsesTextures() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(800, 800), std::string("Uses Textures"));
	auto & context = window->GetContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl; 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<glm::vec4> verts;
	verts.emplace_back(0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(-0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.0f, 0.5f, 0.0f, 1.0f);

	std::vector<glm::vec2> uvs;
	uvs.emplace_back(0.0f, 0.0f);
	uvs.emplace_back(1.0f, 0.0f);
	uvs.emplace_back(1.0f, 0.5f);

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
	
	unsigned int imageDim = 255;
	std::vector<glm::u8vec4> image = std::vector<glm::u8vec4>();
	image.reserve(imageDim * imageDim);
	for (unsigned int i = 0; i < imageDim * imageDim; i++) {
		unsigned char r = (i / imageDim) * 3;
		unsigned char g = (i % imageDim) * 3;
		unsigned char a = (unsigned char)(((float)((i + 1) / imageDim) / imageDim) * 255);

		image.emplace_back(r, g, 255, a);
	}

	auto texture = context.NewTexture([&](OpenGL::ITextureBuilder& tb) {
		tb.NewTexture(OpenGL::TextureTarget::Texture2D)
			.Pixels(image, glm::uvec2(imageDim, imageDim), OpenGL::PixelFormat::RGBA)
			.WithLinearFilters()
			.Repeat();
	});

	vshader.release();
	fshader.release();

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto uv = program->AttributeVariable(std::string("uv"));
	auto texSampler = program->UniformVariable(std::string("ourTexture"));

	vao->Bind();

	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(uv);
	vao->SetVertexAttributePointer(uv, *buf, uvPointer);

	realGl.ClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	window->SwapBuffers();

	texture->Bind();
	texture->BindToSlot(0);
	program->SetUniform(texSampler, 0);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
	window->SwapBuffers();
	std::vector<OpenGL::Buffers> clearBufs;
	clearBufs.push_back(OpenGL::Buffers::Color);
	gl.Clear(clearBufs);
	Sleep(4000);
}

void UsesTexturesFromPngFile() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(800, 800), std::string("Uses Textures From PNG File"));
	auto & context = window->GetContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<glm::vec4> verts;
	verts.emplace_back(0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(-0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.0f, 0.5f, 0.0f, 1.0f);

	std::vector<glm::vec2> uvs;
	uvs.emplace_back(0.0f, 0.0f);
	uvs.emplace_back(0.0f, 1.0f);
	uvs.emplace_back(1.0f, 0.5f);

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

	Auxili::PngImageLoader pngLoader;
	std::unique_ptr<Auxili::ImageData> imageData;
	try {
		imageData = pngLoader.Load("LibPngTests_CreatePngImage2.png");
	}
	catch (Auxili::FileIOException e) {
		std::cout << "Error loading texture image" << std::endl;
		return;
	}

	auto texture = context.NewTexture([&](OpenGL::ITextureBuilder& tb) {
		tb.NewTexture(OpenGL::TextureTarget::Texture2D)
			.Pixels(imageData->Pixels, imageData->Dimensions, OpenGL::PixelFormat::RGBA)
			.WithLinearFilters()
			.Repeat();
	});

	vshader.release();
	fshader.release();

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto uv = program->AttributeVariable(std::string("uv"));
	auto texSampler = program->UniformVariable(std::string("ourTexture"));

	vao->Bind();

	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(uv);
	vao->SetVertexAttributePointer(uv, *buf, uvPointer);

	realGl.ClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	window->SwapBuffers();

	texture->Bind();
	texture->BindToSlot(0);
	program->SetUniform(texSampler, 0);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
	window->SwapBuffers();
	std::vector<OpenGL::Buffers> clearBufs;
	clearBufs.push_back(OpenGL::Buffers::Color);
	gl.Clear(clearBufs);
	Sleep(4000);
}

void UsesTexturesFromBmpFile() {
	OpenGL::RealOpenGL realGl;
	OpenGL::OpenGLWrapper gl(realGl);

	Fenestram::WindowManager windowManager;
	auto window = windowManager.GetNewWindow(glm::uvec2(1600, 1600), std::string("Uses Textures From PNG File"));
	auto & context = window->GetContext();
	std::cout << "Using OpenGL Version: " << context.MajorVersion() << "." << context.MinorVersion() << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<glm::vec4> verts;
	verts.emplace_back(0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(-0.5f, -0.5f, 0.0f, 1.0f);
	verts.emplace_back(0.0f, 0.5f, 0.0f, 1.0f);

	std::vector<glm::vec2> uvs;
	uvs.emplace_back(0.0f, 0.0f);
	uvs.emplace_back(0.0f, 1.0f);
	uvs.emplace_back(1.0f, 0.5f);

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

	Auxili::BmpImageLoader bmpLoader;
	auto imageData = bmpLoader.Load("Dove.bmp");

	auto texture = context.NewTexture([&](OpenGL::ITextureBuilder& tb) {
		tb.NewTexture(OpenGL::TextureTarget::Texture2D)
			.Pixels(imageData->Pixels, imageData->Dimensions, OpenGL::PixelFormat::RGBA)
			.WithLinearFilters()
			.Repeat();
	});

	vshader.release();
	fshader.release();

	auto vao = context.NewVertexArray();

	program->Use();

	auto pos = program->AttributeVariable(std::string("pos"));
	auto uv = program->AttributeVariable(std::string("uv"));
	auto texSampler = program->UniformVariable(std::string("ourTexture"));

	vao->Bind();

	vao->EnableVertexAttribute(pos);
	vao->SetVertexAttributePointer(pos, *buf, vertsPointer);
	vao->EnableVertexAttribute(uv);
	vao->SetVertexAttributePointer(uv, *buf, uvPointer);

	realGl.ClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	window->SwapBuffers();

	texture->Bind();
	texture->BindToSlot(0);
	program->SetUniform(texSampler, 0);

	gl.DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
	window->SwapBuffers();
	std::vector<OpenGL::Buffers> clearBufs;
	clearBufs.push_back(OpenGL::Buffers::Color);
	gl.Clear(clearBufs);
	Sleep(4000);
}
