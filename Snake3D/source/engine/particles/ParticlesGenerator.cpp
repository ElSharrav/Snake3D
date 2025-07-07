#include "ParticlesGenerator.h"

#include <iostream>

#include "../Random/Random.h"

#define NUMBER_OF_ATTRIBUTES 2
#define FLOATS_PER_VERTEX 7
#define COLOR_OFFSET_IN_VERTEX 3
#define POSITION_OFFSET_IN_VERTEX 0

ParticlesGenerator::Point::Point(int instances) : vertices( instances * FLOATS_PER_VERTEX), instances(instances)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), NULL, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)POSITION_OFFSET_IN_VERTEX);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)(COLOR_OFFSET_IN_VERTEX * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribDivisor(0, 1);
	glVertexAttribDivisor(1, 1);

	glBindVertexArray(0);
}

void ParticlesGenerator::Point::draw(ShaderProgram& shader)
{
	shader.use();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_POINTS, 0, 1, instances );
	glBindVertexArray(0);
}
void ParticlesGenerator::Point::setColor(glm::vec4 color, int instance)
{
	vertices.at(instance * FLOATS_PER_VERTEX + COLOR_OFFSET_IN_VERTEX) = color.r;
	vertices.at(instance * FLOATS_PER_VERTEX + COLOR_OFFSET_IN_VERTEX + 1) = color.g;
	vertices.at(instance * FLOATS_PER_VERTEX + COLOR_OFFSET_IN_VERTEX + 2) = color.b;
	vertices.at(instance * FLOATS_PER_VERTEX + COLOR_OFFSET_IN_VERTEX + 3) = color.a;
}
void ParticlesGenerator::Point::setPosition(glm::vec3 position, int instance)
{
	vertices.at(instance * FLOATS_PER_VERTEX) = position.x;
	vertices.at(instance * FLOATS_PER_VERTEX + 1) = position.y;
	vertices.at(instance * FLOATS_PER_VERTEX + 2) = position.z;
}

void ParticlesGenerator::Point::addVertex(glm::vec3 position, glm::vec4 color)
{
	vertices.push_back(position.x);
	vertices.push_back(position.y);
	vertices.push_back(position.z);
	vertices.push_back(color.r);
	vertices.push_back(color.g);
	vertices.push_back(color.b);
	vertices.push_back(color.a);
}

void ParticlesGenerator::Point::updateBufferData()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);
}

void ParticlesGenerator::Point::clearVertices(int reserve)
{
	vertices.clear();
	vertices.reserve(reserve * FLOATS_PER_VERTEX);
}

ParticlesGenerator::ParticlesGenerator(glm::vec3 origin, int instances) : origin(origin), point( instances )
{

}

void Particle::update(float dT)
{
	life -= dT;
	position += (dT * velocity);
	color.a -= (Random::randFloat( 0.0 , 0.8 ) * dT);
}

void ParticlesGenerator::clear()
{
	point.clearVertices(point.instances);
	particles.clear();
}

void ParticlesGenerator::generate(int quantity, glm::ivec3 snakeDirection)
{
	float magnitude = 3;

	particles.clear();
	particles.reserve(quantity);
	point.clearVertices(quantity);

	float floorRestricted = -0.05, ceilRestricted = 0.05;	// random particles velocity in the direction of moving

	float xFloorValue = -1.0, xCeilValue = 1.0;
	float yFloorValue = -1.0, yCeilValue = 1.0;
	float zFloorValue = -1.0, zCeilValue = 1.0;

	if (snakeDirection.x != 0)
	{
		xFloorValue = floorRestricted;
		xCeilValue = ceilRestricted;
	}
	else if (snakeDirection.y != 0)
	{
		yFloorValue = floorRestricted;
		yCeilValue = ceilRestricted;
	}
	else if (snakeDirection.z != 0)
	{
		zFloorValue = floorRestricted;
		zCeilValue = ceilRestricted;
	}
	

	for (size_t i = 0; i < quantity; ++i)
	{
		Particle particle;

		// setting particle data in CPU
		particle.life = 5.0;

		particle.color = glm::vec4(0.0, 1.0, 0.0, 1.0);

		particle.velocity = (magnitude * glm::vec3( Random::randFloat(xFloorValue, xCeilValue), Random::randFloat(yFloorValue, yCeilValue), Random::randFloat(zFloorValue, zCeilValue)));
		particle.position = origin;

		// setting particles data to send to GPU
		point.addVertex(particle.position, particle.color);

		particles.push_back(particle);
	}
	point.updateBufferData();
}
void ParticlesGenerator::update(float dT)
{
	for (size_t i = 0; i < particles.size(); ++i)
	{
		particles.at(i).update(dT);
		point.setColor(particles.at(i).color , i);
		point.setPosition(particles.at(i).position, i);
	}
	point.updateBufferData();
}
void ParticlesGenerator::draw(ShaderProgram& shader)
{
	shader.use();
	point.draw(shader);
}