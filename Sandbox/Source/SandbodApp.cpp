#include <FastEngine.h>

extern int my_external_var;

//This extern is not mandatory 
//because definition is happening here.
extern const int value;

class Sandbox : public FastEngine::Application
{
	public:
		Sandbox()
		{
		
		}

		~Sandbox()
		{
		
		}

};

int user_main_in_app()
{
	std::cout<< "jack\n";
	return 0;
}

int main_ret_app= user_main_in_app();

FastEngine::Application* FastEngine::CreateApplication()
{
	return new Sandbox();
}