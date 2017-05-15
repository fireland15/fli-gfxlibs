#pragma once

#include "ShaderSource.hpp"
#include "IShader.hpp"

#include <ShaderTypeEnum.hpp>
#include <memory>

namespace OpenGL {

	class IShaderBuilder {
	public:
		virtual ~IShaderBuilder() { }

		/// <summary>
		/// Resets the builder to a default state to create new shaders
		/// </summary>
		/// <returns>The shader builder</returns>
		virtual IShaderBuilder& NewShader() = 0;

		/// <summary>
		/// Sets the type of the shader to create
		/// </summary>
		/// <param name="type">The shader type</param>
		/// <returns>The shader builder</returns>
		virtual IShaderBuilder& Type(ShaderType type) = 0;

		/// <summary>
		/// Adds a shader source to be compiled into the shader
		/// </summary>
		/// <param name="source">The shader source</param>
		/// <returns>The shader builder</returns>
		virtual IShaderBuilder& AddSource(ShaderSource source) = 0;

		/// <summary>
		/// Compiles the shaders source
		/// </summary>
		/// <returns>The shader builder</returns>
		/// <exception cref="ShaderCompilationException"></exception>
		virtual IShaderBuilder& Compile() = 0;

		/// <summary>
		/// Builds the shader
		/// </summary>
		/// <typeparam name="IShader"></typeparam>
		/// <returns>A unique pounter to the shader</returns>
		virtual std::unique_ptr<IShader> Build() = 0;
	};

}