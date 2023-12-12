#include "fepch.h"
#include "Shader.h"
#include <glad/glad.h>

namespace FastEngine
{
	Shader::Shader(const std::string& vertexSrc, const std::string& framgentSrc)
	{
		uint32_t program = glCreateProgram();
		uint32_t vs = this->CompileShader(GL_VERTEX_SHADER, vertexSrc);
		uint32_t fs = this->CompileShader(GL_FRAGMENT_SHADER, framgentSrc);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
		m_RendererID = program;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
	{
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glad_glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE)
		{
			int length;
			glad_glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			//This stored message on the stack as it allocates beforehand the size of the pointer. If using n
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);

			std::string shaderTypeStr = "vertex";
			if(type != GL_VERTEX_SHADER)
			{
				shaderTypeStr = "fragment";
			}
			glDeleteShader(id);

			std::string error = "Failed to compile " + shaderTypeStr;
			FE_CORE_ERROR(message);
			FE_CORE_ASSERT(false, error);
			return 0;
		}
		return id;
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}