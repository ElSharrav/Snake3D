#version 330 core
out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D textureSampler;
uniform int postProcessEffect;

// offset for kernel effects
const float offset = 0.1 / 300.0;  

void main()
{
	// offsetts for kernel post processing
  vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );
// numbers to multiply with in kernel postprocessing
    float kernel[9] = float[](
// sharpen kernel
 //       -1, -1, -1,
 //       -1,  9, -1,
 //      -1, -1, -1
// blur kernel
 //       1.0/16, 2.0/16, 1.0/16,
//        2.0/16,  3.0/16, 2.0/16,
 //      1.0/16, 2.0/16, 1.0/16
// edge detection kernel
        1, 1, 1,
        1,  -8, 1,
       1, 1, 1
    );

	vec4 texturePoint = texture( textureSampler, textureCoords);

	switch( postProcessEffect )
	{
	case 0:	// no additional effect
	{
		FragColor =  texturePoint;
		break;
	}
	case 1: // color inversion
	{
		FragColor = vec4(vec4(1.0) - texturePoint);
		break;
	}
	case 2: // grayscale
	{
		float average = 0.2126 * texturePoint .r + 0.7152 * texturePoint .g + 0.0722 * texturePoint .b;
   		FragColor = vec4(average, average, average, 1.0);
		break;
	}
	case 3: // kernel effect
	{
		vec3 sampleTex[9];
   		 for(int i = 0; i < 9; i++)
   		 {
      		  sampleTex[i] = vec3(texture(textureSampler, textureCoords.st + offsets[i]));
   		 }
   		 vec3 col = vec3(0.0);
    		for(int i = 0; i < 9; i++)
   		     col += sampleTex[i] * kernel[i];
    
    		FragColor = vec4(col, 1.0);
		break;
	}
	}

}