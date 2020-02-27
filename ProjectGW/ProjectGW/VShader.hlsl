#pragma pack_matrix( row_major )
//rule of 3
// 3 thrings must match
// 1. C++ Vertex Struct
// 2. Input Layout
// 3. HLSL Vertex Struct

struct InputVertex
{
    float4 xyzw : POSITION;
    float4 rgba : COLOR;
	//VEC_2D uv;
};

struct OutputVertex
{
    float4 xyzw : SV_Position; // system value
    float4 rgba : OCOLOR;
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
    output.xyzw = input.xyzw;
    output.rgba = input.rgba;
    
    // DO math here (shader intrinsics)
    output.xyzw = mul(output.xyzw, worldMatrix);
    output.xyzw = mul(output.xyzw, viewMatrix);
    output.xyzw = mul(output.xyzw, projectionMatrix);
    // dont do prespective divide (will be done by rasterizer)

    
    return output;
}