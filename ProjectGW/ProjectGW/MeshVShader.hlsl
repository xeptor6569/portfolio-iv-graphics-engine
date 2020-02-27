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


OutputVertex main(InputVertex input)
{
    OutputVertex output = (OutputVertex) 0;
    
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