
#include "shader.hpp"

// ------------ Class Constructor Definition ------------

Shader::Shader(){
    // compile shaders
    unsigned int vertex, fragment;
    std::cout << "test\n";
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "test\n";
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    std::cout << "test\n";
    glCompileShader(vertex);
    std::cout << "test\n";
    checkCompileErrors(vertex, "VERTEX");
    std::cout << "test\n";
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    std::cout << "test\n";
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    std::cout << "test\n";
    glCompileShader(fragment);
    std::cout << "test\n";
    checkCompileErrors(fragment, "FRAGMENT");
    std::cout << "test\n";
    // shader Program
    ID = glCreateProgram();
    std::cout << "test\n";
    glAttachShader(ID, vertex);
    std::cout << "test\n";
    glAttachShader(ID, fragment);
    std::cout << "test\n";
    glLinkProgram(ID);
    std::cout << "test\n";
    checkCompileErrors(ID, "PROGRAM");
    std::cout << "test\n";
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    std::cout << "test\n";
    glDeleteShader(fragment);
    std::cout << "test\n";

}

// ------------ Public Functions ------------

void Shader::setup_shader_program(float vertices[], int v_size, unsigned int indices[], int i_size, int buffer_index){
    // create buffers
    add_VAO();
    add_VBO();
    add_EBO();
    // TODO: Add error handling and error codes
    // create VAO
    glGenVertexArrays(1, &VAO_vec[buffer_index]);

    // create OpenGL Buffer for storing vertices and elements
    glGenBuffers(1, &VBO_vec[buffer_index]);

    // create OpenGL Buffer for storing indices of points
    glGenBuffers(1, &EBO_vec[buffer_index]);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_vec[buffer_index]);

    // bind buffer to gl array type
    glBindBuffer(GL_ARRAY_BUFFER, VBO_vec[buffer_index]);
    // copy vertex data into buffer
    glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);

    // this element is needed for plotting more than one triangle
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_vec[buffer_index]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);

    // tell OpenGL how to interpret the vertex data in memory
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

// add VAO to vector
// ------------------------------------------------------------------------
void Shader::add_VAO(){ 
    unsigned int VAO;
    VAO_vec.push_back(VAO);
}
// add VBO to vector
// ------------------------------------------------------------------------
void Shader::add_VBO(){ 
    unsigned int VBO;
    VBO_vec.push_back(VBO);
}
// add EBO to vector
// ------------------------------------------------------------------------
void Shader::add_EBO(){ 
    unsigned int EBO;
    EBO_vec.push_back(EBO);
}
// cleaning up resources
// ------------------------------------------------------------------------
void Shader::delete_vertex_array(int index){ 
    glDeleteVertexArrays(1, &VAO_vec[index]);
    glDeleteBuffers(1, &VBO_vec[index]);
    glDeleteBuffers(1, &EBO_vec[index]);
    VAO_vec.erase(VAO_vec.begin() + index);
    VBO_vec.erase(VBO_vec.begin() + index);
    EBO_vec.erase(EBO_vec.begin() + index);

}

// activate the shader
// ------------------------------------------------------------------------
void Shader::use() const
{ 
    glUseProgram(ID); 
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------ Private Functions ------------

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}