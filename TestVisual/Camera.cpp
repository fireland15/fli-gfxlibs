#include "Camera.hpp"

#include <glm\gtc\matrix_transform.hpp>

TestVisual::Camera::Camera()
	: _position(0.0f, 0.0f, 0.0f), _direction(0.0f, 0.0f, 1.0f), _up(0.0f, 1.0f, 0.0f), _mode(TestVisual::ProjectionMode::Orthographic) { }

TestVisual::Camera::Camera(glm::vec3 & position, glm::vec3 & direction, glm::vec3 & up, TestVisual::ProjectionMode mode) 
	: _position(position), _direction(direction), _up(up), _mode(mode) { }

void TestVisual::Camera::Projection(TestVisual::ProjectionMode mode) {
	_mode = mode;
}

TestVisual::ProjectionMode TestVisual::Camera::Projection() {
	return _mode;
}

glm::vec3 TestVisual::Camera::Position() {
	return _position;
}

void TestVisual::Camera::Position(glm::vec3 & position) {
	_position = position;
}

glm::vec3 TestVisual::Camera::Direction() {
	return _direction;
}

void TestVisual::Camera::Direction(glm::vec3 & direction) {
	_direction = direction;
}

glm::mat4 TestVisual::Camera::ViewMatrix() {
	return glm::lookAt(_position, _position + _direction, _up);
}

glm::mat4 TestVisual::Camera::ProjectionMatrix() {
	if (_mode == TestVisual::ProjectionMode::Orthographic) {
		return glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.001f, 1000.0f);
	}
	else {
		return glm::perspective(glm::radians(45.0f), 1.0f, 0.001f, 1000.0f);
	}
}
