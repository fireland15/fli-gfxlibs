#pragma once

#include <list>

#include <configuration.hpp>

#include "Scene.h"
#include "ISystem.h"
#include "IRenderer.h"

namespace fli {
	namespace gfx {
		namespace core {
			class Engine {
			private:
				util::config::Configuration& m_config;
				std::list<ISystem*> m_systems;
				std::list<IRenderer*> m_renderers;
				Scene m_scene;

				bool m_run = false;

			public:
				Engine(fli::util::config::Configuration& configuration) 
					: m_config(configuration) {

					bool configResult = true;

					if (!configResult) {
						throw std::exception("Could not read expected values from configuration.");
					}
				}

				void Initialize() {
					for (ISystem* system : m_systems) {
						system->Setup(m_scene, m_config);
					}

					for (ISystem* system : m_systems) {
						system->Initialize();
					}
				}

				/*************************************************************
				* Main Loop Methods
				**************************************************************/

				void Run() {
					double timestep = 30.0;
					m_run = true;

					// Todo: Find out how to do loop more betterer
					while (m_run) {
						UpdateSystems(timestep);
						Render(timestep);
					}
				}

				void Run(std::function<void(Engine&)> mainLoop) {
					mainLoop(*this);
				}

				void UpdateSystems(double time) {
					for (ISystem* s : m_systems) {
						s->Update(m_scene, time);
					}
				}

				void Render(double time) {
					for (IRenderer* r : m_renderers) {
						r->Render(m_scene, time);
					}
				}

				/*************************************************************
				* System Management Methods
				**************************************************************/

				void AddSystem(ISystem* system) {
					if (system == nullptr) {
						throw std::exception("System cannot be null.");
					}
					m_systems.push_back(system);
				}

				void AddRenderer(IRenderer* renderer) {
					if (renderer == nullptr) {
						throw std::exception("System cannot be null.");
					}
					m_renderers.push_back(renderer);
				}

			private:
				void StartSystems() {
					for (ISystem* system : m_systems) {
						system->Initialize();
					}
				}
			};
		}
	}
}