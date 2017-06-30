#version 330 core

out vec4 FragColor;

in vec3 vertexColor; // the input variable from the vertex shader (same name and sametype)
in vec2 TexCoord;

uniform sampler2D myTexture;


void main()
{
	FragColor = texture(myTexture, TexCoord);
}
