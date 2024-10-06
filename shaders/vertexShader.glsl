#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 outColor;

uniform mat4 transform;

void main()
{
	gl_Position = vec4(aPos, 1.0) * transform;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	outColor = vec4(aColor, 1.0f);
}

