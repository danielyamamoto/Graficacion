#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 mTransform;
uniform sampler2D theTexture0; //

out vec2 texCoord;

float heightMap (vec3 color) {
	return (0.50*color.r + 0.30*color.g + 0.15*color.b);
}

void main() {
	vec4 newPos = vPosition;
	newPos.y = -20.0 * heightMap(texture(theTexture0, vTexCoord).rgb);
	texCoord = vTexCoord;
	gl_Position = mTransform * newPos;
}
