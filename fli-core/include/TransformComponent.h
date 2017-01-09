#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtx\quaternion.hpp>

typedef glm::vec4 Position;
typedef glm::quat Orientation;
typedef glm::vec4 Scale;
typedef glm::mat4 ModelMatrix;
typedef glm::mat4 TranslationMatrix;
typedef glm::mat4 RotationMatrix;
typedef glm::mat4 ScaleMatrix;

namespace fli {
	namespace gfx {
		namespace core {
			class TransformComponent {
			private:
				Position m_position;
				Orientation m_orientation;
				Scale m_scale;
				ModelMatrix m_modelMatrix;

			public:
				TransformComponent() {
					SetPosition(Position(0.0F, 0.0F, 0.0F, 1.0F));
					SetOrientation(Orientation());
				}

				Position GetPosition() { return m_position; }

				Orientation GetOrientation() { return m_orientation; }

				Scale GetScale() { return m_scale; }

				void SetPosition(const Position& p) {
					m_position = p;
					UpdateModelMatrix();
				}

				void SetOrientation(const Orientation& o) {
					m_orientation = o;
					UpdateModelMatrix();
				}

				void SetOrientation(const Scale& s) {
					m_scale = s;
					UpdateModelMatrix();
				}

				ModelMatrix GetModelMatrix() { return m_modelMatrix; }

			private:
				void UpdateModelMatrix() {
					TranslationMatrix translate = glm::translate(glm::vec3(m_position.x, m_position.y, m_position.z));
					RotationMatrix rotate = glm::toMat4(m_orientation);
					ScaleMatrix scale = glm::scale(glm::vec3(m_scale.x, m_scale.y, m_scale.z));
					m_modelMatrix = translate * rotate * scale;
				}
			};
		}
	}
}