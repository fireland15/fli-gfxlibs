#include "stdafx.h"
#include "CppUnitTest.h"

#include <Entity.h>
#include <TransformComponent.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fli {
	namespace gfx {
		namespace core {
			TEST_CLASS(EntityTests) {
			public:
				TEST_METHOD(TestHasComponent) {
					Entity e;
					bool b = e.HasComponent<TransformComponent>();
					Assert::IsFalse(b);
				}

				TEST_METHOD(TestHasComponentTrue) {
					Entity e;
					e.AddComponent<TransformComponent>(Handle(69));
					bool b = e.HasComponent<TransformComponent>();
					Assert::IsTrue(b);
				}
			};
		}
	}
}