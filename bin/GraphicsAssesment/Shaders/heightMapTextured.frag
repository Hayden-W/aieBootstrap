#version 400

//HeightMap

in vec2 fuv;
in vec4 fColor;
in vec3 fNormal;
in vec4 fPosition;

out vec4 frag_colour;

uniform sampler2D texture;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;


uniform float maxDist;
uniform vec3 ambientLight;
uniform int arraySize;
uniform float lightAmbientStrength;
uniform vec3 lightPositions[10];
uniform vec3 lightColors[10];
uniform bool useTexture;
uniform bool useHeightTextures;
uniform vec3 cameraPos;
uniform float specularPower;

void main ()
{
	frag_colour = vec4(0,0,0,0);

	vec4 currentPixel = vec4(0, 0, 0, 0);
	float currentSpecPow = specularPower;
	if(useHeightTextures)
	{
		if(fPosition.y <= -0.5f)
		{
			currentPixel = texture2D(texture0, fuv) * fColor;
			currentSpecPow *= 0.01f;
		}
		else
		{
			if(fPosition.y > -0.5f && fPosition.y <= 0.0f)
			{
				currentPixel = texture2D(texture1, fuv) * fColor;
				currentSpecPow *= 0.3f;
			}
			else
			{
				if(fPosition.y > 0.0f && fPosition.y <= 0.5f)
				{
					currentPixel = texture2D(texture2, fuv) * fColor;
					currentSpecPow *= 0.6f;
				}
				else
				{
					if(fPosition.y > 0.5f)
					{
						currentPixel = texture2D(texture3, fuv) * fColor;
					}
				}
			}
		}
	}
	else
	{
		currentPixel = texture2D(texture, fuv) * fColor;
	}

	frag_colour += vec4(ambientLight, 1.0) * currentPixel;
	
	for(int i = 0; i < arraySize; i++)
	{
		vec3 diffuse = vec3(0, 0, 0);
		vec3 specularLight = vec3(0, 0, 0);
		vec3 ambient = vec3(0, 0, 0);
		float s = 0;
		float inverseDist = 0;
		float dist = sqrt((fPosition.y - lightPositions[i].y) * 
                     		  (fPosition.y - lightPositions[i].y)
		   		 +(fPosition.x - lightPositions[i].x) * 
                     		  (fPosition.x - lightPositions[i].x)
				 +(fPosition.z - lightPositions[i].z) * 
                     		  (fPosition.z - lightPositions[i].z));

		if(dist < maxDist)
		{
			inverseDist = 1 - dist / maxDist;

			vec3 norm = normalize(fNormal);
			vec3 lightDir = normalize(fPosition.xyz - lightPositions[i].xyz);

			float diff = max(dot(norm, -lightDir), 0.0);
			diffuse = diff * lightColors[i];
			diffuse *= inverseDist;	

			vec3 E = normalize(cameraPos - fPosition.xyz);
			vec3 R = reflect(lightDir, fNormal.xyz);
			s = max(dot(E, R), 0.0);
			s = pow(s, currentSpecPow);

			specularLight = lightColors[i] * s;
			specularLight *= inverseDist;

			ambient = lightColors[i] * lightAmbientStrength;
			ambient *= min(1, max(0, inverseDist));
			//min(1, max(0, t))
		}

		if(useTexture)
		{
			frag_colour += vec4(ambient + diffuse + specularLight, 1.0) * currentPixel;
		}
		else
		{
			frag_colour += vec4(ambient + ambient + diffuse + specularLight, 1.0) * fColor;
		}
	}
}
