#pragma once

#include <glad/glad.h>
#include <filesystem>

namespace gl {

class ShaderProgram {
public:
    ShaderProgram(std::filesystem::path vertex_path,
        std::filesystem::path fragment_path);
    ~ShaderProgram();
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void use() const noexcept;

private:
    ::GLuint _id;
};

}
