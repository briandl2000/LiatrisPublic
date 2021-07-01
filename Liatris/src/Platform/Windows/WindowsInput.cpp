#include "liapch.h"
#include "Liatris/Core/Input.h"

#include "Liatris/Core/Application.h"
#include "Platform/Windows/WindowsInput.h"
#include <GLFW/glfw3.h>

#include "Liatris/Renderer/Buffer.h"

namespace Liatris {

	namespace Internal
	{
		static double mouseX = 0.;
		static double mouseY = 0.;
		static double mouseDeltaX = 0.;
		static double mouseDeltaY = 0.;
	}

	void MousePositionCallback(double x, double y)
	{
		Internal::mouseDeltaX = x-Internal::mouseX;
		Internal::mouseDeltaY = y-Internal::mouseY;
		Internal::mouseX = x;
		Internal::mouseY = y;
	}

	void FlushInput()
	{
		Internal::mouseDeltaX = 0;
		Internal::mouseDeltaY = 0;
	}

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return (state == GLFW_PRESS);
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		return { Internal::mouseX, Internal::mouseY };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

	float Input::GetMouseDeltaX()
	{
		if (abs(Internal::mouseDeltaX) > 4.f)
			return Internal::mouseDeltaX;
		else
			return 0.f;
	}

	float Input::GetMouseDeltaY()
	{
		if (abs(Internal::mouseDeltaY) > 4.f)
			return Internal::mouseDeltaY;
		else
			return 0.f;
	}

}
