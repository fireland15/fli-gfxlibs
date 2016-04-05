#pragma once

#include <memory>
#include <exception>

#include "RenderPipelineBase.h"
#include "IDrawCallGenerator.h"
#include "IDrawCallOrganizer.h"
#include "IBatchOptimizer.h"
#include "Scene.h"


template <typename BatchOptimizer>
class BatchPipeline : public RenderPipelineBase {
private:
	std::unique_ptr<IDrawCallGenerator> m_pGenerator;
	std::unique_ptr<IDrawCallOrganizer> m_pOrganizer;
	std::unique_ptr<IBatchOptimizer>	m_pOptimizer;

	bool m_initialized;

public:
	BatchPipeline() {
		m_pGenerator = nullptr;
		m_pOrganizer = nullptr;
		m_pOptimizer = nullptr;
		m_initialized = false;
	}

	~BatchPipeline() {

	}

	void SetGenerator(std::unique_ptr<IDrawCallGenerator> pGenerator) {
		m_pGenerator = pGenerator;
	}

	void SetOrganizer(std::unique_ptr<IDrawCallOrganizer> pOrganizer) {
		m_pOrganizer = pOrganizer;
	}

	void SetOptimizer(std::unique_ptr<BatchOptimizer> pOptimizer) {
		m_pOptimizer = pOptimizer;
	}

	virtual void Execute(std::unique_ptr<Scene> pScene) {
		if (!m_initialized) {	// Each time this code gets looped through, we only need to call one comparison, not 3
			if (!m_pGenerator) throw std::exception("Generator not set in RenderPipeline");
			if (!m_pOrganizer) throw std::exception("Organizer not set in RenderPipeline");
			if (!m_pOptimizer) throw std::exception("Optimizer not set in RenderPipeline");
			m_initialized = true;
		}

		std::vector<DrawCall> drawCalls = (*m_pGenerator)(pScene);
		std::vector<DrawCall> organizedDrawCalls = (*m_pOrganizer)(pScene);

	}
};