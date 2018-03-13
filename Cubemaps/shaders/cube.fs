#version 330 core

in vec3 TexCoords;
uniform samplerCube cubemap;

out vec4 FragColor;

void main(){
    FragColor = texture(cubemap , vec3(TexCoords.x, TexCoords.y , TexCoords.z));
}