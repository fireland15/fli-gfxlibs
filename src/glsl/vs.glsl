#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) uniform vec4 ucolor;
layout(location = 3) uniform mat4 projection;

layout(location = 7) in vec3 inst_position;

out vec4 vColor;

void main() {
	vec3 finalposition = position + inst_position;

	gl_Position = projection * vec4(finalposition, 1);
	vColor = color + ucolor;
}
