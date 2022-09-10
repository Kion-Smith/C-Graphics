
#version 330 core
in vec3 ourColor;
in vec2 ourTextCoord;
out vec4 color;

//Uniform maps to the textures that we assign in the code. Defualt atleas for my drivers 
//allows me to not  have to define a texture and will use texture0
uniform sampler2D containerTexture;
uniform sampler2D faceTexture;

uniform float visibility;

void main()
{
	//color = texture(texture1, ourTextCoord) * vec4(ourColor, 1.0f);
	//mix will mix the two textures. Linearly interpolates if 1.0 the first texture is only seen if 0 only second is seen
	
	//My solution I had a feeling matrix mult would work but I was not sure why
	color = mix(texture(containerTexture, ourTextCoord), texture(faceTexture, ourTextCoord), visibility); //* vec4(ourColor, 1.0f);
	

}