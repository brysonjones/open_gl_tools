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
    std::vector<float> vertices;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    std::vector<glm::mat4> transform;
    glm::vec3 lineColor;

    public:
        Line();

        int setup(glm::vec3 start, glm::vec3 end, std::vector<glm::mat4> &transformIn);
        int updatePos(std::vector<float> &posIn);
        int updateTransform(std::vector<glm::mat4> &transformIn);

        // int setTransform(glm::mat4 &transformIn);

        int setColor(glm::vec3 color);

        int draw();

        ~Line();

    private:
        int numSegments; // number of transforms in vector

};