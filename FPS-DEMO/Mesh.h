/*
 * File   : Mesh
 * Author : KsGin 
 * Date   : 2018/3/4
 */

#ifndef INC_3D_MODEL_MESH_H
#define INC_3D_MODEL_MESH_H


#include <glm/vec3.hpp>
#include <string>
#include <vector>
#include "shader.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextCoords; //U V
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    /*网格数据*/
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    /*方法*/
    Mesh(std::vector<Vertex> vertices , std::vector<unsigned int> indices , std::vector<Texture> textures);
    void Draw(Shader shader);

private:
    unsigned int VAO;

    unsigned int VBO , EBO;

    void setupMesh();
};


#endif //INC_3D_MODEL_MESH_H
