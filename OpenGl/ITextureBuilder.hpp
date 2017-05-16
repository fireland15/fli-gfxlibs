#pragma once

#include <memory>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\std_based_type.hpp>

#include "PixelFormatEnum.hpp"
#include <TextureTargetEnum.hpp>

namespace OpenGL {
	class ITexture;

	class ITextureBuilder {
	public:
		virtual ~ITextureBuilder() { }
		virtual ITextureBuilder& NewTexture(TextureTarget target) = 0;
		virtual ITextureBuilder& Pixels(std::vector<glm::vec4> & pixels, glm::uvec2 dim, PixelFormat format) = 0;
		virtual ITextureBuilder& Pixels(std::vector<glm::uvec4> & pixels, glm::uvec2 dim, PixelFormat format) = 0;
		virtual ITextureBuilder& Pixels(std::vector<glm::vec3> & pixels, glm::uvec2 dim, PixelFormat format) = 0;
		virtual ITextureBuilder& Pixels(std::vector<glm::uvec3> & pixels, glm::uvec2 dim, PixelFormat format) = 0;
		virtual ITextureBuilder& Pixels(std::vector<glm::u8vec4> & pixels, glm::uvec2 dim, PixelFormat format) = 0;
		virtual ITextureBuilder& Pixels(std::vector<glm::u8vec3> & pixels, glm::uvec2 dim, PixelFormat format) = 0;
		virtual ITextureBuilder& WithLinearFilters() = 0;
		virtual ITextureBuilder& WithNearestFilters() = 0;
		virtual ITextureBuilder& ClampEdges() = 0;
		virtual ITextureBuilder& BorderColor(glm::vec4& color) = 0;
		virtual ITextureBuilder& Repeat() = 0;
		virtual ITextureBuilder& MirroredRepeat() = 0;
		virtual std::unique_ptr<ITexture> Build() = 0;
	};
}