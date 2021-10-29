#version 460 core

layout(location = 0) in vec2 pos
layout(location = 1) in float texIndex


void main()
{
    gl_Position = pos;
}