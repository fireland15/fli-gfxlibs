#pragma once

#include <TextureTargetEnum.hpp>
#include <TextureParameterValueEnum.hpp>

namespace OpenGL {

	class Handle;

	class ITexture {
	public:
		virtual ~ITexture() { }

		/// <summary>
		/// Gets the OpenGL handle for the texture object
		/// </summary>
		/// <returns>The OpenGL handle</returns>
		virtual const Handle & Handle() = 0;

		/// <summary>
		/// Gets the texture's target
		/// </summary>
		/// <returns>The texture's target</returns>
		virtual TextureTarget Target() = 0;

		/// <summary>
		/// Binds the texture to the context
		/// </summary>
		virtual void Bind() = 0;

		/// <summary>
		/// Unbinds the te
		/// </summary>
		virtual void Unbind() = 0;

		/// <summary>
		/// Set the texture wrap in the S direction
		/// </summary>
		/// <param name="value"></param>
		virtual void SetWrapS(TextureParameterValue value) = 0;

		/// <summary>
		/// Set the texture wrap in the T direction
		/// </summary>
		/// <param name="value"></param>
		virtual void SetWrapT(TextureParameterValue value) = 0;

		/// <summary>
		/// Sets the magnification filter
		/// </summary>
		/// <param name="value"></param>
		virtual void SetMagFilter(TextureParameterValue value) = 0;

		/// <summary>
		/// Sets the minification filter
		/// </summary>
		/// <param name="value"></param>
		virtual void SetMinFilter(TextureParameterValue value) = 0;

		/// <summary>
		/// Tells the texture which Active texture slot it should bind to
		/// </summary>
		/// <param name="slot"></param>
		virtual void BindToSlot(unsigned int slot) = 0;
	};

}