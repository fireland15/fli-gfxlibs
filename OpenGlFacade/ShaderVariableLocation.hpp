#pragma once

namespace OpenGL {

	class ShaderVariableLocation {
	public:
		ShaderVariableLocation(int location);
		int Value();
	private:
		int _location;
	};

}