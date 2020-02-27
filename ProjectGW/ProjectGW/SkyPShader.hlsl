// Constant Buffer Variables
TextureCube cubeTexture : register(t0);
SamplerState filter : register(s0);

struct OutputVertex
{
    float4 xyzw : SV_Position; // system value
    //float4 rgba : OCOLOR;
    float3 uvw : TEXCOORD;
};

// ***column major vertice are being used instead of row-major , will want to convert 

// anything sent to vertex shader will automatically be interpolated for you coming into pixel shader in direct X, 
float4 main(OutputVertex inputPixel) : SV_TARGET
{

    return cubeTexture.Sample(filter, inputPixel.uvw);
}