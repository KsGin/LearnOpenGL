/*
 * File   : Model
 * Author : KsGin 
 * Date   : 2018/4/17
 */

#ifndef ADVANCELIGHTING_MODEL_HPP
#define ADVANCELIGHTING_MODEL_HPP

#include <fstream>
#include <iostream>
#include <GL/glew.h>

class Model {
private:
    float *vertices;
    unsigned int *indices;
    unsigned int indexCount;


    void loadModel(const char *fileName) {
        std::ifstream ifs(fileName);
        if (!ifs.is_open()) {
            std::cout << "open model file error" << std::endl;
            return;
        }
        int vertexCount;
        ifs >> vertexCount >> indexCount;

        vertices = new float[vertexCount];
        indices = new unsigned int[indexCount];

        for (auto i = 0; i < vertexCount; ++i) {
            ifs >> vertices[i];
        }

        for (auto i = 0; i < indexCount; ++i) {
            ifs >> indices[i];
        }

        ifs.close();
    }

public:
    unsigned int vertexArrayObject, indexArrayObject , vertexBufferObject;
    Model(const char *fileName) {
        loadModel(fileName);
        glGenBuffers(1, &vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, static_cast<void *>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) (sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        glGenBuffers(1 , &indexArrayObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , indexArrayObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

    }

    void Use() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , indexArrayObject);
    }

    int IndexCount() {
        return indexCount;
    }
};

#endif //ADVANCELIGHTING_MODEL_HPP
