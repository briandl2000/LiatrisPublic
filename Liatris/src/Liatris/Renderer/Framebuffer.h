#pragma once

namespace Liatris
{

	enum class FramebufferTextureFormat
	{
		None = 0,

		RGBA8,
		RED_INTEGER,
		
		DEPTH24STENCIL8,

		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}
		
		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}
		std::vector<FramebufferTextureSpecification> Attachments;
	};
	
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false; 
	};
	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		
		virtual void Resize(int width, int height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
		
		virtual uint32_t GetColorAttachmentRendererID(uint32_t id = 0) const = 0;
		
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	
	private:
	};
}