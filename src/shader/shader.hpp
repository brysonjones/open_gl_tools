#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Shader
{
public:
    unsigned int ID;
    std::vector<unsigned int> VAO_vec; //
    std::vector<unsigned int> VBO_vec; //
    std::vector<unsigned int> EBO_vec; //
    
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader();

    void setup();

    void initShader(std::vector<float> vertices, std::vector<unsigned int> indices, int buffer_index);

    // add VAO to vector
    // ------------------------------------------------------------------------
    void add_VAO();
    // add VBO to vector
    // ------------------------------------------------------------------------
    void add_VBO();
    // add EBO to vector
    // ------------------------------------------------------------------------
    void add_EBO();
    // cleaning up resources
    // ------------------------------------------------------------------------
    void delete_vertex_array(int index);
    // activate the shader
    // ------------------------------------------------------------------------
    void use() const;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const;
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    const char* vShaderCode =
    #include "trans_shader.vs"
    ;
    const char* fShaderCode =
    #include "trans_shader.fs"
    ;

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type);
};