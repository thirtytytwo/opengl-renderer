#ifndef MODEL_H_INCLUDE
#define MODEL_H_INCLUDE
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include "Mesh.h"

class Model
{
public:
    Model(char *path)
    {
        LoadModel(path);
    }
    void Draw(Shader shader)
    {
        for(int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shader);
        }
    }
private:
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;

    void LoadModel(string path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char* path, const string &directory, bool gamma = false);
};
#endif