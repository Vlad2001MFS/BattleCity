#version 450 core

in vec2 psTexCoord;

out vec4 resultColor;

layout(binding = 0) uniform sampler2D gDiffuseMap;

void main() {
	resultColor = texture2D(gDiffuseMap, psTexCoord);
}