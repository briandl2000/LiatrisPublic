#pragma once
#include "Liatris/Renderer/Framebuffer.h"

namespace Liatris
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer() override;

		void Invalidate();
		
		virtual void Resize(int width, int height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
		
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index) const override {LIA_CORE_ASSERT(index < m_ColorAttachments.size(), "Not a valid index!") return m_ColorAttachments[index]; };
		
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:

		uint32_t m_RenderID;
		
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecifications = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment;
	};
}