#version 430 core

in vec3 position;
in vec3 color;

out vec4 fColor;

void main() {
	fColor = vec4(color, 1.0);
	gl_Position = vec4(position);
}