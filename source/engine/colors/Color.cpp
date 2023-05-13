#include "Color.h"

Color::Color(float R, float G, float B, float A) : R(R), G(G), B(B), A(A)
{

}

 glm::vec4 Color::Red = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
 glm::vec4 Color::Black = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
 glm::vec4 Color::White = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);