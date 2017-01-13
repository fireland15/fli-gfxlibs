#include "scene.hpp"

namespace gfx {
	namespace core {

		Scene::Scene()
			: m_entities(*(new containers::MisdirectContainer<Entity>())) {
			m_allocatedEntitiesContainer = true;
		}

		Scene::~Scene() {
			for (auto x : m_components) {
				if (m_allocations.count(x.first) > 0 && m_allocations[x.first] == true) {
					delete m_components[x.first];
				}
			}
		}

		EntityKey Scene::CreateEntity() {
			Entity newEntity;
			return m_entities.Add(newEntity);
		}

		Entity& Scene::GetEntity(const EntityKey key) {
			return m_entities.Get(key);
		}

		void Scene::DeleteEntity(EntityKey& key) {
			m_entities.Remove(key);
		}

		size_t Scene::Size() {
			return m_entities.Size();
		}

		std::vector<EntityKey> Scene::GetEntitiesWhere(std::function<bool(Entity)> predicate) {
			return m_entities.Filter(predicate);
		}

	}
}