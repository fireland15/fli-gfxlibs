#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <functional>

#include <fli-utility\handle.hpp>
#include <fli-utility\misdirect_container.hpp>

#include "entity.hpp"

namespace core {

	typedef containers::Handle EntityKey;

	class Scene {

	private:
		std::unordered_map<std::type_index, bool> m_allocations;
		std::unordered_map<std::type_index, containers::IContainer*> m_components;
		containers::IContainerT<Entity>& m_entities;
		bool m_allocatedEntitiesContainer = false;

	public:
		Scene();

		~Scene();

		EntityKey CreateEntity();

		Entity& GetEntity(const EntityKey key);

		void DeleteEntity(EntityKey& key);

		size_t Size();

		/*************************************************************
		* Component Methods
		**************************************************************/

		template<typename TComponent>
		TComponent& GetComponentFor(const EntityKey entityKey) {
			Entity& entity = m_entities.Get(entityKey);
			if (!entity.HasComponent<TComponent>()) {
				throw std::exception("Cannot get component. Entity does not have component.");
			}
			containers::Handle h = entity.GetComponent<TComponent>();
			containers::IContainerT<TComponent>* container = GetContainerFor<TComponent>();
			return container->Get(h);
		}

		template<typename TComponent>
		void AddComponentFor(const EntityKey& entityKey, TComponent component) {
			Entity& entity = m_entities.Get(entityKey);
			if (entity.HasComponent<TComponent>()) {
				throw std::exception("Cannot add component to entity. Not implemented.");
				// Todo: Remove old component and replace with new one
				// or copy contents
			}
			containers::IContainerT<TComponent>* container = GetContainerFor<TComponent>();
			containers::Handle h = container->Add(component);
			entity.AddComponent<TComponent>(h);
		}

		template<typename TComponent>
		void DeleteComponentFor(const EntityKey entityKey) {
			Entity& entity = m_entities.Get(entityKey);
			if (!entity.HasComponent<TComponent>()) {
				// Todo: decide what happens here
				throw std::exception("Cannot delete component from entity that does not have component");
			}
			containers::Handle h = entity.GetComponent<TComponent>();
			entity.DeleteComponent<TComponent>();
			containers::IContainerT<TComponent>* container = GetContainerFor<TComponent>();
			container->Remove(h);
		}

		/*************************************************************
		* Entity Querying Methods
		**************************************************************/

		std::vector<EntityKey> GetEntitiesWhere(std::function<bool(Entity)> predicate);

		/*************************************************************
		* Component Container Assignment Methods
		**************************************************************/

		template<typename TComponent>
		bool IsComponentInScene() {
			return m_components.count(typeid(TComponent)) > 0;
		}

		template<template<typename> class TContainer, typename TComponent>
		void AddComponent() {
			if (IsComponentInScene<TComponent>()) {
				throw std::exception("Component is already in scene.");
			}
			AllocateContainer<TContainer, TComponent>();
		}

		template<typename TComponent>
		void AddComponent() {
			if (IsComponentInScene<TComponent>()) {
				throw std::exception("Component is already in scene.");
			}
			AllocateContainer<containers::MisdirectContainer, TComponent>();
		}


	private:
		template<template<typename> class TContainer, typename T>
		void AllocateContainer() {
			static_assert(std::is_base_of<containers::IContainer, TContainer<T>>::value, "TContainer must inherit from fli::gfx::core::IContainer");

			// Clean up old container before allocating a new one if there is an old container
			// Todo: May be necessary to copy contents over one day.
			if (m_components.count(typeid(T)) > 0) {
				if (m_allocations[typeid(T)] == true) {
					delete m_components[typeid(T)];
				}
			}

			m_components[typeid(T)] = static_cast<containers::IContainer*>(new TContainer<T>());
			m_allocations[typeid(T)] = true;
		}

		template<typename TComponent>
		inline containers::IContainerT<TComponent>* GetContainerFor() {
			return static_cast<containers::IContainerT<TComponent>*>(m_components[typeid(TComponent)]);
		}
	};

}