
struct OutputVertex
{
    float4 xyzw : SV_Position; // system value
    float4 rgba : OCOLOR;
};

// ***column major vertice are being used instead of row-major , will want to convert 

// anything sent to vertex shader will automatically be interpolated for you coming into pixel shader in direct X, 
float4 main(OutputVertex inputPixel) : SV_TARGET
{
    //return float4(1.0f, 0.0f, 0.0f, 1.0f);
    return inputPixel.rgba;
}