#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>

typedef glm::vec4 Position;
typedef glm::quat Orientation;
typedef glm::vec4 Scale;
typedef glm::mat4 ModelMatrix;
typedef glm::mat4 TranslationMatrix;
typedef glm::mat4 RotationMatrix;
typedef glm::mat4 ScaleMatrix;

namespace gfx {
	namespace core {

		class TransformComponent {

		private:
			Position m_position;
			Orientation m_orientation;
			Scale m_scale;
			ModelMatrix m_modelMatrix;

		public:
			TransformComponent();

			Position GetPosition();

			Orientation GetOrientation();

			Scale GetScale();

			void SetPosition(const Position& p);

			void SetOrientation(const Orientation& o);

			void SetOrientation(const Scale& s);

			ModelMatrix GetModelMatrix();

		private:
			void UpdateModelMatrix();

		};
	}
}