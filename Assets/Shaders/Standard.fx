// Description: Standard effect to build into a general rendering effect

cbuffer TransormBuffer : register(b0)
{
	matrix wvp;
    matrix world;
    float3 viewPosition;
}
cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
    float4 lightAmbient;
    float4 lightDiffuse;
    float4 lightSpecular;
}

Texture2D textureMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
    float3 worldNormal : NORMAL;
    float3 worldTangent : TANGENT;
	float2 texCoord : TEXCOORD0;
    float3 dirToLight : TEXCOORD1;
    float3 dirToView : TEXCOORD2;
};

VS_OUTPUT VS(VS_INPUT input)
{
    matrix toWorld = world;
    matrix toNDC = wvp;
	
	VS_OUTPUT output;
	output.position = mul(float4(input.position, 1.0f), toNDC);
    output.worldNormal = mul(input.normal, (float3x3) toWorld);
    output.worldTangent = mul(input.tangent, (float3x3) toWorld);
	output.texCoord = input.texCoord;
    output.dirToLight = -lightDirection;
    output.dirToView = normalize(viewPosition - mul(float4(input.position, 1.0f), world).xyz);
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 n = normalize(input.worldNormal);
    
    // using normal map to get the new normal
    float3 t = normalize(input.worldTangent);
    float3 b = normalize(cross(n, t));
    float3x3 tbnw = float3x3(t, b, n);
    float4 normalMapColor = normalMap.Sample(textureSampler, input.texCoord);
    float3 unpackedNormalmap = normalize(float3((normalMapColor.xy * 2.0f) - 1.0f, normalMapColor.z));
    n = normalize(mul(unpackedNormalmap, tbnw));
    
    float3 light = normalize(input.dirToLight);
    float3 view = normalize(input.dirToView);
    
    float4 ambient = lightAmbient;
    
    float d = saturate(dot(light, n));
    float4 diffuse = d * lightDiffuse;
    
    float3 r = reflect(-light, n);
    float base = saturate(dot(r, view));
    float s = pow(base, 10);
    float4 specular = s * lightSpecular;
    
    float4 diffuseMapColor = textureMap.Sample(textureSampler, input.texCoord);
    
    //return textureMap.Sample(textureSampler, input.texCoord);
    
    float4 finalColor = (ambient + diffuse) * diffuseMapColor + specular;
    
    return finalColor;
}