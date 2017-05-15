#pragma once

#include <Windows.h>

namespace OpenGL {

	class IWindowsGLProvider {
	public:
		/// <summary>
		/// Makes a specified OpenGL rendering context the calling thread's current rendering context
		/// </summary>
		/// <param name="hdc">Handle to a device context</param>
		/// <param name="hglrc">Handle to an OpenGL rendering context that the function sets as the calling thread's rendering context</param>
		/// <returns>Whether the operation succeeded</returns>
		virtual bool MakeCurrent(HDC hdc, HGLRC hglrc) = 0;

		/// <summary>
		/// Deletes a specified OpenGL rendering context
		/// </summary>
		/// <param name="hglrc">Handle to an OpenGL rendering context that will be deleted</param>
		virtual void DeleteContext(HGLRC hglrc) = 0;

		/// <summary>
		/// Creates a new OpenGL rendering context which is suitable frawing on the device referenced by hdc
		/// </summary>
		/// <param name="hdc">Handle to a device context for which the function creates a suitable OpenGL rendering context</param>
		virtual HGLRC CreateContext(HDC hdc) = 0;
	};

}