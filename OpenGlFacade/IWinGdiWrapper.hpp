#pragma once

#include <Windows.h>
#include <windef.h>

namespace OpenGL {

	class IWinGdiWrapper {
	public:
		virtual ~IWinGdiWrapper() { }

		virtual bool SwapBuffer(HDC hdc) = 0;

		virtual int SelectPixelFormat(HDC hdc, unsigned long flags, unsigned char pixelType, unsigned char colorBits, unsigned char alphaBits, unsigned char accumBits, unsigned char depthBits, unsigned char stencilBits, unsigned char auxBuffers, unsigned char layerType) = 0;

		virtual bool AssignPixelFormat(HDC hdc, int pixelFormat, unsigned long flags, unsigned char pixelType, unsigned char colorBits, unsigned char alphaBits, unsigned char accumBits, unsigned char depthBits, unsigned char stencilBits, unsigned char auxBuffers, unsigned char layerType) = 0;
	};

}