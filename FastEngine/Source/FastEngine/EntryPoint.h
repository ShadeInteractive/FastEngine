#pragma once

#include <iostream>

#ifdef FE_PLATFORM_WINDOWS

FastEngine::Application* FastEngine::CreateApplication();

//This means that value should be defined in another translation unit
extern const int value;

int vars = 52;

int user_main()
{
	printf("%d \n", vars);
	return 0;
}

int main_ret= user_main();


int main(int argc, char** argv)
{
	printf("Hazel Engine");
	printf("extern value %d", value);
	auto app = FastEngine::CreateApplication();
	//Sandbox* sandbox = new Sandbox();
	app->Run();
	delete app;

	return 0;
}

#endif