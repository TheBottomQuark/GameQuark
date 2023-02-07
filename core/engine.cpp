#include "engine.hpp"

void window_resize(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

Window::Window(const char* title, int width, int height) { m_Title = title; m_Width = width;
    m_Height = height;
    if (!init())
        glfwTerminate();

    for (int i = 0; i < MAX_KEYS; i++)
        m_Keys[i] = false;

    for (int i = 0; i < MAX_BUTTONS; i++)
        m_MouseButtons[i] = false;
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::init()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowSizeCallback(m_Window, window_resize);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, cursor_position_callback);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    return true;
}

bool Window::isKeyPressed(unsigned int keycode) const
{
    if (keycode >= MAX_KEYS)
        return false;
    return m_Keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const
{

    if (button >= MAX_BUTTONS)
        return false;
    return m_MouseButtons[button];
}

void Window::getMousePosition(double &x, double &y) const
{
    x = mx;
    y = my;
}

bool Window::closed() const
{
    return glfwWindowShouldClose(m_Window) == 1;
}

void Window::update()
{
    glfwPollEvents();
    //glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
    glfwSwapBuffers(m_Window);
}

void Window::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->m_Keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->m_MouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->mx = xpos;
    win->my = ypos;
}

void librarytest()
{

    Window window("test", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    while (!window.closed())
    {
        double x, y;
        window.getMousePosition(x, y);
        std::cout << "x: " << x << " y: " << y << std::endl;

        window.clear();

        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();

        window.update();
    }

    std::cout << "Passed" << std::endl;
}