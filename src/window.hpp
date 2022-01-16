#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Window
{
public:

    // variables
    const unsigned int WINDOW_WIDTH = 1000;  // TODO: make modular
    const unsigned int WINDOW_HEIGHT = 800;  // TODO: make modular
    std::string title = "Robot Visualization";
    GLFWwindow* glfw_object;

    // functions
    Window();
    int setup();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput();
    int load_opengl_ptrs();
    int render_loop();

private:

};