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
	struct BufferElement {
		
		public:
			std::string Name;
			ShaderDataType Type;
			uint32_t Size; //we use uint32_t to garantee that the size is exactly 32 bits on any platform.
			uint32_t Offset;
			bool Normalized;

			uint32_t GetComponentCount() const
			{
				switch (Type)
				{
					case ShaderDataType::Float:   return 1;
					case ShaderDataType::Float2:  return 2;
					case ShaderDataType::Float3:  return 3;
					case ShaderDataType::Float4:  return 4;
					case ShaderDataType::Boolean: return 1;
				}

				FE_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			}

			BufferElement(ShaderDataType type, std::string name, bool normalized = false)
				: Type(type),Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
			{
			}
	};

	class BufferLayout {
	public:
		/* h: As soon as we implement a constructor with argument and start using a default constructor, we have to implement it manullay */
		BufferLayout() {}
		// what is std::initializer_list: easy way to pass a list of elements to a constructor
		// it is especially useful when using brace-enclosed {} initializer syntax.
		// https://en.cppreference.com/w/cpp/utility/initializer_list
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}
		/*
		* return the elements of the buffer layout
		* h: const in front means that user will not be able to modify the object
		* h: const in the end means that the method will not modify the object
		*/
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; } //use const to certify that this method is not going to modify the object. Return reference in order to avoid copy. 
		
		/* 
		* return the number of bytes between each element in the buffer 
		* h: it's useless to use const in front here because we are returning a value and not a reference
		*/
		inline uint32_t GetStride() const { return m_Stride; }

		/*
		* h: if I want to iterate over the elements of the buffer layout I can create iterators:
		* eg: for (auto& element : layout) ...
		*/
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		/* 
		* h: Inside the Vertex Buffer, GetLayout returns const BufferLayout& so we need to have const iterators
		* eg: for (auto& element : m_vertexBuffer->GetLayout()) ...
		*/
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}			
		}
	
	private:
		/* vector of buffer elements */
		std::vector<BufferElement> m_Elements;

		/* stride is the space between each element in the buffer. 
		Element is for example vertex (float3) + color(float4) + vertex color(float3) = 10 floats = 10 * 4 bytes = 40 bytes
		*/
		uint32_t m_Stride;
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

			virtual const BufferLayout& GetLayout() const = 0;
			virtual void SetLayout(const BufferLayout& layout) = 0;
			/*
			* Create a vertex buffer
			* 
			* @param vertices: pointer to the vertices array
			* @param size: size of the vertices array in bytes
			*/
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
