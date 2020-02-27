#pragma pack_matrix( row_major )
//rule of 3
// 3 thrings must match
// 1. C++ Vertex Struct
// 2. Input Layout
// 3. HLSL Vertex Struct

struct VS_IN
{
    float3 xyz : POSITION;
    float3 uvw : TEXCOORD;
    float3 nrm : NORMAL;
};

struct VS_OUT
{
    float3 xyz : POSITION;
    float3 uvw : TEXCOORD;
    float3 nrm : NORMAL;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.xyz = input.xyz;
    output.uvw = input.uvw;
    output.nrm = input.nrm;
    
    return output;
}