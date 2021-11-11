#version 400 core

out vec4 o_Color;

in float o_TexIndex;
in vec2 o_TexCoord;

uniform sampler2D u_Textures[32];
void main()
{
    int index = int(o_TexIndex);
    o_Color = texture(u_Textures[index], o_TexCoord);
}
