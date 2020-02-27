#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

#include "Lighting.hlsli"

// Constant Buffer Variables
Texture2D txDiffuse : register(t0);
SamplerState filter : register(s0);

struct OutputVertex
{
    float4 xyzw : SV_Position; // system value
    float4 rgba : OCOLOR;
    float4 uvw : TEXCOORD;
    float4 nrm : NORMAL;
    float4 worldpos : WORLDPOS;
};

cbuffer ConstantLights : register(b0)
{
      // Light
    float4 vLightDir[3]; // 0 Direction(values: direction), 1 Point (values: position), 2 Spot (direction)
    float4 vLightColor[3];
    float4 vLightPos[3]; // 0 Directional (none), 1 Point (position), 2 Spot (position)
    float4 vRadius;
    float4 specularColor;
    float4 specularPower;
    float3 cameraPos;
    float buffer;
};


// ***column major vertice are being used instead of row-major , will want to convert 

// anything sent to vertex shader will automatically be interpolated for you coming into pixel shader in direct X, 
float4 main(OutputVertex inputPixel) : SV_TARGET
{
    float3 final_light_color[3] = {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
    };
    float4 finalColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 ambientColor = txDiffuse.Sample(filter, inputPixel.uvw.xy) * 0.25f;
    float intensity[3] = { 1.0f, 1.0f, 1.0f };
    float3 specular_result = { 0.0f, 0.0f, 0.0f };

    
    float4 texColor = (txDiffuse.Sample(filter, inputPixel.uvw.xy)); //* ambientColor);
    float point_light_radius = vRadius.x;
    float inner_cone = vRadius.y;
    float outer_cone = vRadius.z;
    float spot_light_radius = vRadius.w;
    

    
    for (int i = 0; i < 3; i++)
    {
        final_light_color[i] += vLightColor[i];
    }
    
    // Directional Light
    float3 directional_direction = vLightDir[0].xyz;
    float3 directional_color = vLightColor[0].xyz;                                  // diffuse color
    float ratio = DirectionalLightRatio(inputPixel.nrm.xyz, directional_direction); //light intensity
    float3 directional_result = (ratio * directional_color * texColor.xyz);
    final_light_color[0] = directional_result;
    //Specular  
    if (ratio > 0.0f)
    {
        float3 viewDir = normalize(cameraPos.xyz - inputPixel.worldpos.xyz);
        float3 halfVector = normalize((-directional_direction) + viewDir);
        float spec_intensity = max(saturate(pow(dot(normalize(inputPixel.nrm.xyz), halfVector.xyz), specularPower.y)), 0);
        specular_result = saturate(specularColor * spec_intensity * intensity[0]);
        final_light_color[0] = saturate(final_light_color[0] += specular_result);
    }


    // Point Light
    float3 point_direction = PointLightDirection(vLightPos[1].xyz, inputPixel.worldpos.xyz);
    float light_ratio = PointLightRatio(point_direction, inputPixel.nrm.xyz); // diffus?
    float point_attentuation = PointAttentuation(vLightPos[1].xyz, inputPixel.worldpos.xyz, point_light_radius); // make lightRadius(20.f) a variable that is passed through the constant buffer
    float3 point_result = pow(point_attentuation, 2) * light_ratio * final_light_color[1] * texColor.xyz;
    final_light_color[1] = point_result;
    
    // Specular
    if (light_ratio > 0.0f)
    {
        float3 viewDir = normalize(cameraPos.xyz - inputPixel.worldpos.xyz);
        float3 halfVector = normalize((point_direction) + viewDir);
        float spec_intensity = max(pow(saturate(dot(normalize(inputPixel.nrm.xyz), halfVector.xyz)), specularPower.y), 0);
        specular_result = saturate(specularColor * spec_intensity * intensity[1]);
        final_light_color[1] = saturate(final_light_color[1] += specular_result);
    }

    // Spot Light
    float3 spot_direction = SpotLightDirection(vLightPos[2].xyz, inputPixel.worldpos.xyz);
    float spot_surface_ratio = SpotLightSurfaceRatio(spot_direction, vLightDir[2].xyz);
    float spot_factor = SpotLightFactor(spot_surface_ratio, inner_cone);
    // intensity
    float spot_light_ratio = SpotLightRatio(spot_direction, inputPixel.nrm.xyz);
    float spot_attentuation = SpotLightAttenuation(inner_cone, outer_cone, spot_surface_ratio);
    float3 spot_result = pow(spot_attentuation, 2) * spot_factor * spot_light_ratio * final_light_color[2] * texColor.xyz;
    final_light_color[2] = spot_result;
    
    // Specular
    if (spot_light_ratio > 0.0f)
    {
        float3 viewDir = normalize(cameraPos.xyz - inputPixel.worldpos.xyz);
        float3 halfVector = normalize(normalize(spot_direction) + viewDir);
        float spec_intensity = max(saturate(pow(dot(normalize(inputPixel.nrm.xyz), normalize(halfVector.xyz)), specularPower.y)), 0);
        specular_result = saturate(specularColor * spec_intensity * intensity[2]);
        final_light_color[2] = saturate(final_light_color[2] += specular_result);
    }

    
    for (int i = 0; i < 3; i++)
    {
        finalColor.xyz += final_light_color[i];
    }

    finalColor.a = texColor.a;
    
    finalColor.xyz += ambientColor;
    
    return float4(saturate(finalColor.xyz), finalColor.a);
    //return float4(specular_result, 1);
    //return float4(final_light_color[0], 1);
}