#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>



class Line {
    int shaderProgram;
    unsigned int lineVBO=4, instanceVBO=5, VAO=4; // TODO: Change this from hardcode
    unsigned int instanceVBO;
    std::vector<float> vertices;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    glm::mat4 transform;
    glm::vec3 lineColor;
public:
    Line();

    int setup(glm::vec3 start, glm::vec3 end, glm::mat4 transform[10]);

    int setTransform(glm::mat4 &transformIn);

    int setColor(glm::vec3 color);

    int draw();

    ~Line();
};