#ifndef CAMERA_H_INCLUDE
#define CAMERA_H_INCLUDE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float INTENSITY = 0.1f;
const float PITCH = 0.f;
const float YAW = -90.f;
const float SPEED = 1.5f;

class Camera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw, pitch;
    float fov, zNear, zFar, asp;

    void UpdateCameraVec()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward = glm::normalize(front);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(forward, worldUp));
        up    = glm::normalize(glm::cross(right, forward));
    }

public:
    Camera(glm::vec3 pos = glm::vec3(0.f,0.f,3.0f), glm::vec3 up = glm::vec3(0,1,0),float fov = 45.f, float zNear = 0.1f, float zFar = 100.f, float asp = 1.0f): yaw(YAW), pitch(PITCH)
    {
        this->worldUp = up;
        this->cameraPos = pos;
        this->fov = fov;
        this->zNear = zNear;
        this->zFar = zFar;
        this->asp = asp;

        UpdateCameraVec();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(cameraPos, cameraPos +forward, up);
    }

    glm::mat4 GetProjectionMatrix()
    {
        return glm::perspective(fov, asp, zNear,zFar);
    }

    glm::vec3 GetCameraPos()
    {
        return cameraPos;
    }

    //监听鼠标事件
    void CameraMovementEvent(CameraMovement dir, float deltaTime)
    {
        float speed = SPEED * deltaTime;
        if(dir == FORWARD) cameraPos += forward * speed;
        if(dir == BACKWARD) cameraPos -= forward * speed;
        if(dir == LEFT) cameraPos -= right * speed;
        if(dir == RIGHT) cameraPos += right * speed;
        if(dir == UP) cameraPos += up * speed;
        if(dir == DOWN) cameraPos -= up * speed;
    }
    void CameraRotateEvent(float x, float y)
    {
        x *= INTENSITY;
        y *= INTENSITY;

        yaw += x;
        pitch -= y;
        if(pitch > 89.f) pitch = 89.f;
        if(pitch < -89.f) pitch = -89.f;

        UpdateCameraVec();
    }
    void CameraScaleEvent(float offset)
    {
        offset *= INTENSITY;
        fov -= offset;
        if(fov < 1.f) fov = 1.f;
        if(fov > 90.f) fov = 90.f;
    }
};
#endif