#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <print>

#include "window.hpp"

namespace gl {

Window::Window(std::uint16_t width, std::uint16_t height,
    const char* title, GLFWframebuffersizefun resize_fn) {
    if (!glfwInit()) {
        std::println(stderr, "Failed to initialize GLFW");
        std::exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (_window == nullptr) {
        std::println(stderr, "Failed to create window");
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::println(stderr, "Failed to initialize GLAD");
        std::exit(EXIT_FAILURE);
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(_window, resize_fn);
}
Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool Window::should_close() const noexcept {
    return glfwWindowShouldClose(_window);
}
void Window::swap_buffers() const noexcept {
    glfwSwapBuffers(_window);
}
void Window::poll_events(std::function<void(GLFWwindow*)> poll_fn) {
    glfwPollEvents();
    poll_fn(_window);
}

}
