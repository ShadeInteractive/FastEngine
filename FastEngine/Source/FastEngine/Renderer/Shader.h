#pragma once

#include <string>

namespace FastEngine
{
	class Shader
	{
		public:
			Shader(const std::string& vertexSrc, const std::string& framgentSrc);
			~Shader();


			void Bind() const;
			void Unbind() const;

		private:
			uint32_t m_RendererID;

			uint32_t CompileShader(uint32_t type, const std::string& source);
	};

}
