#include <algorithm>

#include "imgui.h"
#include "examples/opengl2_example/imgui_impl_glfw_gl2.h"
#include <GLFW/glfw3.h>

#include "evaluator.h"

template <typename T, size_t N>
char (&_ArraySizeHelper(T (&arr)[N]))[N];
#define COUNT_OF(x) (sizeof(_ArraySizeHelper(x)))

int main(int, char**) {
    // setup window
    glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "%d %s", error, description); });
    if(!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(800, 150, "Calculator", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // setup context
    ImGui::CreateContext();
    ImGui_ImplGlfwGL2_Init(window, true);

    // remove rounding of the console window and enlarge everything
    ImGuiStyle& style    = ImGui::GetStyle();
    style.WindowRounding = 0.f;
    style.ScaleAllSizes(2.5f);

    while(!glfwWindowShouldClose(window)) {
        // event poll
        glfwPollEvents();
        ImGui_ImplGlfwGL2_NewFrame();

        // imgui window should be always maximized
        int window_w, window_h;
        glfwGetWindowSize(window, &window_w, &window_h);
        ImGui::SetNextWindowSize({(float)window_w, (float)window_h}, ImGuiCond_Always);
        ImGui::SetNextWindowPos({0.f, 0.f}, ImGuiCond_Always);

        static char input[128]   = "";
        static char result[128]  = "";
        static char pointer[128] = "";
        static bool success      = true;
        if(ImGui::Begin("evaluator", nullptr,
                        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            // simple filtering of input text - only some characters are allowed...
            if(ImGui::InputText("##input", input, COUNT_OF(input), ImGuiInputTextFlags_CallbackCharFilter, [](auto* d) {
                   return (int)!(d->EventChar < 256 && strchr(" +-/*=1234567890.()logsincosx", (char)d->EventChar));
               }))
                pointer[0] = 0; // clear the pointer if the user has modified the input

            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), pointer);
            ImGui::Text("Result:");
            ImGui::SameLine();
            if(success)
                ImGui::Text(result);
            else
                ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), result);

            if(ImGui::Button("Eval")) {
                try {
                    success = false;
                    snprintf(result, COUNT_OF(result), "%f", evaluator::eval(input));
                    success = true;
                } catch(evaluator::ParseException& e) {
                    snprintf(result, COUNT_OF(result), "%s", e.what());
                    // fill adjust the pointer in its array
                    std::for_each(pointer, pointer + e.pos() + 1, [](char& in) { in = ' '; });
                    // make sure the C string is null terminated
                    pointer[std::min(e.pos() + 1, COUNT_OF(pointer) - 1)] = '^';
                    pointer[std::min(e.pos() + 2, COUNT_OF(pointer) - 1)] = 0;
                } catch(std::exception& e) {
                    snprintf(result, COUNT_OF(result), "%s", e.what());
                } catch(...) {
                    assert(false);
                }
            }
            ImGui::End();
        }

        // rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplGlfwGL2_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // cleanup
    ImGui_ImplGlfwGL2_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
