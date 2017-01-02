#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <typeindex>
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
				std::unordered_map<std::type_index, IContainer&> m_components;
				IContainerT<Entity>& m_entities;

			public:
				Scene()
					: m_entities(*(new MisdirectContainer<Entity>())) {
					m_components[typeid(TransformComponent)] = *(new MisdirectContainer<TransformComponent>());
					m_components[typeid(StaticRenderMeshComponent)] = *(new MisdirectContainer<StaticRenderMeshComponent>());
					m_components[typeid(DynamicRenderMeshComponent)] = *(new MisdirectContainer<DynamicRenderMeshComponent>());
				}

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

				/*************************************************************
				* Component Methods
				**************************************************************/

				template<typename TComponent>
				TComponent& GetComponentFor(const EntityKey entityKey) {
					Entity entity = m_entities.Get(entityKey);
					if (!entity.HasComponent<TComponent>()) {
						throw std::exception("Cannot get component. Handle is invalid.");
					}
					return entity.GetComponent<TComponent>();
				}

				template<typename TComponent>
				void AddComponentFor(const EntityKey entityKey, TComponent component) {
					Handle h = m_transformComponents.Add(component);
					m_entities.Get(entityKey).hTransform = h;
				}

				template<typename TComponent>
				void DeleteComponentFor(const EntityKey entityKey) {
					Handle h = m_entities.Get(entityKey).hTransform;
					if (h.IsValid()) {
						m_transformComponents.Remove(h);
					}
				}

				/*************************************************************
				* Transform Component Methods
				**************************************************************/

				TransformComponent& GetTransformComponentFor(const EntityKey entityKey) {
					Entity entity = m_entities.Get(entityKey);
					if (!entity.hTransform.IsValid()) {
						throw std::exception("Cannot get component. Handle is invalid.");
					}
					return m_transformComponents.Get(entity.hTransform);
				}

				void AddComponentFor(const EntityKey entityKey, TransformComponent component) {
					Handle h = m_transformComponents.Add(component);
					m_entities.Get(entityKey).hTransform = h;
				}

				void DeleteTransformComponentFor(const EntityKey entityKey) {
					Handle h = m_entities.Get(entityKey).hTransform;
					if (h.IsValid()) {
						m_transformComponents.Remove(h);
					}
				}

				/*************************************************************
				* Dynamic Render Mesh Component Methods
				**************************************************************/

				DynamicRenderMeshComponent& GetDynamicRenderMeshComponentFor(const EntityKey key) {
					Entity entity = m_entities.Get(key);
					if (!entity.hDynamicRenderMesh.IsValid()) {
						throw std::exception("Cannot get component. Handle is invalid.");
					}
					return m_dynamicRenderMeshComponents.Get(entity.hDynamicRenderMesh);
				}

				void AddComponentFor(const EntityKey key, DynamicRenderMeshComponent component) {
					Handle h = m_dynamicRenderMeshComponents.Add(component);
					m_entities.Get(key).hDynamicRenderMesh = h;
				}

				void DeleteDynamicRenderMeshComponentFor(const EntityKey key) {
					Handle h = m_entities.Get(key).hDynamicRenderMesh;
					if (h.IsValid()) {
						m_dynamicRenderMeshComponents.Remove(h);
					}
				}

				/*************************************************************
				* Static Render Mesh Component Methods
				**************************************************************/

				StaticRenderMeshComponent& GetStaticRenderMeshComponentFor(const EntityKey key) {
					Entity entity = m_entities.Get(key);
					if (!entity.hStaticRenderMesh.IsValid()) {
						throw std::exception("Cannot get component. Handle is invalid.");
					}
					return m_staticRenderMeshComponents.Get(entity.hStaticRenderMesh);
				}

				void AddComponentFor(const EntityKey key, StaticRenderMeshComponent component) {
					Handle h = m_staticRenderMeshComponents.Add(component);
					m_entities.Get(key).hStaticRenderMesh = h;
				}

				void DeleteStaticRenderMeshComponentFor(const EntityKey key) {
					Handle h = m_entities.Get(key).hStaticRenderMesh;
					if (h.IsValid()) {
						m_staticRenderMeshComponents.Remove(h);
					}
				}

				/*************************************************************
				* Entity Querying Methods
				**************************************************************/

				std::vector<EntityKey> GetEntitiesWhere(std::function<bool(Entity)> predicate) {
					return m_entities.Filter(predicate);
				}
			};
		}
	}
}