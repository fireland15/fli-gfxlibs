#include "RenderSystem.h"

void RenderSystem::SetLogger(LoggerBase* pLogger) {
	m_pLogger = pLogger;
}

void RenderSystem::SetConfig(Configuration* pConfig) {
	m_pConfig = pConfig;
}

void RenderSystem::Start() {

}

void RenderSystem::Update(WorldState& worldState, double time) {

}

void RenderSystem::Stop() {

}
