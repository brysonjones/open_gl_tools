
#include "line.hpp"

Line::Line() {

}

int Line::setup(glm::vec3 start, glm::vec3 end, glm::mat4 transform[10]){

    startPoint = start;
    endPoint = end;
    lineColor = glm::vec3(1,1,1);
    // transform = glm::mat4(1.0f);

    const char *vertexShaderSource = 
        #include "line_shader.vs"
        ;
    const char *fragmentShaderSource = 
        #include "line_shader.fs"
        ;

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors

    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    vertices = {
            start.x, start.y, start.z,
            end.x, end.y, end.z,

    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &lineVBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 


    // instance array setup
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 10, &transform[0], GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    // vertex attributes
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(2); 
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(vec4Size));
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * vec4Size));
    glEnableVertexAttribArray(4); 
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * vec4Size));

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);


}

int Line::setTransform(glm::mat4 &transformIn) {
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, &transform[0][0]);
    transform = transformIn;
    return 1;
}

int Line::setColor(glm::vec3 color) {
    glUseProgram(shaderProgram);
    glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);
    lineColor = color;
    return 1;
}

int Line::draw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_LINES, 0, 2, 10);
    return 1;
}

Line::~Line() {

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &lineVBO);
    glDeleteBuffers(1, &instanceVBO);
    glDeleteProgram(shaderProgram);
}
