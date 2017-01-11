#pragma once

#include <memory>
#include <vector>

#include "Scene.h"
#include "DrawCall.h"

class IDrawCallGenerator {
public:
	//virtual std::vector<DrawCall> operator()(std::unique_ptr<Scene> pScene) = 0;
};