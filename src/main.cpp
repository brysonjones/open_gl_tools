
#include <iostream>
#include <cmath>

#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"

void transform_2D(float x, float y, float theta, Shader &shader, int obj_index);

float vertices[] = {
    // positions         // colors
     0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,   // bottom right
    -0.25f, -0.25f, 0.0f,  0.0f, 1.0f, 1.0f,   // bottom left
     0.25f,  0.25f, 0.0f,  0.0f, 1.0f, 1.0f,   // top right
    -0.25f,  0.25f, 0.0f,  1.0f, 1.0f, 0.0f,   // top left
};   
unsigned int indices[] = {
    0, 1, 2, // first triangle
    1, 2, 3  // second triangle
}; 

int main()
{
    // glfw window creation
    // --------------------
    Window window;
    if (window.setup()){
        return 1;
    }

    // set up shader object
    Shader shader; 

    // TODO: clean up code below -- these ints could be created in a less explicit manner
    shader.add_VAO();
    shader.add_VBO();
    shader.add_EBO();
    shader.setup_shader_program(vertices, sizeof(vertices), indices, sizeof(indices), 0);
    shader.add_VAO();
    shader.add_VBO();
    shader.add_EBO();
    shader.setup_shader_program(vertices, sizeof(vertices), indices, sizeof(indices), 1);

    shader.use();

    // render loop
    // -----------
    while (!window.render_loop()){

        // create transformations
        float x = 0.1*sin(glfwGetTime());
        float y = 0.1*cos(4*glfwGetTime());
        float theta = 0.1*tan(glfwGetTime());
        
        transform_2D(x, y, theta, shader, 0);

        // create transformations
        x = 0.5*sin(glfwGetTime());
        y = 0.5*cos(4*glfwGetTime());
        theta = 1*tan(glfwGetTime());
        
        transform_2D(x, y, theta, shader, 1);

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    while(shader.VAO_vec.size() > 0){
        shader.delete_vertex_array(0);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void transform_2D(float x, float y, float theta, Shader &shader, int obj_index){
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    transform = glm::rotate(transform, theta, glm::vec3(0.0f, 0.0f, 1.0f));

    // get matrix's uniform location and set matrix
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    
    // render the triangle
    glBindVertexArray(shader.VAO_vec[obj_index]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


