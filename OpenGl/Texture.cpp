#include "Texture.hpp"

#include <OpenGLWrapper.hpp>
#include <TextureParameterEnum.hpp>

OpenGL::Texture::Texture(OpenGL::OpenGLWrapper& gl, std::unique_ptr<OpenGL::Handle> handle, OpenGL::TextureTarget target) 
	: _gl(gl), _handle(std::move(handle)), _target(target) {

}

const OpenGL::Handle & OpenGL::Texture::Handle() {
	return *_handle;
}

OpenGL::TextureTarget OpenGL::Texture::Target() {
	return _target;
}

void OpenGL::Texture::Bind() {
	_gl.BindTexture(_target, *_handle);
}

void OpenGL::Texture::Unbind() {
	_gl.BindTexture(_target, OpenGL::Handle(OpenGL::ObjectType::Texture, 0));
}

void OpenGL::Texture::SetWrapS(TextureParameterValue value) {
	_gl.TexParameter(_target, OpenGL::TextureParameter::TextureWrapS, value);
}

void OpenGL::Texture::SetWrapT(TextureParameterValue value) {
	_gl.TexParameter(_target, OpenGL::TextureParameter::TextureWrapT, value);
}

void OpenGL::Texture::SetMagFilter(TextureParameterValue value) {
	_gl.TexParameter(_target, OpenGL::TextureParameter::TextureMagFilter, value);
}

void OpenGL::Texture::SetMinFilter(TextureParameterValue value) {
	_gl.TexParameter(_target, OpenGL::TextureParameter::TextureMinFilter, value);
}

void OpenGL::Texture::BindToSlot(unsigned int slot) {
	_gl.ActiveTexture(GL_TEXTURE0 + slot);
}
