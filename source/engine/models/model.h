#ifndef MODEL_H
#define MODEL_H 

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "mesh.h"

#include <string>
#include <vector>

class ShaderProgram;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    Model(std::string path);

    void Draw(ShaderProgram& shader);
private:
    // model data
    vector<TextureStruct> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
};
#endif