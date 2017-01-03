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
				std::unordered_map<std::type_index, bool> m_allocations;
				std::unordered_map<std::type_index, IContainer*> m_components;
				IContainerT<Entity>& m_entities;
				bool m_allocatedEntitiesContainer = false;

			public:
				Scene()
					: m_entities(*(new MisdirectContainer<Entity>())) {
						m_allocatedEntitiesContainer = true;

						AllocateContainer<MisdirectContainer, TransformComponent>();
						AllocateContainer<MisdirectContainer, StaticRenderMeshComponent>();
						AllocateContainer<MisdirectContainer, DynamicRenderMeshComponent>();
						
						/*m_components[typeid(TransformComponent)] = *(new MisdirectContainer<TransformComponent>());
						m_allocations[typeid(TransformComponent)] = true;

						m_components[typeid(StaticRenderMeshComponent)] = *(new MisdirectContainer<StaticRenderMeshComponent>());
						m_allocations[typeid(StaticRenderMeshComponent)] = true;

						m_components[typeid(DynamicRenderMeshComponent)] = *(new MisdirectContainer<DynamicRenderMeshComponent>());
						m_allocations[typeid(DynamicRenderMeshComponent)] = true;*/
				}

				~Scene() {
					for (auto x : m_components) {
						if (m_allocations.count(x.first) > 0 && m_allocations[x.first]) {
							delete m_components[x.first];
						}
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
					Handle h = entity.GetComponent<TComponent>();

					IContainer* c = m_components[typeid(TComponent)];
					IContainerT<TComponent>* container = static_cast<IContainerT<TComponent>>(c);
					return container->Get(h);
				}

				template<typename TComponent>
				void AddComponentFor(const EntityKey entityKey, TComponent component) {
					/*Handle h = m_transformComponents.Add(component);
					m_entities.Get(entityKey).hTransform = h;*/
				}

				template<typename TComponent>
				void DeleteComponentFor(const EntityKey entityKey) {
					/*Handle h = m_entities.Get(entityKey).hTransform;
					if (h.IsValid()) {
						m_transformComponents.Remove(h);
					}*/
				}

				/*************************************************************
				* Entity Querying Methods
				**************************************************************/

				std::vector<EntityKey> GetEntitiesWhere(std::function<bool(Entity)> predicate) {
					return m_entities.Filter(predicate);
				}

			private:
				template<template<typename> class TContainer, typename T>
				void AllocateContainer() {
					// Clean up old container before allocating a new one if there is an old container
					// Todo: May be necessary to copy contents over one day.
					if (m_components.count(typeid(T)) > 0) {
						if (m_allocations[typeid(T)] == true) {
							delete m_components[typeid(T)];
						}
					}

					m_components[typeid(T)] = new TContainer<T>();
					m_allocations[typeid(T)] = true;
				}
			};
		}
	}
}