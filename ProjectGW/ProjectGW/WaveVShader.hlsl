#pragma pack_matrix( row_major )
//rule of 3
// 3 thrings must match
// 1. C++ Vertex Struct
// 2. Input Layout
// 3. HLSL Vertex Struct

struct InputVertex
{
    float3 xyz : POSITION;
    float3 uvw : TEXCOORD;
    float3 nrm : NORMAL;
};

struct OutputVertex
{
    float4 xyzw : SV_Position; // system value
    float4 rgba : OCOLOR;
    float4 uvw : TEXCOORD;
    float4 nrm : NORMAL;
    float4 worldpos : WORLDPOS;
};

cbuffer SHADER_VARAIBLES : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix; 
};

cbuffer ConstantLights : register(b1)
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

OutputVertex main(InputVertex input)
{
    OutputVertex output = (OutputVertex) 0;
    
    input.xyz.y += cos(input.xyz.x + specularPower.z * 0.05) * .09f;
    //input.xyz.z += cos(input.xyz.x + specularPower.z * 0.05) * .09f;


    output.xyzw = float4(input.xyz, 1); //insert 1 for w
    output.rgba.rgb = input.nrm;
    output.uvw = float4(input.uvw, 1);
    output.nrm = mul(float4(input.nrm, 0), worldMatrix).xyzw;
    
    // DO math here (shader intrinsics)
    output.xyzw = mul(output.xyzw, worldMatrix);
    // Position of the vertex in the world
    output.worldpos = output.xyzw;
    
    output.xyzw = mul(output.xyzw, viewMatrix);
    output.xyzw = mul(output.xyzw, projectionMatrix);
    // dont do prespective divide (will be done by rasterizer)

    
    return output;
}