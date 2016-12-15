#version 430 core

out vec4 fColor;	 // Salida
in vec2 texCoord;	 // Entrada traida del vertex shader

uniform sampler2D theTexture0;	// Textura 0 Lenna
uniform sampler2D theTexture1;	// Textura 1 Fox

void main() {
	fColor = texture(theTexture0, texCoord);
	//fColor = texture(theTexture0, texCoord) + texture(theTexture1, texCoord);  
}