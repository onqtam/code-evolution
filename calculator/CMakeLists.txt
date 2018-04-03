cmake_minimum_required(VERSION 3.0.0)

project(calculator)

add_library(evaluator STATIC src/evaluator.cpp src/evaluator.h)

# enable warnings and latest compiler standard
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(evaluator PUBLIC -std=c++1y -Wall -Wextra)
else()
    target_compile_options(evaluator PUBLIC /std:c++latest /W4)
endif()

# add executable
add_executable(calculator src/main.cpp third_party/imgui/examples/opengl2_example/imgui_impl_glfw_gl2.cpp)
target_link_libraries(calculator PRIVATE evaluator)

# imgui
add_library(imgui STATIC third_party/imgui/imgui.cpp third_party/imgui/imgui_draw.cpp)
target_include_directories(imgui INTERFACE third_party/imgui)

# glfw
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/glfw)

# folders for the third party libs
set_target_properties(glfw PROPERTIES FOLDER "third_party")
set_target_properties(imgui PROPERTIES FOLDER "third_party")

# link the executable to the third parties
find_package(OpenGL REQUIRED)
target_link_libraries(calculator PRIVATE imgui glfw ${OPENGL_LIBRARIES})

# tests
enable_testing()
add_executable(tests tests/tests.cpp)
target_link_libraries(tests evaluator)
target_include_directories(tests PRIVATE src)
target_include_directories(tests PRIVATE third_party/doctest)
add_test(NAME tests COMMAND tests)
