#version 460 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;

out float o_TexIndex;
out vec2 o_TexCoord;

uniform mat4 u_MVP;

void main()
{
    o_TexIndex = texIndex;
    o_TexCoord = texCoord;
    gl_Position = u_MVP * vec4(pos, 0.0, 1.0);
}