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
	if (pixels.size() != dim.x * dim.y) {
		throw OpenGL::InvalidTextureDataException(std::string("Texture dimensions do not match data"));
	}
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::vec4) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::Float;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::uvec4> & pixels, glm::uvec2 dim, PixelFormat format) {
	if (pixels.size() != dim.x * dim.y) {
		throw OpenGL::InvalidTextureDataException(std::string("Texture dimensions do not match data"));
	}
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::uvec4) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::UInt;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::vec3> & pixels, glm::uvec2 dim, PixelFormat format) {
	if (pixels.size() != dim.x * dim.y) {
		throw OpenGL::InvalidTextureDataException(std::string("Texture dimensions do not match data"));
	}
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::vec3) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::Float;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::uvec3> & pixels, glm::uvec2 dim, PixelFormat format) {
	if (pixels.size() != dim.x * dim.y) {
		throw OpenGL::InvalidTextureDataException(std::string("Texture dimensions do not match data"));
	}
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::uvec3) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::UInt;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::u8vec4> & pixels, glm::uvec2 dim, PixelFormat format) {
	if (pixels.size() != dim.x * dim.y) {
		throw OpenGL::InvalidTextureDataException(std::string("Texture dimensions do not match data"));
	}
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::u8vec4) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::Byte;
	_textureDim = dim;
	return *this;
}

OpenGL::ITextureBuilder & OpenGL::TextureBuilder::Pixels(std::vector<glm::u8vec3> & pixels, glm::uvec2 dim, PixelFormat format) {
	if (pixels.size() != dim.x * dim.y) {
		throw OpenGL::InvalidTextureDataException(std::string("Texture dimensions do not match data"));
	}
	AssignPixelData(_pixelData, reinterpret_cast<byte*>(glm::value_ptr(pixels.front())), sizeof(glm::u8vec3) * pixels.size());
	_pixelFormat = format;
	_pixelType = PixelType::Byte;
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

	OpenGL::TextureInternalFormat internalFormat;
	OpenGL::TexturePixelType texPixelType;
	OpenGL::DataType pixelType;
	if (_pixelType == PixelType::UInt) {
		pixelType = OpenGL::DataType::UnsignedInt;
		if (_pixelFormat == PixelFormat::RGB) {
			internalFormat = OpenGL::TextureInternalFormat::RGB32UI;
			texPixelType = OpenGL::TexturePixelType::RGB;
		}
		else if (_pixelFormat == PixelFormat::RGBA) {
			internalFormat = OpenGL::TextureInternalFormat::RGBA32UI;
			texPixelType = OpenGL::TexturePixelType::RGBA;
		}
	}
	else if (_pixelType == PixelType::Float) {
		pixelType = OpenGL::DataType::Float;
		if (_pixelFormat == PixelFormat::RGB) {
			internalFormat = OpenGL::TextureInternalFormat::RGB32F;
			texPixelType = OpenGL::TexturePixelType::RGB;
		}
		else if (_pixelFormat == PixelFormat::RGBA) {
			internalFormat = OpenGL::TextureInternalFormat::RGBA32F;
			texPixelType = OpenGL::TexturePixelType::RGBA;
		}
	}
	else if (_pixelType == PixelType::Byte) {
		pixelType = OpenGL::DataType::UnsignedByte;
		if (_pixelFormat == PixelFormat::RGB) {
			internalFormat = OpenGL::TextureInternalFormat::RGB;
			texPixelType = OpenGL::TexturePixelType::RGB;
		}
		else if (_pixelFormat == PixelFormat::RGBA) {
			internalFormat = OpenGL::TextureInternalFormat::RGBA;
			texPixelType = OpenGL::TexturePixelType::RGBA;
		}
	}

	std::unique_ptr<OpenGL::Handle> handle(std::move(_gl.GenTexture()));

	std::unique_ptr<OpenGL::ITexture> tex(new OpenGL::Texture(_gl, std::move(handle), _textureTarget));
	tex->Bind();

	_gl.TexImage2D(_textureTarget, 0, internalFormat, _textureDim, texPixelType, pixelType, _pixelData.data());
	auto err = _gl.GetError();

	switch (_wrapType) {
	case OpenGL::TextureBuilder::WrapType::BorderColor:
		tex->SetWrapS(OpenGL::TextureParameterValue::ClampToBorder);
		tex->SetWrapT(OpenGL::TextureParameterValue::ClampToBorder);
		//TODO: Set border color
		break;
	case OpenGL::TextureBuilder::WrapType::ClampEdge:
		tex->SetWrapS(OpenGL::TextureParameterValue::ClampToEdge);
		tex->SetWrapT(OpenGL::TextureParameterValue::ClampToEdge);
		break;
	case OpenGL::TextureBuilder::WrapType::Repeat:
		tex->SetWrapS(OpenGL::TextureParameterValue::Repeat);
		tex->SetWrapT(OpenGL::TextureParameterValue::Repeat);
		break;
	case OpenGL::TextureBuilder::WrapType::MirroredRepeat:
		tex->SetWrapS(OpenGL::TextureParameterValue::MirroredRepeat);
		tex->SetWrapT(OpenGL::TextureParameterValue::MirroredRepeat);
		break;
	}

	switch (_filterType) {
	case OpenGL::TextureBuilder::FilterType::Linear:
		tex->SetMagFilter(OpenGL::TextureParameterValue::Linear);
		tex->SetMinFilter(OpenGL::TextureParameterValue::Linear);
		break;
	case OpenGL::TextureBuilder::FilterType::Nearest:
		tex->SetMagFilter(OpenGL::TextureParameterValue::Nearest);
		tex->SetMinFilter(OpenGL::TextureParameterValue::Nearest);
		break;
	}

	_gl.GenerateMipmap(_textureTarget);

	return std::move(tex);
}
