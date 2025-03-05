#include "core/window.hpp"


// fullscreen constructor 
Window::Window(const std::string& title): width(100), height(100), title(title), glfwWindow(nullptr, glfwDestroyWindow) {
    if (instance) {
        throw std::runtime_error("Only one Window instance is allowed!");
    }
    instance = this;
    
    initializeGLFW();
    createWindow(true);
    loadOpenGL();
}
// Constructor
Window::Window(int width, int height, const std::string& title, bool fullscreen)
    : width(width), height(height), title(title), 
      glfwWindow(nullptr, glfwDestroyWindow) {
    
    if (instance) {
        throw std::runtime_error("Only one Window instance is allowed!");
    }
    instance = this;
    
    initializeGLFW();
    createWindow(fullscreen);
    loadOpenGL();
}

// Destructor
Window::~Window() {
    glfwTerminate();
}

// Initialize GLFW
void Window::initializeGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }
}

// Create GLFW Window
void Window::createWindow(bool fullscreen) {
    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    const GLFWvidmode* mode = fullscreen ? glfwGetVideoMode(monitor) : nullptr;

    if (fullscreen) {
        width = mode->width;
        height = mode->height;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindow.reset(glfwCreateWindow(width, height, title.c_str(), monitor, nullptr));
    if (!glfwWindow) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(glfwWindow.get());
    glfwSetKeyCallback(glfwWindow.get(), keyCallback);
}

// Load OpenGL 4.1 using GLAD
void Window::loadOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD!");
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

// Handle Key Input
void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (instance && instance->keyCallbackFunction) {
        instance->keyCallbackFunction(key, scancode, action, mods);
    }
    
    // Exit on Ctrl + Alt + F4
    if (action == GLFW_PRESS && key == GLFW_KEY_F4 && 
        (mods & GLFW_MOD_CONTROL) && (mods & GLFW_MOD_ALT)) {
        glfwSetWindowShouldClose(window, true);
    }
}

// Check if the window should close
bool Window::shouldClose() const {
    return glfwWindowShouldClose(glfwWindow.get());
}

// Poll window events
void Window::pollEvents() const {
    // if esc is pressed, close the window 
    glfwPollEvents();

    if (glfwGetKey(glfwWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(glfwWindow.get(), true);
    }
}

// Swap buffers
void Window::swapBuffers() const {
    glfwSwapBuffers(glfwWindow.get());
}

// Enable/Disable VSync
void Window::setVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

// Set custom key callback
void Window::setKeyCallback(KeyCallback callback) {
    keyCallbackFunction = std::move(callback);
}

void Window::run() const {
    while (!shouldClose()) {
        pollEvents();
        swapBuffers();
    }
}
