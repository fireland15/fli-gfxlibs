#pragma once

#include "ITextureBuilder.hpp"
#include <TextureTargetEnum.hpp>

typedef unsigned char byte;

namespace OpenGL {
	class OpenGLWrapper;

	class TextureBuilder : public ITextureBuilder {
	public:
		TextureBuilder(OpenGLWrapper& gl);
		virtual ~TextureBuilder();
		virtual ITextureBuilder& NewTexture(TextureTarget target) override;
		virtual ITextureBuilder& Pixels(std::vector<glm::vec4> & pixels, glm::uvec2 dim, PixelFormat format) override;
		virtual ITextureBuilder& Pixels(std::vector<glm::uvec4> & pixels, glm::uvec2 dim, PixelFormat format) override;
		virtual ITextureBuilder& Pixels(std::vector<glm::vec3> & pixels, glm::uvec2 dim, PixelFormat format) override;
		virtual ITextureBuilder& Pixels(std::vector<glm::uvec3> & pixels, glm::uvec2 dim, PixelFormat format) override;
		virtual ITextureBuilder& WithLinearFilters() override;
		virtual ITextureBuilder& WithNearestFilters() override;
		virtual ITextureBuilder& ClampEdges() override;
		virtual ITextureBuilder& BorderColor(glm::vec4& color) override;
		virtual ITextureBuilder& Repeat() override;
		virtual ITextureBuilder& MirroredRepeat() override;
		virtual std::unique_ptr<ITexture> Build() override;

	private:
		enum class PixelType {
			Double,
			Float,
			UInt,
			UShort,
			Byte
		};

		enum class FilterType {
			Linear,
			Nearest
		};

		enum class WrapType {
			ClampEdge,
			BorderColor,
			Repeat,
			MirroredRepeat
		};

		OpenGLWrapper& _gl;

		std::vector<byte> _pixelData;
		glm::uvec2 _textureDim;

		PixelFormat _pixelFormat;
		PixelType _pixelType;
		FilterType _filterType;
		WrapType _wrapType;
		TextureTarget _textureTarget;
		glm::vec4 _borderColor;
	};
}