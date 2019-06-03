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

//ssao texture
uniform sampler2D tex_ssao;

//cube reflection map
uniform samplerCube radiance;
uniform samplerCube irradiance;


//shadow depth texture
uniform sampler2D shadowTex;
uniform mat4 lightSpaceMatrix;

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

uniform float specTest;
uniform float glossTest;


//light information in uniform buffer binding 2
layout (std140, binding = 2) uniform lightData
{
	PointLight pointLights[MAX_LIGHTS];
};

//TODO: these should be uniforms
float near = 0.1;
float far = 50.0;
float w = 1.0; //hardness of light-this one should be a hardness map
float fresnelZero = 0.0;
vec3 dirDirection = normalize(vec3(1.0,0.0,0.0)); //for directional light
vec3 dirColor = vec3(1.0f,1.0f,0.88f);

//simple blur function
float Blur(sampler2D tex, int kernelSize)
{
	vec2 texelSize = 1.0 / vec2(textureSize(tex, 0));
	float result = 0.0;

	for (int x = -kernelSize/2; x < kernelSize/2; x++)
	{
		for(int y = -kernelSize/2; y < kernelSize/2; y++)
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(tex, TexCoords + offset).r;
		}
	}

	return result / (kernelSize * kernelSize);
}

//unused function to visualize depth map
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

float attenuation(float dist, float radius, float power)
{

  float att = clamp(1.0 - pow(dist, power)/pow(radius, power), 0.0, 1.0);
  return att;
}

float Fresnel(vec3 V, vec3 L, float F0)
{
  vec3 H = normalize(L + V);
  float dotLH = max(0.0, dot(L,H));
  return F0 + (1.0 - F0) * pow(1.0 - dotLH, 5.0);
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
vec3 LightLevel(vec3 normal, vec3 position, vec3 viewDir, vec3 sint)
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

//computes environment lighting
vec3 EnvironmentLight(vec3 direction, vec3 sint, vec3 viewDir, vec3 env, vec3 envLight, vec3 diffuse, float F0)
{
	vec3 albedo = diffuse / 3.14159;

	float F = Fresnel(viewDir, direction, F0);

	vec3 specColor = mix(diffuse, vec3(1.0), sint);

	vec3 reflectAmount = (albedo * envLight) + (specColor * env * F);

	return reflectAmount;
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

float threshold(in float thr1, in float thr2 , in float val) {
  if (val < thr1) {return 0.0;}
  if (val > thr2) {return 1.0;}
  return val;
}

// averaged pixel difference from 3 color channels
float diff(in vec4 pix1, in vec4 pix2) {
  return (
    abs(pix1.r - pix2.r) +
    abs(pix1.g - pix2.g) +
    abs(pix1.b - pix2.b)
  ) / 3.0;
}

float edge(in sampler2D tex, in vec2 coords, in vec2 renderSize){
  float dx = 1.0 / renderSize.x;
  float dy = 1.0 / renderSize.y;
  vec4 pix[9];

  pix[0] = texture2D(tex, coords + vec2( -1.0 * dx, -1.0 * dy));
  pix[1] = texture2D(tex, coords + vec2( -1.0 * dx , 0.0 * dy));
  pix[2] = texture2D(tex, coords + vec2( -1.0 * dx , 1.0 * dy));
  pix[3] = texture2D(tex, coords + vec2( 0.0 * dx , -1.0 * dy));
  pix[4] = texture2D(tex, coords + vec2( 0.0 * dx , 0.0 * dy));
  pix[5] = texture2D(tex, coords + vec2( 0.0 * dx , 1.0 * dy));
  pix[6] = texture2D(tex, coords + vec2( 1.0 * dx , -1.0 * dy));
  pix[7] = texture2D(tex, coords + vec2( 1.0 * dx , 0.0 * dy));
  pix[8] = texture2D(tex, coords + vec2( 1.0 * dx , 1.0 * dy));

  // average color differences around neighboring pixels
  float delta = (diff(pix[1],pix[7])+
          diff(pix[5],pix[3]) +
          diff(pix[0],pix[8])+
          diff(pix[2],pix[6])
           )/4.;

  return threshold(0.4,0.5,clamp(3.0*delta,0.0,1.0));
}

void main()
{
	float gamma = 2.2;
	vec3 linearConversion = vec3(gamma);

  //load all texture info for fragment
  vec3 normal = texture(gNormal, TexCoords).rgb;
	vec4 diffuse = pow(texture(gColor, TexCoords), vec4(linearConversion, 1.0));
	vec4 specularGloss = pow(texture(gSpecularGloss, TexCoords), vec4(linearConversion, 1.0));
	vec4 emissiveAmbient = pow(texture(gEmissiveAmbient, TexCoords), vec4(linearConversion, 1.0));
	vec3 position = texture(gPosition, TexCoords).rgb;

  //final lighting based on all maps
  //finalColor = (1.0 - f)*fogColor + f * lightColor
	vec3 viewDir = normalize(viewPos - position);
	vec3 rVector = normalize(reflect(-viewDir, normal));

	w = specularGloss.a;

	vec3 env = textureLod(radiance, rVector, (1.0 - w) * 6.0).rgb;
	vec3 envLight = texture(irradiance, normal).rgb;

  vec3 dl = EnvironmentLight(rVector, specularGloss.rgb, viewDir, env, envLight, diffuse.rgb, diffuse.a);
  vec3 pl = LightLevel(normal, position, viewDir, specularGloss.rgb);
  //float fg = attenuation(distance(viewPos, position), 20.0, 2.0);

	vec3 ambient = 0.1 * Blur(tex_ssao, 4) * emissiveAmbient.a * diffuse.rgb;

	//vec4 edgeDetection = (dot(viewDir, normal) > 0.3) ? vec4(1.0) : vec4(1.0, 0.0, 0.0, 1.0);

  vec3 lt = dl + pl;
  color = vec4(lt + emissiveAmbient.rgb + ambient, 1.0 - edge(gPosition, TexCoords, vec2(1280.0, 720.0)));
	//color = vec4(position, 1.0);
	horizontalEmission = blurH();
}
