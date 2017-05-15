#include "UniformTypeFormatter.hpp"

std::map<OpenGL::UniformType, std::string> OpenGL::UniformTypeFormatter::_strings = std::map<OpenGL::UniformType, std::string>();

OpenGL::UniformTypeFormatter::UniformTypeFormatter() {
	if (_strings.empty()) {
		_strings.emplace(UniformType::Float, std::string("float"));
		_strings.emplace(UniformType::Vec2f, std::string("vec2f"));
		_strings.emplace(UniformType::Vec3f, std::string("vec3f"));
		_strings.emplace(UniformType::Vec4f, std::string("vec4f"));
		_strings.emplace(UniformType::Mat2f, std::string("mat2f"));
		_strings.emplace(UniformType::Mat3f, std::string("mat3f"));
		_strings.emplace(UniformType::Mat4f, std::string("mat4f"));
		_strings.emplace(UniformType::Mat2x3f, std::string("mat2x3f"));
		_strings.emplace(UniformType::Mat2x4f, std::string("mat2x4f"));
		_strings.emplace(UniformType::Mat3x2f, std::string("mat3x2f"));
		_strings.emplace(UniformType::Mat3x4f, std::string("mat3x4f"));
		_strings.emplace(UniformType::Mat4x2f, std::string("mat4x3f"));
		_strings.emplace(UniformType::Mat4x3f, std::string("mat4x3f"));
		_strings.emplace(UniformType::Int, std::string("int"));
		_strings.emplace(UniformType::Vec2i, std::string("vec2i"));
		_strings.emplace(UniformType::Vec3i, std::string("vec3i"));
		_strings.emplace(UniformType::Vec4i, std::string("vec4i"));
		_strings.emplace(UniformType::UnsignedInt, std::string("uint"));
		_strings.emplace(UniformType::Vec2u, std::string("vec2u"));
		_strings.emplace(UniformType::Vec3u, std::string("vec3u"));
		_strings.emplace(UniformType::Vec4u, std::string("vec4u"));
		_strings.emplace(UniformType::Double, std::string("double"));
		_strings.emplace(UniformType::Vec2d, std::string("vec2d"));
		_strings.emplace(UniformType::Vec3d, std::string("vec3d"));
		_strings.emplace(UniformType::Vec4d, std::string("vec4d"));
		_strings.emplace(UniformType::Mat2d, std::string("mat2d"));
		_strings.emplace(UniformType::Mat3d, std::string("mat3d"));
		_strings.emplace(UniformType::Mat4d, std::string("mat4d"));
		_strings.emplace(UniformType::Mat2x3d, std::string("mat2x3d"));
		_strings.emplace(UniformType::Mat2x4d, std::string("mat2x4d"));
		_strings.emplace(UniformType::Mat3x2d, std::string("mat3x2d"));
		_strings.emplace(UniformType::Mat3x4d, std::string("mat3x4d"));
		_strings.emplace(UniformType::Mat4x2d, std::string("mat4x2d"));
		_strings.emplace(UniformType::Mat4x3d, std::string("mat4x3d"));
	}
}

std::string OpenGL::UniformTypeFormatter::ToString(UniformType type) {
	return _strings[type];
}
