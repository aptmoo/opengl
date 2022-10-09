// debug.shader: debug and testing shader

#shader vertex
#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexColor;

out vec3 vColor;

void main()
{
    vColor = vertexColor;
    gl_Position = vec4(vertexPosition, 1.0, 1.0);
}

#shader fragment
#version 330 core

in vec3 vColor;

out vec4 color;

uniform vec4 u_Color;

void main()
{
    // color = vec4(vColor.xyz, 1.0);
}