#include "Shader.hpp"

// These three functions help us to load the shader programs from the GLSL files into our program  
std::string Shader::readSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compile(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const GLchar* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

void Shader::createProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::string vertexShaderSource = readShaderSource(vertexShaderPath);
    std::string fragmentShaderSource = readShaderSource(fragmentShaderPath);

    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cerr << "Failed to load shader sources" << std::endl;
        return 0;
    }

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program" << std::endl;
        return -1;
    }

    Shader::shaderId = shaderProgram;

    std::cout << "Shader program ID = " << Shader::shaderId << std::endl;
}




void Shader::useProgram()
{
    // Use shader program
    glUseProgram(shaderId);
}