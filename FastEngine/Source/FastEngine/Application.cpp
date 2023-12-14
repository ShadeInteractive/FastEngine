#include "fepch.h"
#include "Application.h"
#include "Input.h"
#include <glad/glad.h>

#include "Renderer/Buffer.h"


namespace FastEngine
{
	static unsigned int CompileShaderStatic(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
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
			std::string error = "Failed to compile " + shaderTypeStr;
			FE_CORE_ERROR(error);
			FE_CORE_ERROR(message);
			glDeleteShader(id);
			return 0;
		}
		return id;
	}

	static unsigned int CreateShader(const std::string&  vectexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShaderStatic(GL_VERTEX_SHADER, vectexShader);
		unsigned int fs = CompileShaderStatic(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
		return program;
	}

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FE_CORE_ASSERT(!s_Instance,  "Application already exists.")
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create(WidowProperties("test", 720, 720)));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		
		float triangleVertices[3*3] = {
			-0.75f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		
		std::vector<BufferElement> element = {
			{ShaderDataType::Float3, "a_Position"}
		};
		BufferLayout layout(element);
		//m_VertexBuffer->SetLayout(layout);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); //Explain to the gpu how the current data is layout


		glGenBuffers(1, &m_TriangleIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TriangleIndexBuffer);

		uint32_t triangleIndices[3] = {0, 1, 2};
		m_IndexBuffer.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices)/ sizeof(uint32_t)));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);

		glBindVertexArray(m_VertexArrays[1]); // Bind the second vertex array

		glGenBuffers(1, &m_SquareVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER , m_SquareVertexBuffer);

		float squareVertices[4*3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		//glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//glGenBuffers(1, &m_SquareIndexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SquareIndexBuffer);

		unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

		//layout(location = 0) -> specify that the attribute we are looking for is at index 0
		//-> 0 should match with glVertexAttribPointer(0 
		// vec4 is by defaut a postiion inside open gl
		// our Vector3 is converted automatically to vec4
		std::string vertexShader = 
			"#version 330 core\n"
			"\n"
			"layout(location = 0) in vec3 a_Position;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(a_Position, 1.0);\n"
			"}\n";

		std::string vertexShader2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";
		
		// int is 4 bytes from 	0 to 4294967295 -> 
		m_Shader.reset(new Shader(vertexShader2, fragmentShader));
		m_Shader.get()->Bind();
		//m_Shader_old = CreateShader(vertexShader, fragmentShader);
		//glUseProgram(m_Shader_old);
		//glBindVertexArray(0);


	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while(m_Running)
		{
			//FE_CORE_TRACE("Test {0}", 1);

			glClearColor(0.1,0.1,0.1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(m_VertexArrays[0]);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			glBindVertexArray(m_VertexArrays[1]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			//FE_CORE_LOG("Test");
			//glad_glBindVertexArray(m_VertexArray);
			//glad_glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();

			//bool aPressed = Input::IsKeyPressed(FE_KEY_A);
			//FE_TRACE("A pressed {0} ", aPressed);
		}

		//glDeleteProgram(m_Shader);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		if(e.GetEventType() == WindowCloseEvent::GetStaticType())
		{
			//Gets address of an event(type Event) and Type cast it as a point of type WindowCloseEvent. 
			//!!We should be sure it's that type otherwise it's not going to work. 
			WindowCloseEvent* my_close_event = (WindowCloseEvent *) &e;
			OnWindowClosed(*my_close_event);
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.Handled)
				break;

		}
		
		FE_CORE_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}