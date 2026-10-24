#include "Utility.h"

std::string ReadFile(const char* path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        Core::Log::Error("Input/Output", std::format("Failed to open/read the file: '{}'. No such file or directory", path));
    }

    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    file.close();

    return content;
}

std::string ReadFile(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        Core::Log::Error("Input/Output", std::format("Failed to open/read the file: '{}'. No such file or directory", path));
    }

    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    file.close();

    return content;
}
