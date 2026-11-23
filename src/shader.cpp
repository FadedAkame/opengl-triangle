#include <glad/glad.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <print>
#include <string>

#include "shader.hpp"

namespace gl {

static std::string fetch_shader(std::filesystem::path shader_path) {
    if (!std::filesystem::exists(shader_path)) {
        std::println(stderr, "Shader file doesn't exist: '{}'", shader_path.c_str());
        std::exit(EXIT_FAILURE);
    }

    std::ifstream shader_stream(shader_path);
    if (!shader_stream) {
        std::println(stderr, "Shader file couldn't open: '{}'", shader_path.c_str());
        std::exit(EXIT_FAILURE);
    }

    std::string shader_glsl(std::istreambuf_iterator<char> { shader_stream }, { });
    return shader_glsl;
}
static ::GLuint compile_shader(const char* shader_glsl, ::GLenum type) {
    int success { };
    char info_log[512] { };

    ::GLuint shader { glCreateShader(type) };
    ::glShaderSource(shader, 1, &shader_glsl, nullptr);
    ::glCompileShader(shader);
    ::glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        ::glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::println(stderr, "Shader compilation failed: ", info_log);
        std::exit(EXIT_FAILURE);
    }

    return shader;
}

ShaderProgram::ShaderProgram(std::filesystem::path vertex_path,
    std::filesystem::path fragment_path) {
    const auto vertex_glsl { fetch_shader(vertex_path) };
    const auto fragment_glsl { fetch_shader(fragment_path) };

    const auto vertex_shader { compile_shader(vertex_glsl.c_str(),
        GL_VERTEX_SHADER) };
    const auto fragment_shader { compile_shader(fragment_glsl.c_str(),
        GL_FRAGMENT_SHADER) };

    int success { };
    char info_log[512] { };

    _id = glCreateProgram();
    ::glAttachShader(_id, vertex_shader);
    ::glAttachShader(_id, fragment_shader);
    ::glLinkProgram(_id);
    ::glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        ::glGetProgramInfoLog(_id, 512, nullptr, info_log);
        std::println(stderr, "Program linking failed", info_log);
        std::exit(EXIT_FAILURE);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_id);
}

void ShaderProgram::use() const noexcept {
    glUseProgram(_id);
}

}
