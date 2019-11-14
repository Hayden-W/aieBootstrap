#version 400

//FBX Anim FRAG

in vec2 frag_texcoord;

uniform sampler2D texture;

out vec4 frag_color;

void main()
{
	frag_color = texture2D(texture, frag_texcoord);
}