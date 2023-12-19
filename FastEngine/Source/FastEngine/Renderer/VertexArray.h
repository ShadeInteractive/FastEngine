#pragma once

#include "FastEngine/Core.h"
#include "Buffer.h"

#include <memory>


namespace FastEngine {

	class VertexArray
	{
	public:
		virtual ~VertexArray () {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		/*
			return a const reference to a shared pointer stored in index buffer
		*/
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		/* 
		* We use const in parameter to make sure that the function is not modifying the parameter
		*/
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		static VertexArray* Create();
	};

}