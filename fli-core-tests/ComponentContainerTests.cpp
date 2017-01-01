#include "stdafx.h"
#include "CppUnitTest.h"

#include <MisdirectContainer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fli {		
	namespace gfx {
		namespace core {
			TEST_CLASS(MisdirectContainerTests) {
			public:
				TEST_METHOD(TestAdd) {
					MisdirectContainer<int> container;
					container.Add(2);

					Assert::AreEqual((size_t)1, container.Size());
				}

				TEST_METHOD(TestGet) {
					MisdirectContainer<int> container;
					Handle h = container.Add(2);

					int result = container.Get(h);

					Assert::AreEqual(result, 2);

					h = container.Add(3);

					result = container.Get(h);
					Assert::AreEqual(result, 3);
				}

				TEST_METHOD(TestGetWithInvalidHandle) {
					MisdirectContainer<int> container;
					Handle h = container.Add(2);

					auto func = [&container] { container.Get(Handle(34)); };

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(TestRemove) {
					MisdirectContainer<int> container;
					Handle h[5];
					for (int i = 0; i < 5; i++) {
						h[i] = container.Add(i + 2);
					}

					Assert::AreEqual(container.Size(), (size_t)5);

					container.Remove(h[3]);

					Assert::AreEqual(container.Size(), (size_t)4);
					Assert::AreEqual(container.Get(h[0]), 2);
					Assert::AreEqual(container.Get(h[1]), 3);
					Assert::AreEqual(container.Get(h[2]), 4);
					Assert::AreEqual(container.Get(h[4]), 6);

					auto func = [&container, &h] { container.Get(h[3]); };

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(TestRemoveWithInvalidHandle) {
					MisdirectContainer<int> container;
					Handle h[5];
					for (int i = 0; i < 5; i++) {
						h[i] = container.Add(i + 2);
					}

					Assert::AreEqual(container.Size(), (size_t)5);

					auto func = [&container] {container.Remove(Handle(69)); };

					Assert::ExpectException<std::exception>(func);
				}

				TEST_METHOD(TestFilter) {
					MisdirectContainer<int> container;
					for (int i = 0; i < 10; i++) {
						container.Add(i);
					}

					std::vector<Handle> h = container.Filter([&](int j) -> bool { return j > 5; });

					Assert::AreEqual((size_t)4, h.size());
				}
			};
		}
	}
}