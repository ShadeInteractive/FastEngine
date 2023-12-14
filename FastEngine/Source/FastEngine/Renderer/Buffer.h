#pragma once

namespace FastEngine
{
	enum class ShaderDataType{
		None = 0, Float, Float2, Float3, Float4, Boolean
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type){
		switch (type)
		{
			case ShaderDataType::Float:   return 4;
			case ShaderDataType::Float2:  return 4 * 2;
			case ShaderDataType::Float3:  return 4 * 3;
			case ShaderDataType::Float4:  return 4 * 4;
			case ShaderDataType::Boolean: return 4;
		}

		FE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	/*
	*	This represents the layout of type of data that is contained inside Buffer layout.
		Stores name, type, size, offset of a buffer element
	*/
	class BufferElement {
		
		public:
			std::string Name;
			ShaderDataType Type;
			uint32_t Size; //we use uint32_t to garantee that the size is exactly 32 bits on any platform.
			uint32_t Offset;

			BufferElement(ShaderDataType type, std::string name)
				: Type(type),Name(name), Size(ShaderDataTypeSize(type)), Offset(0)
			{
			}
			
	};

	class BufferLayout {
	public:
		BufferLayout(std::vector<BufferElement>) {}
		inline const std::vector<BufferElement>& GetElements() { return m_Elements; } //use const to certify that this method is not going to modify the object. Return reference in order to avoid copy. 
	private:
		std::vector<BufferElement> m_Elements;
		
	};

	/*
		Vertex array (buffer) is data stored on the GPU. This data is a mix of vertices, indices, ... 
		Once vertex buffer is on the gpu we can call the gpu to render this vertex buffer
	*/
	class VertexBuffer
	{
		public:
			virtual ~VertexBuffer () {}
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			static VertexBuffer* Create(float* vertices, uint32_t size);

	};	

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer () {}
		//const means that this member function makes the promise to not modify the object it's called from. 
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	
	};
}
