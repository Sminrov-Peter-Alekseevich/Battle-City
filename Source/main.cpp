#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

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

int main(void){
    setlocale(LC_ALL,"ru");

    if (!glfwInit()) {
        cout << "ошибка: glfw не инициализировался" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
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

    glClearColor(0,0,0,1);

    glfwSetWindowSizeCallback(window,&glWindowResizeCallback);
    glfwSetKeyCallback(window,glKeyPressCallback);

    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}