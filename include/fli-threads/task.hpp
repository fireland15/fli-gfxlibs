#pragma once

#include <functional>

namespace threading {

	class Task {
	public:
		template<typename TFunction, typename... TArgs>
		Task(TFunction f, TArgs&&... args) {
			m_function = std::bind(f, std::forward<TArgs>(args)...);
		}

		void Execute();

	private:
		std::function<void()> m_function;
	};

}