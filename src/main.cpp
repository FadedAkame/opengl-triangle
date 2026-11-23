#include <array>
#include <filesystem>

#include "buffer.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "window.hpp"

using namespace gl;

void resize_callback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const std::filesystem::path vertex_shader_path { "shaders/vert.glsl" };
const std::filesystem::path fragment_shader_path { "shaders/frag.glsl" };

/* See 'vertex.hpp' for more info */
constexpr std::array<Vertex<float>, 3> vertices = { {
    { .position { -0.5f, -0.5f, 0.0f }, .color { 1.0f, 0.0f, 0.0f } },
    { .position { 0.5f, -0.5f, 0.0f }, .color { 0.0f, 1.0f, 0.0f } },
    { .position { 0.0f, 0.5f, 0.0f }, .color { 0.0f, 0.0f, 1.0f } },
} };

int main() {
    /* See 'window.hpp/cpp' for more info */
    Window window(800, 600, "triangle", resize_callback);
    /* See 'shader.hpp/cpp' for more info */
    ShaderProgram program(vertex_shader_path, fragment_shader_path);
    program.use();

    /* See 'buffer.hpp' for more info */
    VAO vao;
    Buffer vbo;
    glBindVertexArray(vao.id());

    glBindBuffer(GL_ARRAY_BUFFER, vbo.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    vao.attributes(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    vao.attributes(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));

    while (!window.should_close()) {
        window.poll_events(process_input);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap_buffers();
    }
}
