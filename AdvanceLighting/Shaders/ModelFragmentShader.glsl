#version 330 core

uniform sampler2D samp;

in vec2 tex;
in vec3 nor;
out vec4 FragColor;


void main(){
	FragColor = texture(samp , tex);
	//FragColor = vec4(1.0f , 1.0f , 1.0f , 1.0f);
}