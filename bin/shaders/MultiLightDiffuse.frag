#version 400

in vec2 fuv;
in vec4 fColor;
in vec3 fNormal;
in vec4 fPosition;

out vec4 frag_colour;

uniform sampler2D texture;

uniform int arraySize;
uniform float lightAmbientStrength;
uniform vec3 lightPositions[10];
uniform vec3 lightColors[10];
uniform bool useTexture;
uniform vec3 cameraPos;
uniform float specularPower;
//vec3[20] diffuse;
void main ()
{
	frag_colour = vec4(0,0,0,0);
	for(int i = 0; i < arraySize; i++)
	{
		vec3 norm = normalize(fNormal);
		vec3 lightDir = normalize(fPosition.xyz - lightPositions[i].xyz);
	
		float diff = max(dot(norm, -lightDir), 0.0);
		vec3 diffuse = diff * lightColors[i];
	
		vec3 E = normalize(cameraPos - fPosition.xyz);
		vec3 R = reflect(lightDir, fNormal.xyz);
		float s = max(dot(E, R), 0.0);
		s = pow(s, specularPower);
	
		vec3 ambient = lightColors[i] * lightAmbientStrength;
		if(useTexture)
		{
			frag_colour += vec4(ambient + diffuse + lightColors[i] * s, 1.0) * texture2D(texture, fuv) * fColor;
		}
		else
		{
			frag_colour += vec4(ambient + diffuse + lightColors[i] * s, 1.0) * fColor;
		}
	}
	
}
