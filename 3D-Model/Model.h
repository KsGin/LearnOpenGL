/*
 * File   : Model
 * Author : KsGin 
 * Date   : 2018/3/4
 */

#ifndef INC_3D_MODEL_MODEL_H
#define INC_3D_MODEL_MODEL_H


#include <assimp/scene.h>
#include "shader.hpp"
#include "Mesh.h"

class Model {
public:
    Model(char *path , bool gamma = false);

    void Darw(Shader shader);

    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

private:

    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif //INC_3D_MODEL_MODEL_H
