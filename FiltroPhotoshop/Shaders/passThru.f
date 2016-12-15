#version 430 core

out vec4 fColor;	 // Salida
in vec2 texCoord;	 // Entrada traida del vertex shader

uniform sampler2D theTexture0;	// Textura 0 Cat
uniform sampler2D theTexture1;	// Textura 1 Lenna
uniform sampler2D theTexture2;  // Textura 2 HeightMap

void main() {
	fColor = texture(theTexture0, texCoord);
	//fColor = texture(theTexture0, texCoord) + texture(theTexture1, texCoord);
	//fColor = texture(theTexture0, texCoord) + texture(theTexture1, texCoord) + texture(theTexture2, texCoord);
	//fColor = mix(texture(theTexture0, texCoord), texture(theTexture1, texCoord), 0.5); // Mezcla las imágenes

	// Split-tone
	vec4 colorDesat = Desaturate(color, 1.0);
	vec3 splitColor = texture1D(GradientMap, colorDesat.r).rgb;
	vec3 result = BlendColor(color, splitColor);
}