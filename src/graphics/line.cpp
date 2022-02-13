
#include "line.hpp"

Line::Line() {

}

int Line::setup(){

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
    
    glGenVertexArrays(1, &VAO);

    return 0;

}

int Line::updatePos(std::vector<float> &posIn) {
    glGenBuffers(1, &lineVBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    if (posIn.size() % 3 == 0){
        numSegments = (posIn.size() / 3)  - 1;
    } else {
        return 1;  // incorrect vector size provided; not divisible by 3
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*posIn.size(), posIn.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0); 

    return 0;
}

int Line::updateTransform(std::vector<glm::mat4> &transformIn) {
    // instance array setup
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    numTransforms = transformIn.size();
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * numTransforms, transformIn.data(), GL_STATIC_DRAW);

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

    return 0;
}

int Line::setColor(glm::vec3 color) {
    glUseProgram(shaderProgram);
    glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);
    lineColor = color;

    return 0;
}

int Line::draw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_LINE_STRIP, 0, numSegments, numTransforms);

    return 0;
}

Line::~Line() {

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &lineVBO);
    glDeleteBuffers(1, &instanceVBO);
    glDeleteProgram(shaderProgram);
}
