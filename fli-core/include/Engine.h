#pragma once

#include <list>

#include <configuration.hpp>

#include "Scene.h"
#include "ISystem.h"
#include "IRenderer.h"
#include "Clock.h"

namespace fli {
	namespace gfx {
		namespace core {
			class Engine {
			private:
				util::config::Configuration& m_config;
				std::list<ISystem*> m_systems;
				std::list<IRenderer*> m_renderers;
				Scene m_scene;
				Clock m_clock;

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
					m_run = true;
					Clock::Timepoint t = m_clock.Now();
					Clock::Duration dt = m_clock.TimeFromEpoch(t);

					while (m_run) {
						double milliseconds = dt.Milliseconds();

						UpdateSystems(milliseconds);
						Render(milliseconds);

						dt = m_clock.Now() - t;
						t = m_clock.Now();
					}
				}

				/// Allows for a custom loop to be implemented from outside the engine class.
				void Run(std::function<void(Engine&)> mainLoop) {
					mainLoop(*this);
				}

				/// <summary>
				/// Calls each system's Update() method.
				/// </summary>
				/// <param name="time">The number of milliseconds to simulate in each system.</param>
				void UpdateSystems(double time) {
					for (ISystem* s : m_systems) {
						s->Update(m_scene, time);
					}
				}

				/// <summary>
				/// Calls each renderers render method.
				/// </summary>
				/// <param name="time">The number of milliseconds in the current timestep.</param>
				void Render(double time) {
					for (IRenderer* r : m_renderers) {
						r->Render(m_scene, time);
					}
				}

				/// <summary>
				/// Returns the current timepoint for the engine's clock.
				/// </summary>
				Clock::Timepoint Now() {
					return m_clock.Now();
				}

				void Stop() {
					for (ISystem* s : m_systems) {
						s->Stop();
					}

					for (IRenderer* r : m_renderers) {
						r->Stop();
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