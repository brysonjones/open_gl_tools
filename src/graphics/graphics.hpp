#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace graphics {
    enum SHADER_COLORS {
        RED = 1,
        GREEN = 2,
        BLUE = 3
    };

    void transform_2D(float x, float y, float theta, unsigned int transformLoc);
    std::vector<float> generateVertices(std::vector<int> centerPos, 
                                        std::vector<int> dims, 
                                        std::vector<int> map_size,
                                        int color);
}