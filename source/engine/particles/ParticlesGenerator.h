#ifndef PARTICLESGENERATOR_H
#define PARTICLESGENERATOR_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../shaders/shaderProgram.h"
#include "../macros.h"


#include <vector>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 color;
	float life;

	void update(float dT);
};

class ParticlesGenerator
{
	class Point
	{
		unsigned int VBO;
		unsigned int VAO;

		int instances;

		std::vector<float> vertices;	// position and color - per vertex

	public:
		Point( int instances );

		void draw(ShaderProgram& shader);
		void setColor(glm::vec4 color, int instance);
		void setPosition(glm::vec3 position, int instance);

		void addVertex(glm::vec3 position, glm::vec4 color);
		void clearVertices(int reserve);

		void updateBufferData();

		friend class ParticlesGenerator;
	};

	glm::vec3 origin;

	Point point;

	std::vector<Particle> particles;

public:
	ParticlesGenerator(glm::vec3 origin, int instances);

	void generate( int quantity , glm::ivec3 snakeDirection);
	void update( float dT );
	// delete particles
	void clear();
	// instanced drawing
	void draw( ShaderProgram& shader );

	SETTER(glm::vec3, origin);
};

#endif