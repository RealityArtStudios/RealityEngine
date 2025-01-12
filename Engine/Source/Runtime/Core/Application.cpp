#include "Application.h"
#include "GameEngine.h"


Application::Application()
{
}

Application::~Application()
{
}

void Application::Run()
{
	GameEngine gameengine;
	gameengine.Run();
}
