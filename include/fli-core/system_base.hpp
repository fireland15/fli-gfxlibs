#pragma once

#include <string>
#include <memory>

#include <fli-utility\log_entry.hpp>
#include <fli-utility\logger_base.hpp>

#include "scene.hpp"
#include "isystem.hpp"

namespace gfx {
	namespace core {
		
		class SystemBase : public ISystem {
		protected:
			std::string m_systemName;

			logging::LoggerBase* m_pLogger;

		public:
			SystemBase();

			void SetLogger(logging::LoggerBase* pLogger);

			virtual void Setup(Scene& scene) = 0;
			virtual void Initialize() = 0;
			virtual void Update(Scene& scene, double time) = 0;
			virtual void Stop() = 0;

		protected:
			void Log(const std::string& msg, logging::LogLvl lvl = logging::LogLvl::all);

			void Log(const std::string& msg, const std::string& details, logging::LogLvl lvl = logging::LogLvl::all);
		};

	}
}