#version 330 core
out vec4 FragColor;

in vec3 inColor;
in vec3 inNormal;
in vec3 inWorldPos;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform float ambientStrength;

void main()
{
// ambient calculations
	vec3 ambient = ambientStrength * lightColor;

// diffuse calculations
	vec3 normalizedNormal = normalize(inNormal);
	vec3 normalizedLightDir = normalize(lightPos - inWorldPos);
	
	float diffuseComponent = max( dot( normalizedNormal , normalizedLightDir  ), 0.0 );
	vec3 diffuse = diffuseComponent * lightColor;

// final lightning color calculations
	vec3 resultingColor = (ambient + diffuse ) * inColor;

// final fragment color calculations
    FragColor = vec4(resultingColor ,1.0f);	// color output from vertex shader
}