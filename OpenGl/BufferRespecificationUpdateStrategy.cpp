#include "BufferRespecificationUpdateStrategy.hpp"
#include <IOpenGL.hpp>

OpenGL::BufferRespecificationUpdateStrategy::BufferRespecificationUpdateStrategy(OpenGLWrapper & gl) : _gl(gl) {

}

OpenGL::BufferRespecificationUpdateStrategy::~BufferRespecificationUpdateStrategy() {

}

void OpenGL::BufferRespecificationUpdateStrategy::RespecifyBuffer(BufferTarget target, const std::vector<unsigned char>& data, BufferUsage usage) {
	_gl.Raw().BufferData(static_cast<unsigned int>(target), data.size(), nullptr, static_cast<unsigned int>(usage));
	_gl.BufferData(target, data, usage);
}
