#pragma once

#include <glm\glm.hpp>

namespace TestVisual {

	enum class ProjectionMode {
		Perspective,
		Orthographic
	};

	class Camera {
	public:
		Camera();
		Camera(glm::vec3 & position, glm::vec3 & direction, glm::vec3 & up, ProjectionMode mode = ProjectionMode::Orthographic);

		void Projection(ProjectionMode mode);
		ProjectionMode Projection();

		glm::vec3 Position();
		void Position(glm::vec3& position);

		glm::vec3 Direction();
		void Direction(glm::vec3 & direction);

		glm::mat4 ViewMatrix();
		glm::mat4 ProjectionMatrix();

	private:
		glm::vec3 _position;
		glm::vec3 _direction;
		glm::vec3 _up;

		ProjectionMode _mode;
	};

}