#pragma once

#include <iostream>

#ifdef FE_PLATFORM_WINDOWS

FastEngine::Application* FastEngine::CreateApplication();

//This means that value should be defined in another translation unit
extern const char* valueDefinedInProject;

int vars = 52;

int before_before_main()
{
	printf("%d \n", vars);
	return 0;
}

int before_before_main_ret = before_before_main();

int before_main()
{
	printf("%d \n", vars);
	return 0;
}

int main_ret= before_main();


int main(int argc, char** argv)
{
	FastEngine::Log::init();
	FE_CORE_WARN("Start FAST ENGINE");
	FE_LOG("Start project {0}", valueDefinedInProject);


	printf("Fast Engine \n");
	printf("Start project %s", valueDefinedInProject);
	auto app = FastEngine::CreateApplication();
	app->PostApplicationInit();
	app->Run();
	delete app;

	return 0;
}

#endif