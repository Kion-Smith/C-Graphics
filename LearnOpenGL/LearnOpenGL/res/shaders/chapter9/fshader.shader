
#version 330 core
in vec2 ourTextCoord;
out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	color = mix(texture(texture1, ourTextCoord), texture(texture2,ourTextCoord), .2 );
}