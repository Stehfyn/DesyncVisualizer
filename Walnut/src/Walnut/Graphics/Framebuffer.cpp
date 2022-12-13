#include "Framebuffer.h"
Framebuffer::Framebuffer(const FramebufferSpecification& spec)
{
	m_Specification = spec;
}
Framebuffer::~Framebuffer()
{

}
void Framebuffer::Construct()
{
	glGenFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthID);
	glBindTexture(GL_TEXTURE_2D, m_DepthID);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthID, 0);

	GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(m_TextureID, buffers);
	Unbind();
}
void Framebuffer::Destruct()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteTextures(1, &m_TextureID);
	glDeleteTextures(1, &m_DepthID);
}
void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	SetScale();
}
void Framebuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Framebuffer::Rescale(float scale)
{
	if (scale >= 0.0f)
	{
		m_Scale = scale;
	}
}
void Framebuffer::Resize(unsigned int w, unsigned int h)
{
	m_Specification.Width = w;
	m_Specification.Height = h;
}
unsigned int Framebuffer::GetRendererID() const
{
	return m_RendererID;
}
void Framebuffer::SetScale()
{
	float x = (m_Specification.Width / 2.0f) - ((m_Specification.Width * m_Scale) / 2.0f);
	float y = (m_Specification.Height / 2.0f) - ((m_Specification.Height * m_Scale) / 2.0f);
	glViewport(x, y, m_Specification.Width * m_Scale, m_Specification.Height * m_Scale);
}