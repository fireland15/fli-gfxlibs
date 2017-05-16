#pragma once

namespace OpenGL {

	struct PixelRGBf {
		union {
			float r;
			float g;
			float b;
		};
	};

}