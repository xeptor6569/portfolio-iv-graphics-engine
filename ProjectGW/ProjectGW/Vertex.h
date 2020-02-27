#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Tex;
	XMFLOAT3 Normal;
};