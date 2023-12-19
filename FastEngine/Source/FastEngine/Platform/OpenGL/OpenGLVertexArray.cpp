#include "fepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace FastEngine{
	
	static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float:   return GL_FLOAT;
		case ShaderDataType::Float2:  return GL_FLOAT;
		case ShaderDataType::Float3:  return GL_FLOAT;
		case ShaderDataType::Float4:  return GL_FLOAT;
		case ShaderDataType::Boolean: return GL_BOOL;
		}

		FE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID); // Bind the vertex array object to the current context. Context means the current state of the open gl
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0); // Set the VAO to default (0) so it will unbind the current VAO
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		FE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			/*
			* h: vertex attribute: A vertex attribute array corresponds to an element inside the buffer layout
			* h: glEnableVertexAttribArray: Enable a generic vertex attribute array so that it can be used during rendering. 
			*/
			glEnableVertexAttribArray(index);

			/*
			* h: glVertexAttribPointer: explains to the gpu how the current data is layout
			* h: TODO: understand the parameter (const void*)element.Offset)
			* documentation: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
			*/
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGlBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);

			index++;
		}
		// if we don't keep vertex buffer here, it's gonna be destroyed and so opengl is not going to keep it
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}