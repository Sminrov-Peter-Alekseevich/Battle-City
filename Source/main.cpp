#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

using namespace std;

GLfloat point[] = {
        0.0f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f
};

GLfloat colors[] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
};


int windowSizeWidth = 640;
int windowSizeHeight = 480;

void glWindowResizeCallback(GLFWwindow *window,int width,int height){
    windowSizeWidth = width;
    windowSizeHeight = height;
    glViewport(0,0,width,height);
}
void glKeyPressCallback(GLFWwindow *window,int key,int scanMode,int action,int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window,GL_TRUE);
    }
}

int main(int argc,char** argv){
    ResourceManager resourceManager(argv[0]);
    setlocale(LC_ALL,"ru");

    if (!glfwInit()) {
        cout << "ошибка: glfw не инициализировался" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowSizeWidth, windowSizeHeight, "Battle City", nullptr, nullptr);
    if (!window){
        cout << "ошибка: не удалось создать окно" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        cout << "Ошибка: GLAD не инициализировался." << endl;
        return -1;
    }

    cout << "видеокарта " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL версия " << glGetString(GL_VERSION) << endl;

    {
        glClearColor(0, 1,1, 1);

        auto pDefaultShaderProgram = resourceManager.LoadShaders("def","Resources/Shaders/vertex.txt","Resources/Shaders/fragment.txt");
        if(!pDefaultShaderProgram){
            std::cerr << "Can't continue program script!" << std::endl;
            return -1;
        }

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glfwSetWindowSizeCallback(window, &glWindowResizeCallback);
        glfwSetKeyCallback(window, glKeyPressCallback);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}