#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "camera.h"
#include "GameObject.h"
#include "Model.h"
#include "shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

Camera * camera = new Camera();
float lastX, lastY;
bool enable2Rotate = true;
float lastFrame, deltaTime;
int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    Shader ourShader("D:/opengl-renderer/assets/shader/testshader.vs", "D:/opengl-renderer/assets/shader/testshader.fs");
    Model _model("D:/opengl-renderer/assets/model/nanosuit.obj");
    glm::vec4 light = glm::vec4(0.f,5.f,5.f,0.f);
    ourShader.use();
    ourShader.SetVec4("lightPos", light);
    
    //主循环
    while (!glfwWindowShouldClose(window))
    {
        float current = static_cast<float>(glfwGetTime());
        deltaTime = current - lastFrame;
        lastFrame = current;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindTexture(GL_TEXTURE_2D, texture);
        ourShader.use();
        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = camera->GetProjectionMatrix();
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
        ourShader.SetVec3("viewPos", camera->GetCameraPos());
        ourShader.setMat4("projection", projection);
        ourShader.SetMat3("normal", glm::inverse(glm::transpose(model)));
        _model.Draw(ourShader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->CameraMovementEvent(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->CameraMovementEvent(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->CameraMovementEvent(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->CameraMovementEvent(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camera->CameraMovementEvent(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) camera->CameraMovementEvent(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double x, double y)
{
    float xpos = static_cast<float>(x);
    float ypos = static_cast<float>(y);

    if(enable2Rotate)
    {
        lastX = xpos;
        lastY = ypos;
        enable2Rotate = false;
    }
    float _x = 0;
    float _y = 0;
    if(glfwGetMouseButton(window, 0))
    {
        _x = xpos - lastX;
        _y = ypos - lastY;
        lastX = xpos;
        lastY = ypos;
    }

    camera->CameraRotateEvent(_x, _y);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->CameraScaleEvent(static_cast<float>(yoffset));
}