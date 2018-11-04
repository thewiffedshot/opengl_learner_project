#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec4 u_Color2;
uniform vec2 u_WindowSize;
uniform float u_SlopeBoundary;
uniform bool u_Switched;

vec2 transformedVec = vec2(gl_FragCoord.x - u_WindowSize.x / 2, gl_FragCoord.y - u_WindowSize.y / 2);
vec2 coordHat = normalize(transformedVec);
float sProductCC = dot(vec2(1, 0), coordHat);
float sProductC = dot(vec2(-1, 0), coordHat);
float angleCC = acos(sProductCC);
float angleC = acos(sProductC);

void main()
{
	if (gl_FragCoord.y > u_WindowSize.y / 2)
	{
		if (!u_Switched)
		{
			if (angleCC < u_SlopeBoundary)
			{
				color = u_Color;
			}
			else
			{
				color = u_Color2;
			}
		}
		else if (angleCC > u_SlopeBoundary)
		{
			color = u_Color;
		}
		else
		{
			color = u_Color2;
		}
	}
	else if (!u_Switched)
	{
		if (angleC < u_SlopeBoundary)
		{
			color = u_Color2;
		}
		else
		{
			color = u_Color;
		}
	}
	else if (angleC > u_SlopeBoundary)
	{
		color = u_Color2;
	}
	else
	{
		color = u_Color;
	}
}
