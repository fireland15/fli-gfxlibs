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
	RenderSystem();

	void SetLogger(LoggerBase* pLogger);
	void SetConfig(Configuration* pConfig);

	virtual void Initialize();
	virtual void Update(Scene& scene, double time);
	virtual void Stop();
};