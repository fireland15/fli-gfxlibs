#pragma once

#include "IGlewProvider.hpp"

namespace OpenGL {

	class GlewProvider : public IGlewProvider {
	public:
		virtual unsigned int Init() override;
		virtual unsigned int Ok() override;
	};

}