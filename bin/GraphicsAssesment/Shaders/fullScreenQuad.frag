#version 400

//FULLSCREEN QUAD

in vec2 fuv;
out vec4 frag_color;

uniform sampler2D texture;

void main()
{
	vec4 color = texture2D(texture, fuv);
	vec3 rgb = vec3(1, 1, 1) - color.rgb;

	frag_color = vec4(rgb, color.a);
}
