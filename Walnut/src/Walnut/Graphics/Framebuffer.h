#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>

struct FramebufferSpecification
{
	uint32_t Width = 0;
	uint32_t Height = 0;
};

class Framebuffer
{
public:
	//TODO: Platformize
	Framebuffer(const FramebufferSpecification& spec);
	~Framebuffer();

	void Construct();
	void Destruct();

	void Bind();
	void Unbind() const;

	void Rescale(float scale);
	void Resize(unsigned int w, unsigned int h);
	unsigned int GetRendererID() const;

private:
	void SetScale();

private:
	unsigned int m_RendererID;
	unsigned int m_TextureID;
	unsigned int m_DepthID;

	FramebufferSpecification m_Specification;
	float m_Scale = 1.0f;
};