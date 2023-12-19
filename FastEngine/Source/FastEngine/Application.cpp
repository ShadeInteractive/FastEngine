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
		
		/*************************/
		/* Create triangle */
		/*************************/

		m_VertexArray.reset(VertexArray::Create());
		float triangleVertices[3*7] = {
			0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> m_VertexBufferTest;
		m_VertexBufferTest.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		
		/* h: this is a syntax allowed by std::initializer_list to create a list of elements of type BufferElement */
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};
		
		/* h: stores the layout inside the vertex buffer */
		
		m_VertexBufferTest->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBufferTest);
		
		uint32_t triangleIndices[6] = {0, 1, 2};
		std::shared_ptr<IndexBuffer> m_IndexBufferTest;
		m_IndexBufferTest.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices)/ sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBufferTest);
		
		/************************************************/
		/* Create square */
		/************************************************/
		//Create vertex array
		m_SquareVertexArray.reset(VertexArray::Create());
		float triangleVerticesTest[4*7] = {
			-0.80f, 0.80f, 0.0f,
			0.75f,  0.90f, 0.0f,
			0.75f,  -0.70f, 0.0f,
			-0.75f, -0.75f, 0.0f
		};
		//Create vertex buffer and connect layout inside it
		std::shared_ptr<VertexBuffer> m_VertexBufferTest2;
		m_VertexBufferTest2.reset(VertexBuffer::Create(triangleVerticesTest, sizeof(triangleVerticesTest)));

		BufferLayout layout2 = {
			{ShaderDataType::Float3, "a_Position"}
		};

		m_VertexBufferTest2->SetLayout(layout2);
		//Store vertex buffer inside the vertex array
		m_SquareVertexArray->AddVertexBuffer(m_VertexBufferTest2);
		
		//Create index buffer and store it inside vertex array
		/*
		* How to understand triangles indices:
		* it's gonna read vertex at index 0 then 1 then 2, then print the triangle.
		* then read vertex 2 then 3 then 0 in order to print the second triangle. 
		*/
		uint32_t triangleIndices2[6] = {0, 1, 2, 2, 3 , 0};
		std::shared_ptr<IndexBuffer> m_IndexBufferTest2;
		m_IndexBufferTest2.reset(IndexBuffer::Create(triangleIndices2, sizeof(triangleIndices2)/ sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(m_IndexBufferTest2);

		std::string vertexShader2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		
		// int is 4 bytes from 	0 to 4294967295 -> 
		m_Shader.reset(new Shader(vertexShader2, fragmentShader));

		std::string vertexShaderBlue = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderBlue = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_FlatColorShader.reset(new Shader(vertexShaderBlue, fragmentShaderBlue));
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

			m_FlatColorShader.get()->Bind();
			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader.get()->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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