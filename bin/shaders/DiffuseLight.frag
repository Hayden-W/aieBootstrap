#version 400

in vec2 fuv;
in vec4 fColor;
in vec3 fNormal;
in vec4 fPosition;

out vec4 frag_colour;

uniform sampler2D texture;

uniform float lightAmbientStrength;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform bool useTexture;
uniform vec3 cameraPos;
uniform float specularPower;

void main ()
{
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(fPosition.xyz - lightPosition.xyz);
	
	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec3 E = normalize(cameraPos - fPosition.xyz);
	vec3 R = reflect(lightDir, fNormal.xyz);
	float s = max(dot(E, R), 0.0);
	s = pow(s, specularPower);
	
	vec3 ambient = lightColor * lightAmbientStrength;
	if(useTexture)
	{
		frag_colour = vec4(ambient + diffuse + lightColor * s, 1.0) * texture2D(texture, fuv) * fColor;
	}
	else
	{
		frag_colour = vec4(ambient + diffuse + lightColor * s, 1.0) * fColor;
	}
	//frag_colour = fColor;
}