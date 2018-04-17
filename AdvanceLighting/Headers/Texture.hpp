/*
 * File   : Texture
 * Author : KsGin 
 * Date   : 2018/4/17
 */

#ifndef ADVANCELIGHTING_TEXTURE_HPP
#define ADVANCELIGHTING_TEXTURE_HPP


#include <string>
#include <GL/glew.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


class Texture {
public:
    unsigned int ID;
    Texture(const char * fileName , bool isAlpha){
        glGenTextures(1 , &ID);
        glBindTexture(GL_TEXTURE_2D , ID);

        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_R , GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

        auto type = GL_RGB;
        if (isAlpha) type = GL_RGBA;

        int width , height , nrChannels;
        unsigned char * data = stbi_load(fileName , &width , &height , &nrChannels , 0);
        if (data){
            glTexImage2D(GL_TEXTURE_2D , 0 , type , width , height , 0 , type , GL_UNSIGNED_BYTE , data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

    void Use(){
        glBindTexture(GL_TEXTURE_2D , ID);
    }
};


#endif //ADVANCELIGHTING_TEXTURE_HPP
