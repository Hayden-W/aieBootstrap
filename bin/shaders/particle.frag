#version 400

in vec4 fColor;
in vec2 fuv;

uniform sampler2D texture;

out vec4 frag_color;


void main()
{
	frag_color = texture2D(texture, fuv) * fColor;
}