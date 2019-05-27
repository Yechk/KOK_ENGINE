//this shader contains post process and deferred lighting techniques for the ENGINE
//
//draws on a full screen quad.
#version 460 core

layout(location = 0) out vec4 color;
layout(location = 1) out vec3 horizontalEmission;

in vec2 TexCoords;

//input textures from gBuffer
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gEmissiveAmbient;
uniform sampler2D gColor;
uniform sampler2D gSpecularGloss;

//cube reflection map
uniform samplerCube skyBox;
uniform samplerCube irradiance;

//testing values
uniform vec3 testSpecular;
uniform float testGloss;
uniform vec3 testEmissive;


//shadow depth texture
uniform sampler2D shadowTex;
uniform mat4 lightSpaceMatrix;

//texture for cel map
uniform sampler2D gCel;

uniform vec3 viewPos;

//array of lights
//sent from a uniform buffer
struct PointLight
{
	vec3 data;
	vec3 position;
	vec3 color;
};
//if more than 10 lights exist, take closest lights only
const int MAX_LIGHTS = 10;
float litByEnvironment = 1.0;
uniform int numLights;


//light information in uniform buffer binding 2
layout (std140, binding = 2) uniform lightData
{
	PointLight pointLights[MAX_LIGHTS];
};

//TODO: these should be uniforms
float near = 0.1;
float far = 50.0;
float w = 1.0; //hardness of light-this one should be a hardness map
vec3 dirDirection = normalize(vec3(0.0,0.0,1.0)); //for directional light
vec3 dirColor = vec3(1.0f,1.0f,0.88f);

//unused function to visualize depth map
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

//cel shades a float
//read from cel map-corresponds to values 0-1
float CelLight(float init, vec3 sketch)
{
  float cel = step(0.4, init);
  cel += step(0.2, init) * 0.4 * sketch.b;
  return clamp(cel,0.0,1.0);
}

float attenuation(float dist, float radius, float power)
{

  float att = clamp(1.0 - pow(dist, power)/pow(radius, power), 0.0, 1.0);
  return att;
}

float ggxSpecular(vec3 N, vec3 V, vec3 L, float roughness, float F0)
{
  float alpha = roughness*roughness;
  vec3 H = normalize(L + V);
  float dotLH = max(0.0, dot(L,H));
  float dotNH = max(0.0, dot(N,H));
  float dotNL = max(0.0, dot(N,L));
  float alphaSqr = alpha * alpha;
  float denom = dotNH * dotNH * (alphaSqr - 1.0) + 1.0;
  float D = alphaSqr / (3.141592653589793 * denom * denom);
  float F = F0 + (1.0 - F0) * pow(1.0 - dotLH, 5.0);
  float k = 0.5 * alpha;
  float k2 = k * k;
  return max(0.001, dotNL * D * F / (dotLH*dotLH*(1.0-k2)+k2));
}

vec3 SpecLight(vec3 direction, vec3 normal, vec3 viewDir, vec3 sint, vec3 color)
{
	//specular shading
	vec3 reflectDir = reflect(-direction, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0 + (100.0 * w));
	vec3 specular = sint * vec3(spec) * clamp(dirColor*2.0, 0, 1);

	return specular;
}

//call this function to look through all point lights and get final light value
vec3 LightLevel(vec3 normal, vec3 position, vec3 sketch, vec3 viewDir, vec3 sint)
{
	//if (numLights > MAX_LIGHTS) return vec3(0,1,0);

	vec3 diff;

	for(int i = 0; i < numLights; i++)
	{
		float dist = distance(pointLights[i].position, position);

		float att = attenuation(dist, pointLights[i].data.x, pointLights[i].data.y);
		att *= att;

		vec3 lightDir = normalize(pointLights[i].position - position);

		//specularity
		vec3 specular = SpecLight(lightDir, normal, viewDir, sint, pointLights[i].color);

		diff += max(dot(normal,lightDir), 0.0) * pointLights[i].color;
		diff += specular;
		diff *= att;
	}

	return diff;
}

float Blur(sampler2D tex, int kernelSize, vec2 coords)
{
	vec2 texelSize = 1.0 / vec2(textureSize(tex, 0));
	float result = 0.0;

	for (int x = -kernelSize/2; x < kernelSize/2; x++)
	{
		for(int y = -kernelSize/2; y < kernelSize/2; y++)
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(tex, coords + offset).r;
		}
	}

	return result / (kernelSize * kernelSize);
}

float ShadowValue(vec3 pos, vec3 normal, vec3 direction)
{
	vec4 fragPosLightSpace = lightSpaceMatrix * vec4(pos, 1.0);

	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(shadowTex, projCoords.xy).r;
	float currentDepth = projCoords.z;

	float bias = max(0.01 * (1.0 - dot(normal, direction)), 0.001);

	float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

	if(projCoords.z > 1.0) shadow = 0.0;

	return 1.0 - shadow;
}

float Squish(float value, float inMin, float inMax, float outMin, float outMax)
{
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

//computes directional light
vec3 DirectionalLight(vec3 normal, vec3 direction, vec3 sketch, vec3 sint, vec3 viewDir, vec3 pos, vec3 env)
{

	float wCalc = 1.0 - w;
	float wAdjust = Squish(wCalc, 0.0, 1.0, 0.0, 0.3);
	float absorption = Squish(w, 0.0, 1.0, 0.4, 1.0);
  float intensity =
		max((dot(normal,direction) + wAdjust) / (1.0 + wAdjust), 0.05); //light should never be absolute zero

	vec3 diff = absorption * intensity * dirColor;
	vec3 envColor = absorption * env;

	diff = mix(diff, envColor, litByEnvironment);

	vec3 specular = sint * ggxSpecular(normal, viewDir, direction, max(0.17, wCalc), 0.9);

	float shade = ShadowValue(pos, normal, direction);

	return ((diff*shade) + (specular*shade));
}

vec3 blurH()
{
	float weight[10] = float[] (0.197413, 0.174667, 0.120978, 0.065591, 0.027835, 0.009245, 0.002403, 0.000489, 0.000078, 0.00001); //TODO: definitely bake into a texture

	vec2 texelSize = 2.0 / vec2(textureSize(gEmissiveAmbient, 0));

  //blur function
  vec3 rt = texture(gEmissiveAmbient, TexCoords).rgb * weight[0];

	for (int x = 1; x < 10; x++)
	{
		rt += texture(gEmissiveAmbient, TexCoords + (texelSize * vec2(x, 0.0))).rgb * weight[x];
    rt += texture(gEmissiveAmbient, TexCoords - (texelSize * vec2(x, 0.0))).rgb * weight[x];
	}

	return rt;
}

void main()
{
  //load all texture info for fragment
  vec3 normal = texture(gNormal, TexCoords).rgb;
	vec4 diffuse = texture(gColor, TexCoords);
	vec4 specularGloss = texture(gSpecularGloss, TexCoords);
	vec4 emissiveAmbient = texture(gEmissiveAmbient, TexCoords);
	vec3 position = texture(gPosition, TexCoords).rgb;
  vec3 sketch = texture(gCel, TexCoords*8.0).rgb;

  //final lighting based on all maps
  //finalColor = (1.0 - f)*fogColor + f * lightColor
	vec3 viewDir = normalize(viewPos - position);
	vec3 rVector = reflect(-viewDir, normal);

	w= min(1.0, specularGloss.a);

	vec3 env = texture(skyBox, rVector).rgb;
	vec3 envLight = texture(irradiance, rVector).rgb;

  vec3 dl = DirectionalLight(normal, dirDirection, sketch, specularGloss.rgb, viewDir, position, envLight);
  vec3 pl = LightLevel(normal, position, sketch, viewDir, specularGloss.rgb);
  float fg = attenuation(distance(viewPos, position), 20.0, 2.0);
	float reflectAmount = pow(w, 1.5);
  vec3 lt = mix(diffuse.rgb, env, reflectAmount) * (dl + pl);
  color = vec4(lt + emissiveAmbient.rgb, emissiveAmbient.a);
	horizontalEmission = blurH();
}
