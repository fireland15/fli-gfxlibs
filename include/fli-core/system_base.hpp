#pragma once

#include <string>
#include <memory>

#include <fli-utility\log_entry.hpp>
#include <fli-utility\logger_base.hpp>

#include "scene.hpp"
#include "isystem.hpp"
#include "event_router.hpp"

namespace core {
		
	class SystemBase : public ISystem {
	protected:
		std::string m_systemName;

		std::shared_ptr<logging::LoggerBase> m_pLogger;

		std::shared_ptr<EventRouter> m_pEventRouter;

	public:
		SystemBase(
			std::string systemName, 
			std::shared_ptr<logging::LoggerBase> pLogger, 
			std::shared_ptr<EventRouter> pEventRouter);

		virtual void Setup(Scene& scene) = 0;

		virtual void Initialize() = 0;

		virtual void Update(Scene& scene, double time) = 0;

		virtual void Stop() = 0;

	protected:
		void Log(const std::string& msg, logging::LogLvl lvl = logging::LogLvl::all);

		void Log(const std::string& msg, const std::string& details, logging::LogLvl lvl = logging::LogLvl::all);

		virtual void RegisterForEvents() = 0;
	};

}