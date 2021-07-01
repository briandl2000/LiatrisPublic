#include <Liatris.h>
#include <Liatris/Core/EntryPoint.h>

#include "EditorLayer.h"

class Sandbox : public Liatris::Application
{
public:
	Sandbox()
	{
		PushLayer(new Liatris::EditorLayer());
	}

	~Sandbox()
	{

	}
};

Liatris::Application* Liatris::CreateApplication()
{
	return new Sandbox();
}