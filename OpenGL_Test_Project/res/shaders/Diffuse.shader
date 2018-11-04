#shader vertex
#version 330 core

layout(location = 0) in vec3 position_worldspace;
layout(location = 1) in vec3 vNormal_worldspace;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
uniform vec3 u_lightPos;

out vec4 normal_cameraspace;
out vec4 pos_cameraspace;
out vec4 lightpos_cameraspace;

void main()
{
	mat4 transformation = u_projMatrix * u_viewMatrix * u_modelMatrix;
	gl_Position = transformation * vec4(position_worldspace, 1);
	normal_cameraspace = normalize(u_viewMatrix * u_modelMatrix * vec4(vNormal_worldspace, 0));
	pos_cameraspace = u_viewMatrix * u_modelMatrix * vec4(position_worldspace, 1);
	lightpos_cameraspace = u_viewMatrix * vec4(u_lightPos, 1);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 normal_cameraspace;
in vec4 pos_cameraspace;
in vec4 lightpos_cameraspace;

vec4 lightDir = normalize(lightpos_cameraspace - pos_cameraspace);

uniform vec4 u_MaterialDiffuseColor;
uniform vec4 u_LightColor;
uniform float u_LightDistance;
uniform float u_LightPower;
uniform vec3 u_AmbientLight;

float cosTheta = clamp(dot(normalize(normal_cameraspace.xyz), lightDir.xyz), 0, 1);

void main()
{
	color = vec4(u_AmbientLight, 0) + vec4(u_MaterialDiffuseColor.xyz * u_LightColor.xyz * cosTheta * u_LightPower / (u_LightDistance * u_LightDistance), 1);
}