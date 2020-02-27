#pragma once


float DirectionalLightRatio(float3 normal, float3 lightDir)
{
    return saturate(dot(normalize(normal), -normalize(lightDir)));
}

float3 PointLightDirection(float3 lightPos, float3 worldPos)
{
    return normalize(lightPos - worldPos);
}

float PointLightRatio(float3 pointDir, float3 normal)
{
    return saturate(dot(pointDir, normalize(normal)));
}

float PointAttentuation(float3 lightPos, float3 surfacePos, float lightRadius)
{
    return 1.0f - saturate(length(lightPos - surfacePos) / lightRadius);
}

float3 SpotLightDirection(float3 lightPos, float3 surfacePos)
{
    return normalize(lightPos - surfacePos);
}

float SpotLightSurfaceRatio(float3 lightDir, float3 coneDir)
{
    return saturate(dot(-lightDir, normalize(coneDir)));
}

float SpotLightFactor(float surfaceRatio, float coneRatio) //coneratio innerratio
{
    return (surfaceRatio > coneRatio) ? 1 : 0;

}

float SpotLightRatio(float3 lightDir, float3 surfaceNormal)
{
    return saturate(dot(lightDir, normalize(surfaceNormal)));
}

float SpotAttentuation(float innerConeRatio, float surfaceRatio, float outerConeRatio)
{
    return 1.0f - saturate((innerConeRatio - surfaceRatio) / (innerConeRatio - outerConeRatio));

}

float SpotLightAttenuation(float innerConeRatio, float outerConeRatio, float surfaceRatio)
{
    return smoothstep(innerConeRatio, outerConeRatio, surfaceRatio);
}
