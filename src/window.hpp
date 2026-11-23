#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <functional>

namespace gl {

class Window {
public:
    Window(std::uint16_t width, std::uint16_t height,
        const char* title, GLFWframebuffersizefun resize_fn);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool should_close() const noexcept;
    void swap_buffers() const noexcept;
    void poll_events(std::function<void(GLFWwindow*)> poll_fn);

private:
    GLFWwindow* _window;
};

}
