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
			};
		}
	}
}