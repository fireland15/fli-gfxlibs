#include "TextureBuilder.hpp"

#include "Texture.hpp"
#include "OpenGLWrapper.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "InvalidTextureDataException.hpp"

OpenGL::TextureBuilder::TextureBuilder(OpenGLWrapper& gl)
	: _gl(gl) { }

OpenGL::TextureBuilder::~TextureBuilder() { }

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::NewTexture(OpenGL::TextureTarget target) {
	_pixelData.clear();
	_textureTarget = target;
	return *this;
}

void AssignPixelData(std::vector<byte>& out, const byte* data, unsigned int bytes) {
	out = std::vector<byte>(data, data + bytes);
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::vec4> & pixels, glm::uvec2 dim, PixelFormat format) {
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::vec4) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::Float;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::uvec4> & pixels, glm::uvec2 dim, PixelFormat format) {
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::uvec4) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::UInt;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::vec3> & pixels, glm::uvec2 dim, PixelFormat format) {
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::vec3) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::UInt;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::uvec3> & pixels, glm::uvec2 dim, PixelFormat format) {
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::uvec3) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::UInt;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::WithLinearFilters() {
	_filterType = FilterType::Linear;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::WithNearestFilters() {
	_filterType = FilterType::Nearest;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::ClampEdges() {
	_wrapType = WrapType::ClampEdge;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::BorderColor(glm::vec4& color) {
	_wrapType = WrapType::BorderColor;
	_borderColor = color;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Repeat() {
	_wrapType = WrapType::Repeat;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::MirroredRepeat() {
	_wrapType = WrapType::MirroredRepeat;
	return *this;
}

std::unique_ptr<OpenGL::ITexture> OpenGL::TextureBuilder::Build() {
	if (_pixelData.empty())
		throw OpenGL::InvalidTextureDataException(std::string("texture data was empty"));
	if (_pixelData.size() != (_textureDim.x * _textureDim.y))
		throw OpenGL::InvalidTextureDataException(std::string("texture dimensions did not match pixel data"));

	OpenGL::TextureInternalFormat internalFormat;
	switch (_pixelFormat) {
		case OpenGL::PixelFormat::RGBA:
			internalFormat = OpenGL::TextureInternalFormat::RGBA;
			break;
		case OpenGL::PixelFormat::BGRA:
			internalFormat = OpenGL::TextureInternalFormat::RGBA;
			break;
		case OpenGL::PixelFormat::RGB:
			internalFormat = OpenGL::TextureInternalFormat::RGB;
			break;
		case OpenGL::PixelFormat::BGR:
			internalFormat = OpenGL::TextureInternalFormat::RGB;
			break;
	}

	OpenGL::TexturePixelType pixelType;
	switch (_pixelType) {
	case OpenGL::TextureBuilder::PixelType::Float:
		pixelType = OpenGL::TexturePixelType::Float
	}


	std::unique_ptr<OpenGL::Handle> handle(std::move(_gl.GenTexture()));

	std::unique_ptr<OpenGL::ITexture> tex(new OpenGL::Texture(_gl, std::move(handle), _textureTarget));
	tex->Bind();
	_gl.TexImage2D(_textureTarget, 0, internalFormat, _textureDim, )

	return std::unique_ptr<ITexture>();
}
