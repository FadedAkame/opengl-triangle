cmake_minimum_required(VERSION 3.20)
project(triangle LANGUAGES C CXX)

# Main settings
option(ENABLE_SANITIZERS "Enable ASan + UBSan" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw"
)

add_library(glad STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c"
)
target_include_directories(glad SYSTEM PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include"
)

# Main executable
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wformat=2
    -Wnull-dereference
    -Wdouble-promotion
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
)

# Optional ASan + UBSan
if(ENABLE_SANITIZERS)
    set(SANITIZER_FLAGS
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )

    target_compile_options(${PROJECT_NAME} PRIVATE ${SANITIZER_FLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${SANITIZER_FLAGS})
endif()
