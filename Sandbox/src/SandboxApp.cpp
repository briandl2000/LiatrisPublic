#include <Liatris.h>
#include <Liatris/Core/EntryPoint.h>

class ExampleLayer : public Liatris::Layer
{
public:
	ExampleLayer()
	{
	}

	virtual void OnAttach() override
	{
		
	}

	void OnUpdate(Liatris::Timestep ts) override
	{
	}
	
	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Liatris::Event& event) override
	{
	}

private:
};

class Sandbox : public Liatris::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Liatris::Application* Liatris::CreateApplication()
{
	return new Sandbox();
}