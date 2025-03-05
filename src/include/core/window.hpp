
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>

class Window {
public:
    using KeyCallback = std::function<void(int, int, int, int)>;

    Window(const std::string& title);
    Window(int width = 100, int height = 100, const std::string& title = "Sea", bool fullscreen = true);
    ~Window();

    void setKeyCallback(KeyCallback callback);
    
    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    
    void run() const;

    void setVSync(bool enabled);

private:
    void initializeGLFW();
    void createWindow(bool fullscreen);
    void loadOpenGL();

    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    static inline Window* instance = nullptr; // Needed for static callbacks

    int width, height;
    std::string title;
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> glfwWindow;
    KeyCallback keyCallbackFunction;
};

#endif // WINDOW_H
