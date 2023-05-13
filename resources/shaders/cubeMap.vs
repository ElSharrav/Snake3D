#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;


out vec3 textureDir;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 toCenter = aPos - vec3(0.5);
	vec4 pos = projection * view * vec4(toCenter, 1.0);
    	gl_Position = pos;
//   	gl_Position = pos.xyww; // in this case skybox always have depth value at 1.0
//				// since, depth value is calculated as pos.w / pos.z : in this case it 
//				// translates to pos.w / pos.w = 1.0
   	textureDir = toCenter;
}