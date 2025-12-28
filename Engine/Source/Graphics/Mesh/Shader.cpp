#include "Shader.h"

template<string T>
std::string Engine::Shader::ReadFile(const T& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        throw std::exception("Failed to open shader file");
    }

    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    file.close();

    return content;
}

Engine::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = ReadFile(vertexPath);
    std::string fragmentCode = ReadFile(fragmentPath);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    Error(vertexShader, "Vertex Shader");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    Error(fragmentShader, "Fragment Shader");

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    Error(programID, "Shader Program");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Engine::Shader::~Shader()
{
    Delete();
}

void Engine::Shader::Activate()
{
    glUseProgram(programID);
}

void Engine::Shader::Delete()
{
    glDeleteProgram(programID);
}

void Engine::Shader::Error(GLuint shader, const std::string& type)
{
    GLint compiled;
    char infoLog[1024];

    if (type == "Shader Program")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &compiled);

        if (compiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::print("{} linking failed: {}\n", shader, infoLog);
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (compiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::print("{} compilation failed: {}\n", shader, infoLog);
        }
    }
}
