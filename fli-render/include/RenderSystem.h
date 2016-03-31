#pragma once

#include "SystemBase.h"
#include "logger_base.hpp"
#include "configuration.hpp"

typedef fli::util::log::LoggerBase LoggerBase;
typedef fli::util::config::Configuration Configuration;

class RenderSystem : public SystemBase {
private:
	LoggerBase* m_pLogger;
	Configuration* m_pConfig;

public:
	void SetLogger(LoggerBase* pLogger);
	void SetConfig(Configuration* pConfig);

	virtual void Start();
	virtual void Update(WorldState& worldState, double time);
	virtual void Stop();
};