#include "line.h"

#include "glad/glad.h" 

#include <glm/gtc/matrix_transform.hpp>

Line::Line(glm::vec3 firstVertice, glm::vec3 secondVertice) : width(1)
{
	vertices[0] = firstVertice.x;
	vertices[1] = firstVertice.y;
	vertices[2] = firstVertice.z;
	vertices[6] = secondVertice.x;
	vertices[7] = secondVertice.y;
	vertices[8] = secondVertice.z;
	//vertices[16] = thirdVertice.x;
	//vertices[17] = thirdVertice.y;
	//vertices[18] = thirdVertice.z;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);

//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	model = glm::mat4(1.0f);
}

void Line::draw(ShaderProgram& shader)
{
	shader.use();
	shader.setMatrix4("model", model);
	glBindVertexArray(VAO);
	glLineWidth(width);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Line::setColor(glm::vec3 color)
{
	vertices[3] = color.x;
	vertices[4] = color.y;
	vertices[5] = color.z;
	vertices[9] = color.x;
	vertices[10] = color.y;
	vertices[11] = color.z;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);

}

void Line::setWidth(float width)
{
	this->width = width;
}

void Line::setPosition(glm::vec3 position)
{
	model = glm::translate(glm::mat4(1.0f), position);
}

//void Line::setTextureCoords(Vec2<float> firstTexCoords, Vec2<float> secondTexCoords, Vec2<float> thirdTexCoords)
//{
//	vertices[6] = firstTexCoords.x;
//	vertices[7] = firstTexCoords.y;
//	vertices[14] = secondTexCoords.x;
//	vertices[15] = secondTexCoords.y;
//	vertices[22] = thirdTexCoords.x;
//	vertices[23] = thirdTexCoords.y;
//
//	glBindVertexArray(VAO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindVertexArray(0);
//}

void Line::rotate(float degrees , glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(degrees), axis);
}