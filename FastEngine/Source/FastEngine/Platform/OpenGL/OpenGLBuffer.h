#pragma once
#include "FastEngine/Renderer/Buffer.h"

namespace FastEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual OpenGLVertexBuffer() {}

		// Inherited via VertexBuffer
		virtual void Bind() const override;

		virtual void Unbind() const override;
	private:
		unint32_t m_RendererID;
	};

}