
#include <iostream>
#include <cmath>

#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"

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
    shader.setup();

    // TODO: clean up code below -- these ints could be created in a less explicit manner
    shader.setup_shader_program(vertices, sizeof(vertices), indices, sizeof(indices), 0);
    shader.setup_shader_program(vertices, sizeof(vertices), indices, sizeof(indices), 1);


    // render loop
    // -----------
    while (!window.render_loop()){

        // create transformations
        float x = 0.1*sin(glfwGetTime());
        float y = 0.1*cos(4*glfwGetTime());
        float theta = 0.1*tan(glfwGetTime());

        glBindVertexArray(shader.VAO_vec[0]);
        shader.use();
        graphics::transform_2D(x, y, theta, shader.ID);

        // create transformations
        x = 0.5*sin(glfwGetTime());
        y = 0.5*cos(4*glfwGetTime());
        theta = 1*tan(glfwGetTime());
        
        glBindVertexArray(shader.VAO_vec[1]);
        shader.use();
        graphics::transform_2D(x, y, theta, shader.ID);

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


