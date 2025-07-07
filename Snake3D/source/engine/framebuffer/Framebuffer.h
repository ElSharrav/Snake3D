#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer
{
	unsigned int framebuffer;
	unsigned int texture;
	unsigned int renderbuffer;

public:
	~Framebuffer();
	// todo : creating renderbuffers as framebuffers attachement 
	// you cannot directly read from renderbuffer while you can from texture
	// which in most cases means that you should use textures for color buffers, and renderbuffers for depth and stencil buffers
	void generate(unsigned int textureX, unsigned int textureY);
	void activateFramebuffer();
	void activateTexture();
};

#endif