#include "fepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

namespace FastEngine
{
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch(Renderer::GetRendererAPI())
		{
			case RendererAPI::None: FE_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);

		}
		
		FE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch(Renderer::GetRendererAPI())
		{
		case RendererAPI::None: FE_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);

		}

		FE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}