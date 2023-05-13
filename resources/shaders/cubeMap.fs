#version 330 core
out vec4 FragColor;

in vec3 textureDir;

uniform samplerCube cubemap;

void main()
{
    FragColor = texture( cubemap, textureDir );	// color output from vertex shader
  //  FragColor = vec4(0.0f,1.0f, 0.0f, 1.0f);	
}