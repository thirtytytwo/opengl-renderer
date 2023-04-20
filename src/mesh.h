#ifndef MESH_H_INCLUDE
#define MESH_H_INCLUDE
#include<string>
#include<vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

using namespace std;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 tangent;
    glm::vec3 bitTangent;
};

struct Texture
{
    unsigned int ID;
    string type;
    string path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> texture;
    unsigned int vArray;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> texture)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->texture = texture;

        SetupMesh();
    }

    void Draw(Shader &shader)
    {
        unsigned int diffuse = 1;
        unsigned int specular = 1;
        unsigned int normal = 1;
        unsigned int height = 1;
        for(unsigned int i = 0; i < texture.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            string number;
            string name = texture[i].type;
            if(name=="texture_diffuse") number = to_string(diffuse++);
            else if(name=="texture_specular") number = to_string(specular++);
            else if(name=="texture_normal") number = to_string(normal++);
            else if(name=="texture_height") number = to_string(height++);

            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, texture[i].ID);
        }

        glBindVertexArray(vArray);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

        glActiveTexture(GL_TEXTURE0);
    }
private:
    unsigned int vBuffer, iBuffer;
    void SetupMesh()
    {
        glGenVertexArrays(1, &vArray);
        glGenBuffers(1, &vBuffer);
        glGenBuffers(1, &iBuffer);

        glBindVertexArray(vArray);
        glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitTangent));

        glBindVertexArray(0);
    }
};
#endif