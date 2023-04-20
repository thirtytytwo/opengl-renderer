#ifndef GAMEOBJECT_H_INCLUDE
#define GAMEOBJECT_H_INCLUDE
#include <glm/glm.hpp>

#include "Model.h"

class GameObject
{
private:
    Model *model;
    Shader *shader;
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    GameObject(glm::vec3 pos = glm::vec3(0,0,0), glm::vec3 rot = glm::vec3(0,0,0), glm::vec3 sca = glm::vec3(1,1,1))
    {
        this->position = pos;
        this->rotation = rot;
        this->scale = sca;
    }
    void SetupShader(const char* vs, const char * fs)
    {
        shader = new Shader(vs, fs);
    }
    void SetupModel(char* path)
    {
        model = new Model(path);
    }
    void Render()
    {
        model->Draw(*shader);
    }
};
#endif