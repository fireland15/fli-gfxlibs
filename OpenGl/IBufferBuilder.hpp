#pragma once

#include <functional>
#include <memory>

#include <BufferUsageEnum.hpp>
#include <BufferTargetEnum.hpp>

#include "IBuffer.hpp"

namespace OpenGL {

	class IBuffer;
	class IBufferDataBuilder;

	class IBufferBuilder {
	public:
		/// <summary>
		/// Virtual destructor
		/// </summary>
		/// <returns></returns>
		virtual ~IBufferBuilder() { };

		/// <summary>
		/// Begins the creation of a new buffer. Clears all internal state to default values when the builder has already been used for buffer creation.
		/// </summary>
		/// <returns>Reference to this builder</returns>
		virtual IBufferBuilder& NewBuffer() = 0;

		/// <summary>
		/// Sets the usage of the buffer to be built
		/// </summary>
		/// <param name="usage">The buffer's usage</param>
		/// <returns>Reference to this builder</returns>
		virtual IBufferBuilder& UsedFor(BufferUsage usage) = 0;

		/// <summary>
		/// Sets the target of the buffer to be built
		/// </summary>
		/// <param name="target">The buffer's target</param>
		/// <returns>Reference to this builder</returns>
		virtual IBufferBuilder& Targeting(BufferTarget target) = 0;

		/// <summary>
		/// Sets the data in the buffer to be built
		/// </summary>
		/// <param name="func">A function describing the data to be put in the buffer</param>
		/// <returns>Reference to this builder</returns>
		virtual IBufferBuilder& WithData(std::function<void(IBufferDataBuilder&)> func) = 0;

		/// <summary>
		/// Calls to OpenGl to create the buffer with the specified target, usage, and data.
		/// </summary>
		/// <returns>A unique pointer to the newly created buffer</returns>
		virtual std::unique_ptr<IBuffer> Build() = 0;
	};

}