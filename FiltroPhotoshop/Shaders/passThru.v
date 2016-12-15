#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 mTransform;
uniform sampler2D theTexture0; // Lenna
uniform sampler2D theTexture1; // Fox
uniform sampler2D theTexture2; // HeightMap

uniform sampler2D Tex;
uniform sampler1D GradientMap;
uniform sampler1D GradientGround;

varying vec2 uv;
out vec2 texCoord;

float luminosity (vec3 color) {
	return (0.49*color.r + 0.51*color.g + 0.14*color.b);
}

//void main()
//{
	//vec4 newPos = vPosition;
	//newPos.y = 2.0 * luminosity(texture(theTexture0, vTexCoord).rgb);
	//texCoord = vTexCoord;
	//gl_Position = mTransform * newPos;
//}

void main() 
{	
	vec3 color = texture2D(Tex, uv).xyz;

	// Split-tone
	vec4 colorDesat = Desaturate(color, 1.0);
	vec3 splitColor = texture1D(GradientMap, colorDesat.r).rgb;
	vec3 pass1 = BlendColor(color, splitColor);

	// Vertical gradient
	vec4 verticalGradientColor = texture1D(GradientGround, uv.y);
	vec3 pass2 = mix(pass1, BlendColor(pass1, verticalGradientColor.rgb), verticalGradientColor.a);

	// Luminosity
	vec3 pass3 = mix(pass2, BlendLuminosity(pass2, color + vec3(0.08)), 0.5);

	// Linear light at 40%
	vec3 pass4 = mix(pass3, BlendLinearLight(pass3, color), 0.4);

	// Final
	gl_FragColor = vec4(pass4, 1.0);
}