#pragma once

#ifdef LIA_PLATFORM_WINDOWS

extern Liatris::Application* Liatris::CreateApplication();

int main(int argc, char** argv)
{
	Liatris::Log::Init();
	auto app = Liatris::CreateApplication();
	app->Run();
	delete app;
}
#endif // LIA_PLATFORM_WINDOWS
 