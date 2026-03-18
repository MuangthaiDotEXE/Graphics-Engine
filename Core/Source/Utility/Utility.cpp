#include "Utility.h"

std::string ReadFile(const char* path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        throw std::exception("Failed to open and read the file (Input/Output)");
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
        throw std::exception("Failed to open and read the file (Input/Output)");
    }

    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    file.close();

    return content;
}

Core::Utility::Utility()
{
}

Core::Utility::~Utility()
{
}
