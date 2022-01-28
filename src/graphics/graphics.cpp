#include "graphics.hpp"

namespace graphics {
    void transform_2D(float x, float y, float theta, unsigned int ID){
        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
        transform = glm::rotate(transform, theta, glm::vec3(0.0f, 0.0f, 1.0f));

        // get matrix's uniform location and set matrix
        unsigned int transformLoc = glGetUniformLocation(ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        
        // render the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}