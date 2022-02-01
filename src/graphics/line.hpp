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
    unsigned int VBO, VAO;
    std::vector<float> vertices;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    glm::mat4 transform;
    glm::vec3 lineColor;
public:
    Line();
    
    int setup(glm::vec3 start, glm::vec3 end);

    int setTransform(glm::mat4 transformIn);

    int setColor(glm::vec3 color);

    int draw();

    ~Line();
};