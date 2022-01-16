#include "window.hpp"

Window::Window(){
}

int Window::setup(){
    glfw_object = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), NULL, NULL);
    if (glfw_object == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(glfw_object);
    glfwSetFramebufferSizeCallback(glfw_object, framebuffer_size_callback);

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Window::processInput()
{
    if(glfwGetKey(glfw_object, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw_object, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glad: load all OpenGL function pointers
// ---------------------------------------
int Window::load_opengl_ptrs(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }    
    return 0;
}

// rendor loop
// ---------------------------------------
int Window::render_loop(){
    if (glfwWindowShouldClose(glfw_object))
    {
        std::cout << "Window Closing" << std::endl;
        return 1;
    }    

    // input
    // -----
    processInput();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(glfw_object);
    glfwPollEvents();

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

