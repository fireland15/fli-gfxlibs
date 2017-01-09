#include "stdafx.h"
#include "CppUnitTest.h"

#include <Engine.h>
#include <ISystem.h>
#include <configuration.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fli {
	namespace gfx {
		namespace core {
			class MockConfigReader : public util::config::ConfigurationReaderBase {
			private:
				std::map<std::string, std::string> m_map;

			public:
				void Add(std::string key, std::string value) {
					m_map.insert(std::make_pair(key, value));
				}

				virtual std::map<std::string, std::string> GetConfigValues() {
					return m_map;
				}
			};

			class MockSystem : public ISystem {
			public:
				bool SetupCalled = false;
				bool InitializeCalled = false;
				virtual void Setup(Scene& scene, util::config::Configuration& config) { 
					SetupCalled = true;
				}
				virtual void Initialize() {
					InitializeCalled = true;
				}
				virtual void Update(Scene& scene, double time) { }
				virtual void Stop() { }
			};

			TEST_CLASS(EngineTests) {
			public:
				TEST_METHOD(TestConstruction) {
					MockConfigReader cfgrdr;
					cfgrdr.Add("timestep", "30.0");

					Engine e = Engine(util::config::Configuration(cfgrdr));
				}

				TEST_METHOD(InitializeCallsSetupForEachSystem) {
					MockConfigReader cfgrdr;
					cfgrdr.Add("timestep", "30.0");
					Engine e = Engine(util::config::Configuration(cfgrdr));

					MockSystem* mockSystem1 = new MockSystem();
					MockSystem* mockSystem2 = new MockSystem();
					MockSystem* mockSystem3 = new MockSystem();

					e.AddSystem((ISystem*)mockSystem1);
					e.AddSystem((ISystem*)mockSystem2);
					e.AddSystem((ISystem*)mockSystem3);

					e.Initialize();

					Assert::IsTrue(mockSystem1->SetupCalled);
					Assert::IsTrue(mockSystem2->SetupCalled);
					Assert::IsTrue(mockSystem3->SetupCalled);
				}

				TEST_METHOD(InitializeCallsInitializeForEachSystem) {
					MockConfigReader cfgrdr;
					cfgrdr.Add("timestep", "30.0");
					Engine e = Engine(util::config::Configuration(cfgrdr));

					MockSystem* mockSystem1 = new MockSystem();
					MockSystem* mockSystem2 = new MockSystem();
					MockSystem* mockSystem3 = new MockSystem();

					e.AddSystem((ISystem*)mockSystem1);
					e.AddSystem((ISystem*)mockSystem2);
					e.AddSystem((ISystem*)mockSystem3);

					e.Initialize();

					Assert::IsTrue(mockSystem1->InitializeCalled);
					Assert::IsTrue(mockSystem2->InitializeCalled);
					Assert::IsTrue(mockSystem3->InitializeCalled);
				}

				TEST_METHOD(RunCallsUpdate) {
					MockConfigReader cfgrdr;
					cfgrdr.Add("timestep", "30.0");
					Engine e = Engine(util::config::Configuration(cfgrdr));

					MockSystem* mockSystem1 = new MockSystem();
					MockSystem* mockSystem2 = new MockSystem();
					MockSystem* mockSystem3 = new MockSystem();

					e.AddSystem((ISystem*)mockSystem1);
					e.AddSystem((ISystem*)mockSystem2);
					e.AddSystem((ISystem*)mockSystem3);

					e.Initialize();

					Assert::IsTrue(mockSystem1->InitializeCalled);
					Assert::IsTrue(mockSystem2->InitializeCalled);
					Assert::IsTrue(mockSystem3->InitializeCalled);
				}
			};
		}
	}
}