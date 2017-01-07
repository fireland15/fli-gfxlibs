#include "stdafx.h"
#include "CppUnitTest.h"

#include <Scene.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fli {
	namespace gfx {
		namespace core {
			template<typename TComponent>
			class MockComponentContainer : public IContainerT<TComponent> {
				virtual TComponent& Get(const Handle&) {
					return TComponent();
				}

				virtual Handle Add(TComponent) {
					return Handle();
				}

				virtual void Remove(Handle&) {
					return;
				}
				virtual size_t Size() {
					return 0;
				}
			};

			TEST_CLASS(SceneTests) {
			public:
				TEST_METHOD(CreateEntityTest) {
					Scene container;

					EntityKey k = container.CreateEntity();

					Assert::AreEqual((size_t)1, container.Size());
				}

				TEST_METHOD(GetEntityWithInvalidKey) {
					Scene container;

					container.CreateEntity();

					auto func = [&container] {container.GetEntity(69); };

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(DeleteEntity) {
					Scene container;

					EntityKey k = container.CreateEntity();
					Assert::AreEqual((size_t)1, container.Size());

					container.DeleteEntity(k);
					Assert::AreEqual((size_t)0, container.Size());
				}

				TEST_METHOD(DeleteEntityWithInvalidKey) {
					Scene container;

					EntityKey k = container.CreateEntity();
					Assert::AreEqual((size_t)1, container.Size());

					auto func = [&container] { EntityKey k = 69; container.DeleteEntity(k); };
					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(AddComponent) {
					Scene scene;
					scene.AddComponent<TransformComponent>();

					EntityKey k = scene.CreateEntity();
					scene.AddComponentFor<TransformComponent>(k, TransformComponent());
					
					Assert::AreEqual((size_t)1, scene.Size());
				}

				TEST_METHOD(AddComponentWhenComponentAlreadyThere) {
					Scene scene;
					scene.AddComponent<TransformComponent>();

					EntityKey k = scene.CreateEntity();

					auto func = [&scene, &k] {
						scene.AddComponentFor<TransformComponent>(k, TransformComponent());
						scene.AddComponentFor<TransformComponent>(k, TransformComponent());
					};

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(DeleteComponent) {
					Scene scene;
					scene.AddComponent<TransformComponent>();

					EntityKey k = scene.CreateEntity();
					scene.AddComponentFor<TransformComponent>(k, TransformComponent());
					scene.DeleteComponentFor<TransformComponent>(k);

					Entity& e = scene.GetEntity(k);
					Assert::IsFalse(e.HasComponent<TransformComponent>());
				}

				TEST_METHOD(DeleteComponentWhenEntityDoesntHaveOne) {
					Scene scene;
					scene.AddComponent<TransformComponent>();

					EntityKey k = scene.CreateEntity();

					auto func = [&scene, &k] {
						scene.DeleteComponentFor<TransformComponent>(k);
					};

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(GetComponent) {
					Scene scene;
					scene.AddComponent<TransformComponent>();

					EntityKey k = scene.CreateEntity();
					scene.AddComponentFor<TransformComponent>(k, TransformComponent());

					TransformComponent& c = scene.GetComponentFor<TransformComponent>(k);
					c.SetPosition(Position(1.0F));

					TransformComponent res = scene.GetComponentFor<TransformComponent>(k);

					Assert::AreEqual(1.0F, res.GetPosition().x);
					Assert::AreEqual(1.0F, res.GetPosition().y);
					Assert::AreEqual(1.0F, res.GetPosition().z);
				}

				TEST_METHOD(GetComponentWhenNotThere) {
					Scene scene;
					scene.AddComponent<TransformComponent>();

					EntityKey k = scene.CreateEntity();

					auto func = [&scene, &k] {
						TransformComponent& c = scene.GetComponentFor<TransformComponent>(k);
					};

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(IsComponentInSceneNotInScene) {
					Scene scene;

					bool res = scene.IsComponentInScene<TransformComponent>();

					Assert::IsFalse(res);
				}

				TEST_METHOD(IsComponentInSceneInScene) {
					Scene scene;

					scene.AddComponent<TransformComponent>();

					bool res = scene.IsComponentInScene<TransformComponent>();

					Assert::IsTrue(res);
				}
			};
		}
	}
}