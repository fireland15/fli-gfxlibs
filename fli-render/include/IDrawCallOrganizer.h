#pragma once

#include <memory>
#include <vector>

#include "Scene.h"
#include "DrawCall.h"

class IDrawCallOrganizer {
public:
	virtual std::vector<DrawCall> operator()(std::vector<DrawCall>& drawCalls) = 0;
};