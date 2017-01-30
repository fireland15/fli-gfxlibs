#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) uniform vec4 ucolor;
layout(location = 3) uniform mat4 projection;

out vec4 vColor;

void main() {
	gl_Position = projection * vec4(position, 1);
	vColor = color + ucolor;
}
