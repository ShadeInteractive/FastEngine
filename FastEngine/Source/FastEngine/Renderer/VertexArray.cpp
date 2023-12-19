
#include "fepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace FastEngine
{

	VertexArray* VertexArray::Create()
	{
		switch(Renderer::GetRendererAPI())
		{
			case RendererAPI::None: FE_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();

		}

		FE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}