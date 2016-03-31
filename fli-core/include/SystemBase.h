#pragma once

class SystemBase {
public:
	virtual void Start() = 0;
	virtual void Update(double time) = 0;
	virtual void Stop() = 0;
};