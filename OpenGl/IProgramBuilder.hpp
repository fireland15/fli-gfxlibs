#pragma once

#include <memory>

#include "IShader.hpp"

namespace OpenGL {

	class IShader;
	class IProgram;

	class IProgramBuilder {
	public:
		virtual ~IProgramBuilder() { }

		/// <summary>
		/// Resets defaults to create new program
		/// </summary>
		/// <returns>The program builder</returns>
		virtual IProgramBuilder& NewProgram() = 0;

		/// <summary>
		/// Attaches the shader to the program
		/// </summary>
		/// <param name="shader">The shader to attach to the program</param>
		/// <returns>The program builder</returns>
		virtual IProgramBuilder& Attach(IShader& shader) = 0;

		/// <summary>
		/// Links and builds the program. Detaches shaders when complete
		/// </summary>
		/// <typeparam name="IProgram"></typeparam>
		/// <returns></returns>
		/// <exception cref="ProgramLinkException"></exception>
		virtual std::unique_ptr<IProgram> Build() = 0;
	};

}