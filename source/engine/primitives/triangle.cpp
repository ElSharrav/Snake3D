#include "triangle.h"

#include "glad/glad.h" 

#include <glm/gtc/matrix_transform.hpp>

Triangle::Triangle(Vec3<float> firstVertice, Vec3<float> secondVertice, Vec3<float> thirdVertice)
{
	vertices[0] = firstVertice.x;
	vertices[1] = firstVertice.y;
	vertices[2] = firstVertice.z;
	vertices[8] = secondVertice.x;
	vertices[9] = secondVertice.y;
	vertices[10] = secondVertice.z;
	vertices[16] = thirdVertice.x;
	vertices[17] = thirdVertice.y;
	vertices[18] = thirdVertice.z;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	model = glm::mat4(1.0f);
}

void Triangle::draw(ShaderProgram& shader)
{
	shader.use();
	shader.setMatrix4("model", model);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void Triangle::setColor(Vec3<float> color)
{
	vertices[3] = color.x;
	vertices[4] = color.y;
	vertices[5] = color.z;
	vertices[11] = color.x;
	vertices[12] = color.y;
	vertices[13] = color.z;
	vertices[19] = color.x;
	vertices[20] = color.y;
	vertices[21] = color.z;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Triangle::setTextureCoords(Vec2<float> firstTexCoords, Vec2<float> secondTexCoords, Vec2<float> thirdTexCoords)
{
	vertices[6] = firstTexCoords.x;
	vertices[7] = firstTexCoords.y;
	vertices[14] = secondTexCoords.x;
	vertices[15] = secondTexCoords.y;
	vertices[22] = thirdTexCoords.x;
	vertices[23] = thirdTexCoords.y;

	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Triangle::rotate(float degrees , glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(degrees), axis);
}