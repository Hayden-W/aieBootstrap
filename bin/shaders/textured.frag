#version 400

in vec2 fuv;
in vec4 fColor;

out vec4 frag_colour;

uniform sampler2D texture;

void main ()
{
	frag_colour = texture2D(texture, fuv) * fColor;
}

