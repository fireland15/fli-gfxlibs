#pragma once

#include <memory>
#include <vector>

#include "Scene.h"
#include "DrawCall.h"
#include "RenderBatch.h"

class IBatchOptimizer {
public:
	virtual std::vector<RenderBatch> operator()(std::vector<DrawCall>& drawCalls) = 0;
};