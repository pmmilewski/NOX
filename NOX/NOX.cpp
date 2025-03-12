#include "source/VulkanRenderer.h"
#include "source/WwiseIntegration.h"
#include "source/FPSCamera.h"
#include "source/RoomAcoustics.h"

static VulkanRenderer g_Renderer;
static WwiseIntegration g_SoundEngine;

auto camera = FPSCamera(0.5f, 0.5f, 2.0f);
static auto cameraView = camera.GetCameraMatrix();

float deltaTime{};
std::chrono::time_point<std::chrono::steady_clock> lastFrame {};

bool firstMouse = true;
float lastX = 400, lastY = 300;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.RotateCamera(xoffset, yoffset, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ZoomCamera(yoffset, deltaTime);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    glm::vec3 cameraMovement(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraMovement.x += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraMovement.x -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraMovement.y -= 1.0f;;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraMovement.y += 1.0f;

    camera.MoveCamera(cameraMovement, deltaTime);
}

// Main code
int main(int, char**)
{
    RoomAcoustics roomAcoustics;
    roomAcoustics.PopulateScene();
    g_Renderer.SetCurrentScene(roomAcoustics.GetSceneObjects());
    
    g_Renderer.initWindow();
    g_Renderer.initVulkan();

    glfwSetCursorPosCallback(g_Renderer.getWindow(), mouse_callback);
    glfwSetScrollCallback(g_Renderer.getWindow(), scroll_callback);
    glfwSetInputMode(g_Renderer.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    g_Renderer.setupImGuiBackends();
    
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Initializing WWise
    g_SoundEngine.InitWwise();
    g_SoundEngine.InitWwiseComm();

    // Main loop
    while (!glfwWindowShouldClose(g_Renderer.getWindow()))
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - lastFrame).count();
        lastFrame = currentTime;
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        processInput(g_Renderer.getWindow());

        // Start the Dear ImGui frame
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

#if 0
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                g_SoundEngine.PlayEvent();
                counter++;
            }

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
#endif
        ImGui::Render();
        g_Renderer.SetViewMatrix(camera.GetCameraMatrix());
        g_Renderer.drawFrame();
        g_SoundEngine.RenderAudio();
    }

    // Terminating Wwise
    g_SoundEngine.TermWwiseComm();
    g_SoundEngine.TermWwise();
    
    // Cleanup
    g_Renderer.deviceWaitIdle();
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    g_Renderer.cleanup();
    
    return 0;
}
