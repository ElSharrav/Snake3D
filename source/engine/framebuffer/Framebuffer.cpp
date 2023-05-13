#include "Framebuffer.h"

#include <glad/glad.h> 
#include <stdexcept>

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &framebuffer);
}

void Framebuffer::generate(unsigned int textureX, unsigned int textureY)
{
	//create framebuffer
	glGenFramebuffers(1, &framebuffer);

	activateFramebuffer();

	//creating texture which will be attach to framebuffer
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureX, textureY, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//attaching texture to framebuffer
	//GL_COLOR_ATTACHMENT0
	//GL_DEPTH_ATTACHMENT0
	//GL_STENCIL_ATTACHMENT0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);	

	//creating renderbuffer
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, textureX, textureY);


	// attach renderbuffer to depth and stencil framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw std::runtime_error("Framebuffer is not complete: " + glCheckFramebufferStatus(GL_FRAMEBUFFER));
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::activateFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void Framebuffer::activateTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
