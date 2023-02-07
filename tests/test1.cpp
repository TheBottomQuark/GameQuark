#include "engine.hpp"

int main(int argc, char *argv[])
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

    return 0;
}
