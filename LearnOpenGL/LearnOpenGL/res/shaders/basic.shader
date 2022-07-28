//To use this shader must use The Cherno's shader parsing
#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
#shader fragment
#version 330 core

out vec4 fragColor;

void main()
{
	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}