#include "fepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FastEngine
{
	//////////////////////////////////////////
	//Vertex buffer
	//////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		//1= Number of buffer objects we want to create. //the renderer id of the created buffer. This variable is set by open gl when creating buffer
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); //Bind the buffer to the current context. GL_ARRAY_BUFFER: Buffer containing an array of vertices
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //Create and initilize buffer object
		
		//Old version of gl buffer creation.
		//glGenVertexArrays(2, m_VertexArrays); // Create two vertex arrays -> this method return the indexes of vertex arrays created
		//glBindVertexArray(m_VertexArrays[0]); // Bind (add to the current context) the first vertex array that will store triangle -> All consecutive actions will work on that context
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//////////////////////////////////////////
	//Index buffer
	//////////////////////////////////////////
	
	/*
	* @brief: Create an index buffer
	* 
	* @param indices: pointer to the indices array
	* @param size: size of the indices array
	*/
	OpenGLIndexBuffer::OpenGLIndexBuffer (uint32_t* indices, uint32_t count) 
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID); //Create a buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); //Bind the buffer to the current context // GL_ELEMENT_ARRAY_BUFFER: Buffer containing an array of indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW); //Create and initilize buffer object 
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}