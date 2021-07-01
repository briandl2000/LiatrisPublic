#pragma once

#include "Liatris/Core/Layer.h"

#include "Liatris/Events/ApplicationEvent.h"
#include "Liatris/Events/KeyEvent.h"
#include "Liatris/Events/MouseEvent.h"

namespace Liatris {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvenets = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvenets = true;
		float m_Time = 0.f;
	};

}