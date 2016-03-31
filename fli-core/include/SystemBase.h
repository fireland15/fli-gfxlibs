#pragma once

#include "WorldState.h"

class SystemBase {
public:
	virtual void Start() = 0;
	virtual void Update(WorldState& worldState, double time) = 0;
	virtual void Stop() = 0;
};