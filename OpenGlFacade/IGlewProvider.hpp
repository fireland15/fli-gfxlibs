#pragma once

namespace OpenGL {

	class IGlewProvider {
	public:
		/// <summary>
		/// Initialize OpenGL extension entry points
		/// </summary>
		/// <returns>Status code of the operation</returns>
		virtual unsigned int Init() = 0;

		/// <summary>
		/// A way to expose GLEW_OK
		/// </summary>
		/// <returns>The value of GLEW_OK</returns>
		virtual unsigned int Ok() = 0;
	};

}