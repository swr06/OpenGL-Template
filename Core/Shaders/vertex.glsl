#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 u_ModelMatrix = mat4(1.0f);
uniform mat4 u_ViewProjectionMatrix;

void main()
{
	gl_Position = u_ViewProjectionMatrix * vec4(position.x, position.y, position.z, 1.0f); 
	TexCoord = texCoord; 
}