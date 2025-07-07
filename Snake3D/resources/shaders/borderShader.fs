#version 330 core
out vec4 FragColor;

in vec3 color;

void main()
{
    vec3 borderColor = vec3( 0.44, 0.0, 0.0 );
    FragColor = vec4( borderColor , 1.0f);	// color output from vertex shader
}