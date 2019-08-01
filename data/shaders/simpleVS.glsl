#version 450 core

layout(location = 0) in vec3 vsPos;
layout(location = 1) in vec2 vsTexCoord;

out vec2 psTexCoord;

layout(binding = 0, std140) uniform ConstantBuffer {
	mat4 gWorldMat;
	mat4 gViewMat;
	mat4 gProjMat;
	vec2 gUvOffset;
	vec2 gUvSize;
};

void main() {
	gl_Position = gProjMat*gViewMat*gWorldMat*vec4(vsPos, 1.0);
	psTexCoord = vsTexCoord*gUvSize + gUvOffset;
}