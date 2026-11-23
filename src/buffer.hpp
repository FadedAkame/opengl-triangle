#pragma once

#include <glad/glad.h>
#include <cstddef>

namespace gl {

class Buffer {
public:
    Buffer() {
        glGenBuffers(1, &_id);
    }
    ~Buffer() {
        glDeleteBuffers(1, &_id);
    }
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    inline ::GLuint id() const noexcept {
        return _id;
    }

private:
    ::GLuint _id;
};

class VAO {
public:
    VAO() {
        glGenVertexArrays(1, &_id);
    }
    ~VAO() {
        glDeleteVertexArrays(1, &_id);
    }
    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;

    inline ::GLuint id() const noexcept {
        return _id;
    }
    inline void attributes(::GLuint index, ::GLint size, ::GLenum type,
        ::GLboolean norm, ::GLsizei stride, std::size_t offset) const noexcept {
        glVertexAttribPointer(index, size, type,
            norm, stride, reinterpret_cast<void*>(offset));
        glEnableVertexAttribArray(index);
    }

private:
    ::GLuint _id;
};

}
