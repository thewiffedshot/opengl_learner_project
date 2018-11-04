#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_WindowSize;
uniform float u_SlopeBoundary;

vec2 transformedVec = vec2(gl_FragCoord.x - u_WindowSize.x / 2, gl_FragCoord.y - u_WindowSize.y / 2);
vec2 coordHat = normalize(transformedVec);
float sProduct = dot(vec2(1, 0), coordHat);
float angle = acos(sProduct);

//vec2 origin = vec2(u_WindowSize.x / 2, u_WindowSize.y / 2);
//float slope = (gl_FragCoord.x - origin.x) / (gl_FragCoord.y - origin.y);

void main()
{
	if (angle < u_SlopeBoundary)
	{
		color = u_Color;
	}
	else
	{
		color = vec4(1.0, 0.0, 1.0, 1.0);
	}
}
