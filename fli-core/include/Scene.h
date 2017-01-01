#pragma once

#include <vector>
#include <map>
#include <functional>

#include <Entity.h>
#include <Handle.h>
#include <TransformComponent.h>
#include <StaticRenderMeshComponent.h>
#include <DynamicRenderMeshComponent.h>
#include <MisdirectContainer.h>

namespace fli {
	namespace gfx {
		namespace core {
			typedef Handle EntityKey;

			class Scene {
			private:
				bool m_allocContainers = false;
				IContainer<TransformComponent>& m_transformComponents;
				IContainer<StaticRenderMeshComponent>& m_staticRenderMeshComponents;
				IContainer<DynamicRenderMeshComponent>& m_dynamicRenderMeshComponents;
				IContainer<Entity>& m_entities;

			public:
				Scene() 
					: m_transformComponents(*(new MisdirectContainer<TransformComponent>()))
					, m_staticRenderMeshComponents(*(new MisdirectContainer<StaticRenderMeshComponent>()))
					, m_dynamicRenderMeshComponents(*(new MisdirectContainer<DynamicRenderMeshComponent>()))
					, m_entities(*(new MisdirectContainer<Entity>())) { 
					m_allocContainers = true;
				}

				Scene(
					IContainer<TransformComponent>& modelComponentContainer, 
					IContainer<StaticRenderMeshComponent>& staticMeshComponentContainer,
					IContainer<DynamicRenderMeshComponent>& dynamicMeshComponentContainer,
					IContainer<Entity>& entityContainer)
					: m_transformComponents(modelComponentContainer)
					, m_staticRenderMeshComponents(staticMeshComponentContainer)
					, m_dynamicRenderMeshComponents(dynamicMeshComponentContainer)
					, m_entities(entityContainer) { }

				~Scene() {
					if (m_allocContainers) {
						delete & m_transformComponents;
						delete & m_staticRenderMeshComponents;
						delete & m_dynamicRenderMeshComponents;
						delete & m_entities;
					}
				}

				EntityKey CreateEntity() {
					Entity newEntity;
					return m_entities.Add(newEntity);
				}

				Entity& GetEntity(const EntityKey key) {
					return m_entities.Get(key);
				}

				void DeleteEntity(EntityKey& key) {
					DeleteTransformComponentFor(key);

					m_entities.Remove(key);
				}

				size_t Size() {
					return m_entities.Size();
				}

				TransformComponent& GetTransformComponentFor(const EntityKey entityKey) {
					Entity entity = m_entities.Get(entityKey);
					return m_transformComponents.Get(entity.TransformHandle);
				}

				void AddTransformComponentFor(const EntityKey entityKey, TransformComponent transfromComponent) {
					Handle h = m_transformComponents.Add(transfromComponent);
					m_entities.Get(entityKey).TransformHandle = h;
				}

				void DeleteTransformComponentFor(const EntityKey entityKey) {
					Handle h = m_entities.Get(entityKey).TransformHandle;
					if (h.IsValid()) {
						m_transformComponents.Remove(h);
					}
				}

				std::vector<EntityKey> GetEntitiesWhere(std::function<bool(Entity)> predicate) {
					return m_entities.Filter(predicate);
				}
			};
		}
	}
}