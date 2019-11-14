#version 410

//FBX Anim VERT

in vec4 position;
in vec4 normal;
in vec4 tangent;
in vec2 tex_coord;
in vec4 weights;
in vec4 indices;

//out vec3 frag_normal;
//out vec3 frag_position;
//out vec3 frag_tangent;
//out vec3 frag_bitangent;
out vec2 frag_texcoord;

uniform mat4 projection_view;
uniform mat4 model;

// we need to give our bone array a limit
const int MAX_BONES = 128;
uniform mat4 bones[MAX_BONES];

void main()
{
	//frag_position = position.xyz;
	//frag_normal = normal.xyz;
	//frag_tangent = tangent.xyz;
	//frag_bitangent = cross(normal.xyz, tangent.xyz);
	frag_texcoord = tex_coord;

	// cast the indices to integer's so they can index an array
	ivec4 index = ivec4(indices);
	// sample bones and blend up to 4
	vec4 P = bones[ index.x ] * position * weights.x;
	P += bones[ index.y ] * position * weights.y;
	P += bones[ index.z ] * position * weights.z;
	P += bones[ index.w ] * position * weights.w;
	gl_Position = projection_view * model * P;
}