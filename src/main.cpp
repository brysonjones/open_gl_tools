#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "shader/shader.hpp"
#include "window/window.hpp"

void transform_2D(float x, float y, float theta, Shader &shader);

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
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    Window window;
    if (window.setup()){
        return 1;
    }

    if (window.load_opengl_ptrs()){
        return 2;
    }

    // set up shader object
    std::string vertexShaderPath = "/home/bkjones/Documents/bkjones_cmu/open_gl_tools/src/shader/trans_shader.vs";
    std::string fragmentShaderPath =  "/home/bkjones/Documents/bkjones_cmu/open_gl_tools/src/shader/trans_shader.fs";
    Shader shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str()); 

    // TODO: clean up code below -- these ints could be created in a less explicit manner
    unsigned int VAO, VBO, EBO;
    shader.add_VAO(VAO);
    shader.add_VBO(VBO);
    shader.add_EBO(EBO);
    shader.setup_shader_program(vertices, sizeof(vertices), indices, sizeof(indices));
    shader.use();

    // render loop
    // -----------
    while (!window.render_loop()){

        // create transformations
        float x = 0.5*sin(glfwGetTime());
        float y = 0.5*cos(4*glfwGetTime());
        float theta = 1*tan(glfwGetTime());
        
        transform_2D(x, y, theta, shader);

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void transform_2D(float x, float y, float theta, Shader &shader){
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
    transform = glm::rotate(transform, theta, glm::vec3(0.0f, 0.0f, 1.0f));

    // get matrix's uniform location and set matrix
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    
    // render the triangle
    glBindVertexArray(shader.VAO_vec[0]);  // TODO: make this not hardcoded
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


