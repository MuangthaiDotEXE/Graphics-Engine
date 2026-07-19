#include "Shader.h"

Core::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode, fragmentCode;

    if (std::filesystem::exists(vertexPath) && std::filesystem::exists(fragmentPath))
    {
        vertexCode = ReadFile(vertexPath);
        fragmentCode = ReadFile(fragmentPath);
    }
    else
    {
        vertexCode = vertexPath;
        fragmentCode = fragmentPath;
    }

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

Core::Shader::~Shader()
{
    Delete();
}

void Core::Shader::Activate()
{
    glUseProgram(programID);
}

void Core::Shader::Delete()
{
    glDeleteProgram(programID);
}

void Core::Shader::Error(GLuint shader, const std::string& type)
{
    GLint completed;
    char infoLog[1024];

    if (type == "Shader Program")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &completed);

        if (completed == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::print(stdout, "{} linking failed: {}\n", shader, infoLog);
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &completed);

        if (completed == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::print(stdout, "{} compilation failed: {}\n", shader, infoLog);
        }
    }
}
