#pragma once

#include "IWinGdiWrapper.hpp"

namespace OpenGL {

	class WinGdiWrapper : public IWinGdiWrapper {
	public:
		virtual bool SwapBuffer(HDC hdc) override;

		virtual int SelectPixelFormat(HDC hdc, unsigned long flags, unsigned char pixelType, unsigned char colorBits, unsigned char alphaBits, unsigned char accumBits, unsigned char depthBits, unsigned char stencilBits, unsigned char auxBuffers, unsigned char layerType) override;

		virtual bool AssignPixelFormat(HDC hdc, int pixelFormat, unsigned long flags, unsigned char pixelType, unsigned char colorBits, unsigned char alphaBits, unsigned char accumBits, unsigned char depthBits, unsigned char stencilBits, unsigned char auxBuffers, unsigned char layerType) override;
	};

}