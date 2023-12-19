#include <FastEngine.h>
#include <bitset>
#include "CppLearning/PointersLearning.h"



extern int my_external_var;


class TestLayer : public FastEngine::Layer
{
public:
	TestLayer()
		:Layer("Example")
	{}

	inline void OnUpdate()
	{
		if(FastEngine::Input::IsKeyPressed(FE_KEY_TAB))
			FE_TRACE("Tab key pressed. KeyCode= {0}", FE_KEY_TAB);
	}

	void OnEvent(FastEngine::Event& event) override
	{
		//FE_TRACE("{0}", event);
	}
};

class TestLayer2 : public FastEngine::Layer
{
public:
	TestLayer2()
		:Layer("Example2")
	{}

	void OnEvent(FastEngine::Event& event) override
	{
		
		//FE_TRACE("{0}", event);
	}
};


//This extern is not mandatory 
//because definition is happening here.
extern const char* valueDefinedInProject = "Sandbox";

class Sandbox : public FastEngine::Application
{
	public:
		Sandbox()
		{
			//PushLayer(new TestLayer());
			//PushLayer(new TestLayer2());
			PushOverlay(new FastEngine::ImGuiLayer());
		}

		~Sandbox()
		{
		
		}

};

int user_main_in_app()
{
	const int to_shift_a = 1;
	const int b = 2;
	const int c = 3;

	std::bitset<8> a_bit = std::bitset<8>(to_shift_a);
	std::cout << "a = " << to_shift_a << " a_bit = " << a_bit << "\n";
	
	const int shift_0 = 0;
	const int shift_1 = 1;
	const int shift_2 = 2;
	const int shift_3 = 3;
	const int shift_4 = 4;
	
	int shifted_0 = to_shift_a << shift_0;
	std::bitset<8> shifted_0_bit = std::bitset<8>(shifted_0);
	std::cout << "shifted_0 = " << shifted_0 << " shifted_0_bit = " << shifted_0_bit << "\n";
	int shifted_1 = to_shift_a << shift_1;
	std::bitset<8> shifted_1_bit = std::bitset<8>(shifted_1);
	std::cout << "shifted_1 = " << shifted_1 << " shifted_1_bit = " << shifted_1_bit << "\n";
	int shifted_2 = to_shift_a << shift_2;
	std::bitset<8> shifted_2_bit = std::bitset<8>(shifted_2);
	std::cout << "shifted_2 = " << shifted_2 << " shifted_2_bit = " << shifted_2_bit << "\n";

	int merged_0_and_1 = shifted_0 | shifted_1;
	std::cout << "Merged_0_and_1 = " << merged_0_and_1 << " Bit = " << std::bitset<8>(merged_0_and_1) << "\n";

	int merged_0_and_2 = shifted_0 | shifted_2;
	std::cout << "Merged_0_and_2 = " << merged_0_and_2 << " Bit = " << std::bitset<8>(merged_0_and_2) << "\n";

	std::cout<< "jack\n";

	
	return 0;
}

int main_ret_app= user_main_in_app();

/*
* This is an extern method declared inside Fast Engine and called when the engine starts.
*/
FastEngine::Application* FastEngine::CreateApplication()
{
	std::cout << "Sandbox implementation of Create application." << "\n";
	return new Sandbox();
}

void FastEngine::Application::PostApplicationInit()
{
	PointersLearning* var = new PointersLearning();
	var->PrintPointers();
}