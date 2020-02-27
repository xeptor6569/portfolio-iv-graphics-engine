#pragma pack_matrix( row_major )

//#include "SharedDefines.h"

#define MAX_SEGMENTS 8

// the output stream must contain clip space verticies (if sent to the rasterizer)
struct GS_IN
{
    float3 xyz : POSITION;
    float3 uvw : TEXCOORD;
    float3 nrm : NORMAL;
};

struct GS_OUT
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
// you may not exceed 1024 scalars. the max number of scalars output from this shader is 24

//[maxvertexcount(MAX_SEGMENTS * 8 + 3)]
[maxvertexcount(3)]
// this operation builds each point into a blade of grass 
void main(point GS_IN input[1], inout TriangleStream<GS_OUT> output)
{   
    float bladeWidth = 2.0f; //theScene.BladeWidth
    float bladeHeight = 1.0f; //theScene.BladeHeight
    float halfBW = bladeWidth * 0.5;
    
    GS_OUT verts[3];
    
    for (uint i = 0; i < 3; ++i)
    {
	// colors
        verts[i].rgba = float4(0.0f, 1.0f, 0.1f, 1);
	// positions
        verts[i].xyzw = float4(input[0].xyz, 1);
    
    // uvs
        verts[i].uvw = float4(input[0].uvw, 1);
    // normals
        verts[i].nrm = mul(float4(input[0].nrm, 0), worldMatrix).xyzw;

    }
 
    // shift to make triangle
    verts[0].xyzw.x -= halfBW;
    verts[1].xyzw.y += bladeHeight;
    verts[2].xyzw.x += halfBW;
    
    for (uint i = 0; i < 3; ++i)
    {        
        verts[i].xyzw = mul(verts[i].xyzw, worldMatrix);
        verts[i].worldpos = verts[i].xyzw;
        verts[i].xyzw = mul(verts[i].xyzw, viewMatrix);
        verts[i].xyzw = mul(verts[i].xyzw, projectionMatrix);
        output.Append(verts[i]);
    }
    
    //output.RestartStrip();
    //output.Append(verts[2]);
    //output.Append(verts[1]);
    //output.Append(verts[0]);
    
}