#pragma once
#include "FastEngine/Renderer/Buffer.h"

namespace FastEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public: 
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
		
	public: 
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);

		virtual ~OpenGLIndexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID, m_Count;
	
	};

}