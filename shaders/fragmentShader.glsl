#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float interpol = 0.1;

void main()
{
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), interpol);
}	
