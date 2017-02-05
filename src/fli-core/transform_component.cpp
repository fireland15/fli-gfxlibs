#include "transform_component.hpp"

namespace core {

	TransformComponent::TransformComponent() {
		SetPosition(Position(0.0F, 0.0F, 0.0F, 1.0F));
		SetOrientation(Orientation());
	}

	Position 
	TransformComponent::GetPosition() { 
		return m_position; 
	}

	Orientation 
	TransformComponent::GetOrientation() { 
		return m_orientation; 
	}

	Scale 
	TransformComponent::GetScale() { 
		return m_scale; 
	}

	void 
	TransformComponent::SetPosition(const Position& p) {
		m_position = p;
		UpdateModelMatrix();
	}

	void 
	TransformComponent::SetOrientation(const Orientation& o) {
		m_orientation = o;
		UpdateModelMatrix();
	}

	void 
	TransformComponent::SetOrientation(const Scale& s) {
		m_scale = s;
		UpdateModelMatrix();
	}

	ModelMatrix 
	TransformComponent::GetModelMatrix() { return m_modelMatrix; }

	void 
	TransformComponent::UpdateModelMatrix() {
		TranslationMatrix translate = glm::translate(glm::vec3(m_position.x, m_position.y, m_position.z));
		RotationMatrix rotate = glm::toMat4(m_orientation);
		ScaleMatrix scale = glm::scale(glm::vec3(m_scale.x, m_scale.y, m_scale.z));
		m_modelMatrix = translate * rotate * scale;
	}

}