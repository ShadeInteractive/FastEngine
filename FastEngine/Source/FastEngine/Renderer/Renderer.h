#pragma once


namespace FastEngine
{
	enum class RendererAPI
	{
		None=0, OpenGL = 1		
	};

	class Renderer
	{
	public: 
		inline static RendererAPI GetRendererAPI(){return s_rendererAPI;};
	private:
		static RendererAPI s_rendererAPI;
	};
}