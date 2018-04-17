#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNor;

uniform mat4 model;

layout (std140) uniform VP{
	mat4 projection;
	mat4 view;
};

out vec2 tex;
out vec3 nor;

void main(){
    nor = aNor * mat3(model);
	tex = aTex;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}