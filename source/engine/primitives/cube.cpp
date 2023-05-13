#include "cube.h"

#include "glad/glad.h" 

#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(float width, float length, float height)
{

	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = length;
	vertices[11] = width;
	vertices[12] = 0;
	vertices[13] = length;
	vertices[22] = width;
	vertices[23] = height;
	vertices[24] = length;

	vertices[33] = 0;
	vertices[34] = 0;
	vertices[35] = length;
	vertices[44] = width;
	vertices[45] = height;
	vertices[46] = length;
	vertices[55] = 0;
	vertices[56] = height;
	vertices[57] = length;

	vertices[66] = 0;
	vertices[67] = 0;
	vertices[68] = 0;
	vertices[77] = 0;
	vertices[78] = 0;
	vertices[79] = length;
	vertices[88] = 0;
	vertices[89] = height;
	vertices[90] = length;

	vertices[99] = 0;
	vertices[100] = 0;
	vertices[101] = 0;
	vertices[110] = 0;
	vertices[111] = height;
	vertices[112] = length;
	vertices[121] = 0;
	vertices[122] = height;
	vertices[123] = 0;
	
	vertices[132] = width;
	vertices[133] = 0;
	vertices[134] = 0;
	vertices[143] = 0;
	vertices[144] = 0;
	vertices[145] = 0;
	vertices[154] = 0;
	vertices[155] = height;
	vertices[156] = 0;

	vertices[165] = width;
	vertices[166] = 0;
	vertices[167] = 0;
	vertices[176] = 0;
	vertices[177] = height;
	vertices[178] = 0;
	vertices[187] = width;
	vertices[188] = height;
	vertices[189] = 0;

	vertices[198] = width;
	vertices[199] = 0;
	vertices[200] = length;
	vertices[209] = width;
	vertices[210] = 0;
	vertices[211] = 0;
	vertices[220] = width;
	vertices[221] = height;
	vertices[222] = 0;

	vertices[231] = width;
	vertices[232] = 0;
	vertices[233] = length;
	vertices[242] = width;
	vertices[243] = height;
	vertices[244] = 0;
	vertices[253] = width;
	vertices[254] = height;
	vertices[255] = length;

	vertices[264] = 0;
	vertices[265] = height;
	vertices[266] = length;
	vertices[275] = width;
	vertices[276] = height;
	vertices[277] = length;
	vertices[286] = width;
	vertices[287] = height;
	vertices[288] = 0;

	vertices[297] = 0;
	vertices[298] = height;
	vertices[299] = length;
	vertices[308] = width;
	vertices[309] = height;
	vertices[310] = 0;
	vertices[319] = 0;
	vertices[320] = height;
	vertices[321] = 0;

	vertices[330] = width;
	vertices[331] = 0;
	vertices[332] = 0;
	vertices[341] = 0;
	vertices[342] = 0;
	vertices[343] = 0;
	vertices[352] = 0;
	vertices[353] = 0;
	vertices[354] = length;

	vertices[363] = width;
	vertices[364] = 0;
	vertices[365] = 0;
	vertices[374] = 0;
	vertices[375] = 0;
	vertices[376] = length;
	vertices[385] = width;
	vertices[386] = 0;
	vertices[387] = length;

	// normal vectors
	for (int i = 8; i <= 66; i+=11)
	{
		vertices[i] = 0;
		vertices[i + 1] = 0;
		vertices[i + 2] = 1;
	}

	for (int i = 74; i <= 132; i += 11)
	{
		vertices[i] = -1;
		vertices[i + 1] = 0;
		vertices[i + 2] = 0;
	}

	for (int i = 140; i <= 198; i += 11)
	{
		vertices[i] = 0;
		vertices[i + 1] = 0;
		vertices[i + 2] = -1;
	}

	for (int i = 206; i <= 264; i += 11)
	{
		vertices[i] = 1;
		vertices[i + 1] = 0;
		vertices[i + 2] = 0;
	}

	for (int i = 272; i <= 330; i += 11)
	{
		vertices[i] = 0;
		vertices[i + 1] = 1;
		vertices[i + 2] = 0;
	}

	for (int i = 338; i <= 396; i += 11)
	{
		vertices[i] = 0;
		vertices[i + 1] = -1;
		vertices[i + 2] = 0;
	}

	// sending data to GPU

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);					/// vertex coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3*sizeof(float)));	/// vertex color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6*sizeof(float)));	/// vertex texture coordinates
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8*sizeof(float)));	/// vertex normal vector

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	model = glm::mat4(1.0f);
}

void Cube::draw(ShaderProgram& shader)
{
	shader.use();
	shader.setMatrix4("model", model);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::move(glm::vec3 move)
{
	model = glm::translate(model, move);
}

void Cube::setColor(glm::vec3 color)
{
	for (int i = 3; i < 396 ; i+=11)
	{
		vertices[i] = color.x;
		vertices[i+1] = color.y;
		vertices[i+2] = color.z;
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}



void Cube::setTextureCoords(Vec2<float> firstTexCoords, Vec2<float> secondTexCoords, Vec2<float> thirdTexCoords, Vec2<float> fourthTexCoords)
{
	for (int i = 6; i < 396; i+=66)
	{
		vertices[i] = firstTexCoords.x;
		vertices[i+1] = firstTexCoords.y;
		vertices[i+11] = secondTexCoords.x;
		vertices[i+12] = secondTexCoords.y;
		vertices[i+22] = thirdTexCoords.x;
		vertices[i+23] = thirdTexCoords.y;

		vertices[i+33] = firstTexCoords.x;
		vertices[i + 34] = firstTexCoords.y;
		vertices[i + 44] = thirdTexCoords.x;
		vertices[i + 45] = thirdTexCoords.y;
		vertices[i + 55] = fourthTexCoords.x;
		vertices[i + 56] = fourthTexCoords.y;
	}

	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Cube::setPosition(const glm::vec3& position)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model,  position );
}

/*

void Triangle::rotate(float degrees , glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(degrees), axis);
}

*/