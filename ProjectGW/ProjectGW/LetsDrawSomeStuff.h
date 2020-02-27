// This file can be used to contain very basic DX11 Loading, Drawing & Clean Up. (Start Here, or Make your own set of classes)
#pragma once
// Include our DX11 middle ware 
#include "../../Gateware/Interface/G_Graphics/GDirectX11Surface.h"
#include "../../Gateware/Interface/G_System/GInput.h"
#include "../../Gateware/Interface/G_System/GWindow.h"

// Other possible Gateware libraries:
// GMatrix, GAudio, GController, GInput, GLog, GFile... +more
// While these libraries won't directly add any points to your project they can be used to make them more "gamelike"
// To add a library just include the relevant "Interface" & add any related *.cpp files from the "Source" folder to the Gateware filter->.
// Gateware comes with MSDN style docs too: "Gateware\Documentation\html\index.html"

// Include DirectX11 for interface access
#include <d3d11.h>
#include <atlbase.h>

#include "DDSTextureLoader.h"
#include "Importer.h"
#include "XTime.h"
#include "Camera.h"
#include <ctime>

// Shaders
#include "PShader.csh"
#include "VShader.csh"
#include "MeshVShader.csh"
#include "TexPShader.csh"
#include "SkyVShader.csh"
#include "SkyPShader.csh"
#include "GeoVShader.csh"
#include "GShader.csh"
#include "InstVShader.csh"
#include "GeoPShader.csh"
#include "WavePShader.csh"
#include "WaveVShader.csh"

// Math lib
#include "mymath.h"  //mine
#include <DirectXMath.h>  // Directs  (gateware also has its own)
#include "../../Gateware/Interface/G_Math/GMathDefines.h"
#include "../../Gateware/Interface/G_Math/GMatrix.h"

// Pre-made mesh
#include "Assets/StoneHenge.h"
#include "Assets/StoneHenge_Texture.h"

using namespace DirectX;

#define SAFE_RELEASE(ptr) { if(ptr) { ptr->Release(); ptr = nullptr; } }
#define WHITE {1.0f, 1.0f, 1.0f, 1.0f }

// Simple Container class to make life easier/cleaner
class LetsDrawSomeStuff
{
	// variables here
	GW::GRAPHICS::GDirectX11Surface* mySurface = nullptr;
	GW::SYSTEM::GInput* input;
	// Gettting these handles from GDirectX11Surface will increase their internal refrence counts, be sure to "Release()" them when done!
	ID3D11Device *myDevice = nullptr;
	IDXGISwapChain *mySwapChain = nullptr;
	ID3D11DeviceContext *myContext = nullptr;

	// TODO: Add your own D3D11 variables here (be sure to "Release()" them when done!)
	// buffer to store vertices
	// input layout
	// vertex/pixel sharders
	unsigned int numVerts = 0;
	float aspectRatio = 1; // built in somewhere?
	const wchar_t* fname;

	CComPtr<ID3D11Buffer> vBuff; // vertex buffer
	CComPtr<ID3D11InputLayout> vLayout;  // what vertex data looks like
	CComPtr<ID3D11VertexShader> vShader; // HLSL
	CComPtr<ID3D11PixelShader> pShader; // HLSL

	CComPtr<ID3D11Buffer> cBuff; // shader vars

	// mesh data
	CComPtr<ID3D11Buffer> vBuffMesh; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMesh; // index buffer

	// mesh vertex shader 
	CComPtr < ID3D11VertexShader> vMeshShader; // HLSL
	CComPtr < ID3D11InputLayout> vMeshLayout;  // what vertex data looks like

	// Texture
	CComPtr < ID3D11PixelShader> texPShader; // HLSL
	CComPtr < ID3D11SamplerState> samplerState;
	CComPtr < ID3D11ShaderResourceView> textureRV = nullptr;
	CComPtr<ID3D11ShaderResourceView> textureRV2;

	// Floor
		// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshFloor; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshFloor; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderFloor; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutFloor;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVFloor;

	// Ship
		// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshShip; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshShip; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderShip; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutShip;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVShip;

	// Earth
	// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshEarth; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshEarth; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderEarth; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutEarth;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVEarth;

	// Venus
// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshVenus; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshVenus; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderVenus; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutVenus;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVVenus;

	// Mars
// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshMars; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshMars; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderMars; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutMars;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVMars;

	// Earth Moon
// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshEM; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshEM; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderEM; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutEM;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVEM;

	// SUN
// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshSun; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshSun; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderSun; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutSun;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVSun;

	// SkyBox
	// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshSky; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshSky; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderSky; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutSky;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVSky;
	// Pixel
	CComPtr < ID3D11PixelShader> skyPShader; // HLSL

	// Moon
	// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshMoon; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshMoon; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderMoon; // HLSL
	CComPtr<ID3D11VertexShader> vMeshShaderMoonInst; // HLSL for use with instancing

	CComPtr<ID3D11InputLayout> vMeshLayoutMoon;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVMoon;


	// Geometry
// mesh data
	CComPtr<ID3D11Buffer> vBuffGeo; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffGeo; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vShaderGeo; // HLSL
	CComPtr<ID3D11InputLayout> vLayoutGeo;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVGeo;
	// Geo
	CComPtr<ID3D11GeometryShader> gShader;
	// Constant buffer
	CComPtr<ID3D11Buffer> cBuffGeo;
	// Pixel
	CComPtr < ID3D11PixelShader> geoPShader; // HLSL


	CComPtr<ID3D11RasterizerState> rastStateCullOn;
	CComPtr<ID3D11RasterizerState> rastStateCullOff;

	// Lighting
	CComPtr<ID3D11Buffer> cBuffLight;

	// Waveing variables
	CComPtr<ID3D11VertexShader> vWaveShader; // HLSL
	CComPtr<ID3D11PixelShader> pWaveShader; // HLSL

	//Scene 2 Holy Grail
		// SkyBox
	// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshSky2; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshSky2; // index buffer
	CComPtr<ID3D11InputLayout> vMeshLayoutSky2;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVSky2;

	// Floor
		// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshFloorHG; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshFloorHG; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderFloorHG; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutFloorHG;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVFloorHG;

	// Rabbit
	// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshBunny; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshBunny; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderBunny; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutBunny;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVBunny;

	// Knight
	// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshKnight; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshKnight; // index buffer
	// mesh vertex shader 
	CComPtr<ID3D11VertexShader> vMeshShaderKnight; // HLSL
	CComPtr<ID3D11InputLayout> vMeshLayoutKnight;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVKnight;

	// Grail
// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshGrail; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshGrail; // index buffer
	CComPtr<ID3D11InputLayout> vMeshLayoutGrail;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVGrail;

	// Crow
// mesh data
	CComPtr<ID3D11Buffer> vBuffMeshCrow; // vertex buffer
	CComPtr<ID3D11Buffer> iBuffMeshCrow; // index buffer
	CComPtr<ID3D11InputLayout> vMeshLayoutCrow;  // what vertex data looks like
	// Texture
	CComPtr<ID3D11ShaderResourceView> textureRVCrow;


	// Math stuff
	struct Shader_Vars
	{
		XMFLOAT4X4 wMatrix; //storage type
		XMFLOAT4X4 vMatrix;
		XMFLOAT4X4 pMatrix;
		//XMFLOAT4 cameraPos;
	}MyShaderVars;

	struct ConstantLights
	{
		// Light
		XMFLOAT4 vLightDir[3];
		XMFLOAT4 vLightColor[3];
		XMFLOAT4 vLightPos[3];
		XMFLOAT4 vRadius;
		XMFLOAT4 specularColor;
		XMFLOAT4 specularPower;
		XMFLOAT3 cameraPos;
		float buffer;
	};

	float outState = 0.0f;

	// Camera
	Camera cam;
	Camera cam2;

	float camSpeed = 0.006f;
	double delta = 0.0f;
	double speed = 50.f;
	
	// Importer
	FbxScene* scene;
	SimpleMesh shipMesh;

	vector<SimpleMesh> meshs;

	// Instancing
	struct InstanceType
	{
		XMFLOAT3 instancePos;
	};

	CComPtr<ID3D11Buffer> instanceBuffer;

	int mInstanceCount;
	int mVertexCount;

	// Mini-map viewport
	D3D11_VIEWPORT viewPort;
	D3D11_VIEWPORT viewPort2;

	unsigned int vpWidth;
	unsigned int vpHeight;
	unsigned int vpTopLeftX;
	unsigned int vpTopLeftY;

	float fovDegrees = 90.f;
	//float cam1Fov = 3.14f / 2.0f;
	float cam1Fov = (fovDegrees/360.f)* 3.14f;

	float nearZ = 0.1f;
	float farZ = 1000.f;


	// Timer
	// Timer init
	XTime xtimer;

	std::clock_t start;
	float duration;

public:
	// Init
	LetsDrawSomeStuff(GW::SYSTEM::GWindow* attatchPoint);
	// Shutdown
	~LetsDrawSomeStuff();
	// Draw
	void Render();
	void UpdateCamera();
};

// Init
LetsDrawSomeStuff::LetsDrawSomeStuff(GW::SYSTEM::GWindow* attatchPoint)
{
	if (attatchPoint) // valid window?
	{

		// Create surface, will auto attatch to GWindow
		if (G_SUCCESS(GW::GRAPHICS::CreateGDirectX11Surface(attatchPoint, GW::GRAPHICS::DEPTH_BUFFER_SUPPORT, &mySurface)))
		{
			// Grab handles to all DX11 base interfaces
			mySurface->GetDevice((void**)&myDevice);
			mySurface->GetSwapchain((void**)&mySwapChain);
			mySurface->GetContext((void**)&myContext);


			// TODO: Create new DirectX stuff here! (Buffers, Shaders, Layouts, Views, Textures, etc...)
			// Get aspect ratio using Gateware
			mySurface->GetAspectRatio(aspectRatio);


			HWND hwnd;
			attatchPoint->GetWindowHandle(sizeof(HWND), (void**)&hwnd);
			CreateGInput(hwnd, sizeof(HWND), &input);

			attatchPoint->GetWidth(vpWidth);
			attatchPoint->GetHeight(vpHeight);
			attatchPoint->GetClientTopLeft(vpTopLeftX, vpTopLeftY);
			
			// Rasterizer states
			D3D11_RASTERIZER_DESC rastDesc = {};
			rastDesc.CullMode = D3D11_CULL_NONE;
			rastDesc.FillMode = D3D11_FILL_SOLID;

			myDevice->CreateRasterizerState(&rastDesc, &rastStateCullOff.p);

			D3D11_RASTERIZER_DESC rastDescBack = {};
			rastDescBack.CullMode = D3D11_CULL_BACK;
			rastDescBack.FillMode = D3D11_FILL_SOLID;

			myDevice->CreateRasterizerState(&rastDescBack, &rastStateCullOn.p);

			HRESULT hr;

			// Load it on the card
			D3D11_BUFFER_DESC bDesc, instancebDesc;
			D3D11_SUBRESOURCE_DATA subData, instanceData;
			InstanceType* instances;

#pragma region "Triangle"
			VERTEX_3D tri[] = 
			{
				// xyzw, rgba
				// front
				{{ 0.0f,   1.0f,   0.0f,  1.f }, {1.f, 1.f, 1.f, 1.f}},
				{{ 0.25f, -0.25f, -0.25f, 1.f }, {1.f, 0.f, 1.f, 1.f}},
				{{-0.25f, -0.25f, -0.25f, 1.f }, {1.f, 1.f, 0.f, 1.f}},
				// right
				{{ 0.0f,   1.0f,   0.0f,  1.f }, {1.f, 1.f, 1.f, 1.f}},
				{{ 0.25f, -0.25f,  0.25f, 1.f }, {1.f, 0.f, 1.f, 1.f}},
				{{ 0.25f, -0.25f, -0.25f, 1.f }, {1.f, 1.f, 0.f, 1.f}},
				// back 
				{{ 0.0f,   1.0f,  0.0f,  1.f }, {1.f, 1.f, 1.f, 1.f}},
				{{-0.25f, -0.25f, 0.25f, 1.f }, {1.f, 0.f, 1.f, 1.f}},
				{{ 0.25f, -0.25f, 0.25f, 1.f }, {1.f, 1.f, 0.f, 1.f}},
				// left
				{{ 0.0f,   1.0f,   0.0f, 1.f }, {1.f, 1.f, 1.f, 1.f}},
				{{-0.25f, -0.25f,-0.25f, 1.f }, {1.f, 0.f, 1.f, 1.f}},
				{{-0.25f, -0.25f, 0.25f, 1.f }, {1.f, 1.f, 0.f, 1.f}}

			};

			numVerts = ARRAYSIZE(tri);

			ZeroMemory(&bDesc, sizeof(bDesc));
			ZeroMemory(&subData, sizeof(subData));

			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(VERTEX_3D) * numVerts; //get how many elements in array (verts)
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = tri;

			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuff);

			// Input Layout
			// describe the vertex to D3D11
			D3D11_INPUT_ELEMENT_DESC ieDesc[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(ieDesc, 2, VShader, sizeof(VShader), &vLayout);
#pragma endregion

#pragma region "Constant Buffer"
			// Create Constant Buffer
			ZeroMemory(&bDesc, sizeof(bDesc));
			ZeroMemory(&subData, sizeof(subData));

			bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bDesc.ByteWidth = sizeof(Shader_Vars); //get how many elements in array (verts)
			bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_DYNAMIC;
			
			//subData.pSysMem = 0;

			hr = myDevice->CreateBuffer(&bDesc, nullptr, &cBuff);
#pragma endregion

#pragma region "Shader Compile&Load"
			// write and compile  & load our shaders
			hr = myDevice->CreateVertexShader(VShader, sizeof(VShader), nullptr, &vShader);
			hr = myDevice->CreatePixelShader(PShader, sizeof(PShader), nullptr, &pShader);
			hr = myDevice->CreatePixelShader(TexPShader, sizeof(TexPShader), nullptr, &texPShader);
			hr = myDevice->CreatePixelShader(SkyPShader, sizeof(SkyPShader), nullptr, &skyPShader);
			hr = myDevice->CreatePixelShader(GeoPShader, sizeof(GeoPShader), nullptr, &geoPShader);
			// Load our new mesh shader
			hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderFloor);
			hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderMoon);
			hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderBunny);
			hr = myDevice->CreateVertexShader(InstVShader, sizeof(InstVShader), nullptr, &vMeshShaderMoonInst);

			// Geo shader
			hr = myDevice->CreateVertexShader(GeoVShader, sizeof(GeoVShader), nullptr, &vShaderGeo);
			hr = myDevice->CreateGeometryShader(GShader, sizeof(GShader), nullptr, &gShader);

			// Wave Shader
			hr = myDevice->CreateVertexShader(WaveVShader, sizeof(WaveVShader), nullptr, &vWaveShader);
			hr = myDevice->CreatePixelShader(WavePShader, sizeof(WavePShader), nullptr, &pWaveShader);

#pragma endregion
		
#pragma region "Sample State"
			// Create the sample state
			D3D11_SAMPLER_DESC sampleDesc = {};
			sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampleDesc.MinLOD = 0;
			sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;

			hr = myDevice->CreateSamplerState(&sampleDesc, &samplerState);
#pragma endregion

#pragma region "Model Loading"
			// 0 - Floor, 1- Ship, 2- Moon 3- Sky
			// Floor
			scene = ImporterFbx("Assets/sci_fi_floor.fbx"); 
			meshs.push_back(ProcessFbxMesh(scene));
			// Ship
			scene = ImporterFbx("Assets/talon.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Moon
			scene = ImporterFbx("Assets/moon.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Sky
			scene = ImporterFbx("Assets/SkyBox.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Earth
			scene = ImporterFbx("Assets/Earth.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Venus
			scene = ImporterFbx("Assets/planet.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Mars
			scene = ImporterFbx("Assets/planet.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Earth Moon
			scene = ImporterFbx("Assets/moon.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Holy Grail Floor // 8
			scene = ImporterFbx("Assets/hg_floor.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Sun
			scene = ImporterFbx("Assets/planet.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Bunny
			scene = ImporterFbx("Assets/Bunny.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Knight
			scene = ImporterFbx("Assets/knight.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// Sky Sun
			scene = ImporterFbx("Assets/SkyBox.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// HG Holy Grail // 13
			scene = ImporterFbx("Assets/Grail.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
			// HG Crow // 14
			scene = ImporterFbx("Assets/Crow2.fbx");
			meshs.push_back(ProcessFbxMesh(scene));
#pragma endregion

#pragma region "Floor Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[0].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[0].vertexList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshFloor); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[0].indicesList.size();
			subData.pSysMem = meshs[0].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshFloor);


			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescFloor[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescFloor, 3, MeshVShader, sizeof(MeshVShader), &vMeshLayoutFloor);


			// Load the texture 
			fname = L"Assets/sci_floor_diffuse.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVFloor);
#pragma endregion

#pragma region "Ship Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[1].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[1].vertexList.data();

			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshShip); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[1].indicesList.size();
			subData.pSysMem = meshs[1].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshShip);

			// Load our new mesh shader
			hr = myDevice->CreateVertexShader(WaveVShader, sizeof(WaveVShader), nullptr, &vMeshShaderShip);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescShip[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescShip, ARRAYSIZE(meshInputDescShip), WaveVShader, sizeof(WaveVShader), &vMeshLayoutShip);


			// Load the texture 
			fname = L"Assets/talon.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVShip);
#pragma endregion

#pragma region "Moon Init"
			// Moon
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[2].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[2].vertexList.data();

			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshMoon); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[2].indicesList.size();
			subData.pSysMem = meshs[2].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshMoon);

			//
			// Instancing
			//
			// Number of Instances in the array
			mInstanceCount = 4;
			// Create the instance array
			instances = new InstanceType[mInstanceCount];
			instances[0].instancePos = XMFLOAT3(-0.9f, 0.3f, 0.0f);
			instances[1].instancePos = XMFLOAT3(-0.9f, 0.3f, 0.4f);
			instances[2].instancePos = XMFLOAT3(-0.9f, 0.3f, -0.4f);
			instances[3].instancePos = XMFLOAT3(-0.9f, 0.3f, 0.8f);
			// Setup the instance buffer desc
			instancebDesc.Usage = D3D11_USAGE_DEFAULT;
			instancebDesc.ByteWidth = sizeof(InstanceType) * mInstanceCount;
			instancebDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			instancebDesc.CPUAccessFlags = 0;
			instancebDesc.MiscFlags = 0;
			instancebDesc.StructureByteStride = 0;
			// Give subresource structure a pointer to instance data
			instanceData.pSysMem = instances;
			instanceData.SysMemPitch = 0;
			instanceData.SysMemSlicePitch = 0;
			// Create the instance buffer
			hr = myDevice->CreateBuffer(&instancebDesc, &instanceData, &instanceBuffer);

			// Release instance array
			delete[] instances;
			instances = 0;

			
			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescMoon[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				// Instance position 
				{"POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			};
			//hr = myDevice->CreateInputLayout(meshInputDescMoon, ARRAYSIZE(meshInputDescMoon), MeshVShader, sizeof(MeshVShader), &vMeshLayoutMoon);
			hr = myDevice->CreateInputLayout(meshInputDescMoon, ARRAYSIZE(meshInputDescMoon), InstVShader, sizeof(InstVShader), &vMeshLayoutMoon);


			// Load the texture 
			fname = L"Assets/moon_Diffuse.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVMoon);
#pragma endregion

#pragma region "Sky Init Space"
			// Sky
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[3].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[3].vertexList.data();

			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshSky); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[3].indicesList.size();
			subData.pSysMem = meshs[3].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshSky);

			// Load our new mesh shader
			hr = myDevice->CreateVertexShader(SkyVShader, sizeof(SkyVShader), nullptr, &vMeshShaderSky);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescSky[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescSky, ARRAYSIZE(meshInputDescSky), SkyVShader, sizeof(SkyVShader), &vMeshLayoutSky);


			// Load the texture 
			fname = L"Assets/SpaceSkybox.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVSky);
#pragma endregion

#pragma region "Sky Init Sunset"
			// Sky
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[12].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[12].vertexList.data();

			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshSky2); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[12].indicesList.size();
			subData.pSysMem = meshs[12].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshSky2);

			//// Load our new mesh shader
			//hr = myDevice->CreateVertexShader(SkyVShader, sizeof(SkyVShader), nullptr, &vMeshShaderSky);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescSky2[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescSky2, ARRAYSIZE(meshInputDescSky2), SkyVShader, sizeof(SkyVShader), &vMeshLayoutSky2);


			// Load the texture 
			fname = L"Assets/SunsetSkybox.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVSky2);
#pragma endregion

#pragma region "Stonehenge Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(StoneHenge_data);
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = StoneHenge_data;
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMesh); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(StoneHenge_indicies);
			subData.pSysMem = StoneHenge_indicies;
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMesh);

			// Load our new mesh shader
			hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShader);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDesc[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDesc, 3, MeshVShader, sizeof(MeshVShader), &vMeshLayout);



			// Load the texture 
			const wchar_t* fname = L"Assets/StoneHenge.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRV);

#pragma endregion

#pragma region "Earth Init"
						// Load our complex mesh onto the card
						bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
						bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[4].vertexList.size();
						bDesc.CPUAccessFlags = 0;
						bDesc.MiscFlags = 0;
						bDesc.StructureByteStride = 0;
						bDesc.Usage = D3D11_USAGE_IMMUTABLE;
			
						subData.pSysMem = meshs[4].vertexList.data();
			
						hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshEarth); // vertex buffer
			
						// index buffer mesh
						bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
						bDesc.ByteWidth = sizeof(int) * meshs[4].indicesList.size();
						subData.pSysMem = meshs[4].indicesList.data();
						hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshEarth);
			
						// Load our new mesh shader
						hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderEarth);
			
						// Make matching input layout for mesh vertex
						D3D11_INPUT_ELEMENT_DESC meshInputDescEarth[] =
						{
							{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
							{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
							{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						hr = myDevice->CreateInputLayout(meshInputDescEarth, ARRAYSIZE(meshInputDescEarth), MeshVShader, sizeof(MeshVShader), &vMeshLayoutEarth);
			
			
						// Load the texture 
						fname = L"Assets/earth_texture.dds";
						hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVEarth);
#pragma endregion

#pragma region "Venus Init"
						// Load our complex mesh onto the card
						bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
						bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[5].vertexList.size();
						bDesc.CPUAccessFlags = 0;
						bDesc.MiscFlags = 0;
						bDesc.StructureByteStride = 0;
						bDesc.Usage = D3D11_USAGE_IMMUTABLE;

						subData.pSysMem = meshs[5].vertexList.data();

						hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshVenus); // vertex buffer

						// index buffer mesh
						bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
						bDesc.ByteWidth = sizeof(int) * meshs[5].indicesList.size();
						subData.pSysMem = meshs[5].indicesList.data();
						hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshVenus);

						// Load our new mesh shader
						hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderVenus);

						// Make matching input layout for mesh vertex
						D3D11_INPUT_ELEMENT_DESC meshInputDescVenus[] =
						{
							{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
							{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
							{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						hr = myDevice->CreateInputLayout(meshInputDescVenus, ARRAYSIZE(meshInputDescVenus), MeshVShader, sizeof(MeshVShader), &vMeshLayoutVenus);


						// Load the texture 
						fname = L"Assets/venus_texture.dds";
						hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVVenus);
#pragma endregion

#pragma region "Mars Init"
						// Load our complex mesh onto the card
						bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
						bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[6].vertexList.size();
						bDesc.CPUAccessFlags = 0;
						bDesc.MiscFlags = 0;
						bDesc.StructureByteStride = 0;
						bDesc.Usage = D3D11_USAGE_IMMUTABLE;

						subData.pSysMem = meshs[6].vertexList.data();

						hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshMars); // vertex buffer

						// index buffer mesh
						bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
						bDesc.ByteWidth = sizeof(int) * meshs[6].indicesList.size();
						subData.pSysMem = meshs[6].indicesList.data();
						hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshMars);

						// Load our new mesh shader
						hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderMars);

						// Make matching input layout for mesh vertex
						D3D11_INPUT_ELEMENT_DESC meshInputDescMars[] =
						{
							{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
							{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
							{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						hr = myDevice->CreateInputLayout(meshInputDescMars, ARRAYSIZE(meshInputDescMars), MeshVShader, sizeof(MeshVShader), &vMeshLayoutMars);


						// Load the texture 
						fname = L"Assets/mars_texture.dds";
						hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVMars);
#pragma endregion

#pragma region "Sun Init"
						// Load our complex mesh onto the card
						bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
						bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[9].vertexList.size();
						bDesc.CPUAccessFlags = 0;
						bDesc.MiscFlags = 0;
						bDesc.StructureByteStride = 0;
						bDesc.Usage = D3D11_USAGE_IMMUTABLE;

						subData.pSysMem = meshs[9].vertexList.data();

						hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshSun); // vertex buffer

						// index buffer mesh
						bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
						bDesc.ByteWidth = sizeof(int) * meshs[9].indicesList.size();
						subData.pSysMem = meshs[9].indicesList.data();
						hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshSun);

						// Load our new mesh shader
						hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderSun);

						// Make matching input layout for mesh vertex
						D3D11_INPUT_ELEMENT_DESC meshInputDescSun[] =
						{
							{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
							{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
							{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						hr = myDevice->CreateInputLayout(meshInputDescSun, ARRAYSIZE(meshInputDescSun), MeshVShader, sizeof(MeshVShader), &vMeshLayoutSun);


						// Load the texture 
						fname = L"Assets/sun_texture.dds";
						hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVSun);
#pragma endregion

#pragma region "Earth Moon Init"
						// Load our complex mesh onto the card
						bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
						bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[7].vertexList.size();
						bDesc.CPUAccessFlags = 0;
						bDesc.MiscFlags = 0;
						bDesc.StructureByteStride = 0;
						bDesc.Usage = D3D11_USAGE_IMMUTABLE;

						subData.pSysMem = meshs[7].vertexList.data();

						hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshEM); // vertex buffer

						// index buffer mesh
						bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
						bDesc.ByteWidth = sizeof(int) * meshs[7].indicesList.size();
						subData.pSysMem = meshs[7].indicesList.data();
						hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshEM);

						// Load our new mesh shader
						hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderEM);

						// Make matching input layout for mesh vertex
						D3D11_INPUT_ELEMENT_DESC meshInputDescEM[] =
						{
							{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
							{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
							{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						hr = myDevice->CreateInputLayout(meshInputDescEM, ARRAYSIZE(meshInputDescEM), MeshVShader, sizeof(MeshVShader), &vMeshLayoutEM);


						// Load the texture 
						fname = L"Assets/moon_texture.dds";
						hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVEM);
#pragma endregion

#pragma region "Geometry Shader Triangle Init"
			VERTEX_3D vert[] = {{ 0.0f,   2.75f,   -15.0f,  1.f }, {1.f, 1.f, 1.f, 1.f}};
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(VERTEX_3D) ; //get how many elements in array (verts)
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;
			
			subData.pSysMem = vert;
			
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffGeo);
			
			// Input Layout
			// describe the vertex to D3D11
			D3D11_INPUT_ELEMENT_DESC geoDesc[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(geoDesc, ARRAYSIZE(geoDesc), GeoVShader, sizeof(GeoVShader), &vLayoutGeo);
#pragma endregion

#pragma region "HG Floor Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[8].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[8].vertexList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshFloorHG); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[8].indicesList.size();
			subData.pSysMem = meshs[8].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshFloorHG);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescFloorHG[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescFloorHG, ARRAYSIZE(meshInputDescFloorHG), MeshVShader, sizeof(MeshVShader), &vMeshLayoutFloorHG);

			// Load the texture 
			fname = L"Assets/hg_floor_og.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVFloorHG);
#pragma endregion

#pragma region "HG Bunny Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[10].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[10].vertexList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshBunny); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[10].indicesList.size();
			subData.pSysMem = meshs[10].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshBunny);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescBunny[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescBunny, ARRAYSIZE(meshInputDescBunny), MeshVShader, sizeof(MeshVShader), &vMeshLayoutBunny);

			// Load the texture 
			fname = L"Assets/bunny_texture.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVBunny);
#pragma endregion

#pragma region "HG Knight Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[11].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[11].vertexList.data();

			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshKnight); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[11].indicesList.size();
			subData.pSysMem = meshs[11].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshKnight);


			// Load our new mesh shader
			hr = myDevice->CreateVertexShader(MeshVShader, sizeof(MeshVShader), nullptr, &vMeshShaderKnight);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescKnight[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,   D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescKnight, ARRAYSIZE(meshInputDescKnight), MeshVShader, sizeof(MeshVShader), &vMeshLayoutKnight);


			// Load the texture 
			fname = L"Assets/gold_texture.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVKnight);
#pragma endregion

#pragma region "HG Grail Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[13].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[13].vertexList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshGrail); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[13].indicesList.size();
			subData.pSysMem = meshs[13].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshGrail);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescGrail[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescGrail, ARRAYSIZE(meshInputDescGrail), MeshVShader, sizeof(MeshVShader), &vMeshLayoutGrail);

			// Load the texture 
			fname = L"Assets/grail_texture.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVGrail);
#pragma endregion

#pragma region "HG Crow Init"
			// Load our complex mesh onto the card
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(SimpleVertex) * meshs[14].vertexList.size();
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_IMMUTABLE;

			subData.pSysMem = meshs[14].vertexList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &vBuffMeshCrow); // vertex buffer

			// index buffer mesh
			bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bDesc.ByteWidth = sizeof(int) * meshs[14].indicesList.size();
			subData.pSysMem = meshs[14].indicesList.data();
			hr = myDevice->CreateBuffer(&bDesc, &subData, &iBuffMeshCrow);

			// Make matching input layout for mesh vertex
			D3D11_INPUT_ELEMENT_DESC meshInputDescCrow[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },    // APPEND_ALIGNED_ELEMENT will automatically calculate the byte offset
				{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			hr = myDevice->CreateInputLayout(meshInputDescCrow, ARRAYSIZE(meshInputDescCrow), MeshVShader, sizeof(MeshVShader), &vMeshLayoutCrow);

			// Load the texture 
			fname = L"Assets/crow_texture.dds";
			hr = CreateDDSTextureFromFile(myDevice, fname, nullptr, &textureRVCrow);
#pragma endregion

#pragma region "Light Init"
			// Create Constant Buffer
			bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bDesc.ByteWidth = sizeof(ConstantLights); //get how many elements in array (verts)
			bDesc.CPUAccessFlags = 0;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;
			bDesc.Usage = D3D11_USAGE_DEFAULT;

			hr = myDevice->CreateBuffer(&bDesc, nullptr, &cBuffLight);
#pragma endregion

#pragma region "Cam/View/Projection Init"
			// Set the initial Camera eye position
			cam.SetEyePos({ 4, 10, -25 });

			//XMStoreFloat4(&MyShaderVars.cameraPos, cam.GetEyePosVector());

			// Store initial view Matrix
			XMStoreFloat4x4(&MyShaderVars.vMatrix, cam.GetViewMatrix());

			// Set & Store initial projection matrix
			//cam.SetProjectionMatrix(XMMatrixPerspectiveFovLH(3.14f / 2.0f, aspectRatio/2, 0.1f, 1000));
			cam.SetProjectionMatrix(XMMatrixPerspectiveFovLH(cam1Fov, aspectRatio / 2, 0.1f, 1000));
			XMStoreFloat4x4(&MyShaderVars.pMatrix, cam.GetProjectionMatrix());
#pragma endregion

#pragma region "Cam2/View/Projection Init"
			// Set the initial Camera eye position
			cam2.SetEyePos({ -12, 80, 5});

			cam2.SetEyePosVector({ -12, 80, 5});

			cam2.RotateCamera(45.0f, 45.f);
			// Store initial view Matrix
			//cam2.SetEyeRotVector({ 0.0f, -90.0f, 0.0f, });
			XMStoreFloat4x4(&MyShaderVars.vMatrix, cam2.GetViewMatrix());

			// Set & Store initial projection matrix
			cam2.SetProjectionMatrix(XMMatrixPerspectiveFovLH(3.14f / 2.0f, aspectRatio/2, 0.1f, 1000));
			//cam2.SetProjectionMatrix(XMMatrixPerspectiveFovLH(cam1Fov, aspectRatio / 2, 0.1f, 1000));
			XMStoreFloat4x4(&MyShaderVars.pMatrix, cam2.GetProjectionMatrix());
#pragma endregion

		}
	}
}

// Shutdown
LetsDrawSomeStuff::~LetsDrawSomeStuff()
{
	// Release DX Objects aquired from the surface
	myDevice->Release();
	mySwapChain->Release();
	myContext->Release();

	// TODO: "Release()" more stuff here!
	// Used CComPtrs to auto release

	if (mySurface) // Free Gateware Interface
	{
		mySurface->DecrementCount(); // reduce internal count (will auto delete on Zero)
		mySurface = nullptr; // the safest way to fly
	}
}

// Draw
void LetsDrawSomeStuff::Render()
{
	if (mySurface) // valid?
	{
		// this could be changed during resolution edits, get it every frame
		ID3D11RenderTargetView *myRenderTargetView = nullptr;
		ID3D11DepthStencilView *myDepthStencilView = nullptr;
		if (G_SUCCESS(mySurface->GetRenderTarget((void**)&myRenderTargetView)))
		{
			// Grab the Z Buffer if one was requested
			if (G_SUCCESS(mySurface->GetDepthStencilView((void**)&myDepthStencilView)))
			{
				myContext->ClearDepthStencilView(myDepthStencilView, D3D11_CLEAR_DEPTH, 1, 0); // clear it to Z exponential Far.
				myDepthStencilView->Release();
			}	
			// Set active target for drawing, all array based D3D11 functions should use a syntax similar to below
			ID3D11RenderTargetView* const targets[] = { myRenderTargetView };
			myContext->OMSetRenderTargets(1, targets, myDepthStencilView);
	
			// Clear the screen to blue
			const float sky_blue[] = { 0.0f, 0.749f, 1.0f, 1 };

			myContext->ClearRenderTargetView(myRenderTargetView, sky_blue);
			
			// TODO: Set your shaders, Update & Set your constant buffers, Attatch your vertex & index buffers, Set your InputLayout & Topology & Draw!
					// Input Assembler
			// Timer
			xtimer.Signal();
			delta += xtimer.Delta();

			mySurface->GetAspectRatio(aspectRatio);
			

			viewPort.Width = vpWidth / 2;
			viewPort.Height = vpHeight;
			viewPort.TopLeftX = vpTopLeftX;
			viewPort.TopLeftY = vpTopLeftY;
			viewPort.MinDepth = 0;
			viewPort.MaxDepth = 1;

			
			myContext->RSSetViewports(1, &viewPort);


			// Make a world view & projection matrix
			// World
			XMMATRIX temp = XMMatrixIdentity();
#pragma region "Wave/Hover"
			// Timer
			duration = (clock() - start);
			// Venus
			static bool shift = false;
			static float wave = 860.f;
			static float jump = 0.36f;
			// Spaceship
			static bool shiftV = false;
			static float hover = 860.f;
			static float hoverJump = 0.36f;
			if ((int)duration % 1000 > 60)
			{
				// Venus
				if (!shift)
					wave += jump;
				else
					wave -= jump;
				if (wave > 1200)
					shift = true;
				else if (wave < 600)
					shift = false;

				// Spaceship
				if (!shiftV)
					hover += jump;
				else
					hover -= jump;
				if (hover > 1200)
					shiftV = true;
				else if (hover < 600)
					shiftV = false;

				start = clock();
			}
#pragma endregion

#pragma region "Lighting"

			// Setup our lighting parameters
			XMFLOAT4 vLightDirs[3] =
			{
				XMFLOAT4(-1.0f, -0.25f, 0.0f, 1.0f),  // directional  (Direction, used)
				XMFLOAT4(10.0f, 10.0f, 0.0f, 1.0f),   // Point  (Direction, not used)
				XMFLOAT4(0.577f, -0.577f, 0.0f, 1.0f),   // Spot    (Direction , used)
			};
			XMFLOAT4 vLightColors[3] =
			{
				XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), // white
				XMFLOAT4(0.0f, 1.15f, 0.f, 1.0f),   // green
				XMFLOAT4(1.0, 1.0f, 1.0f, 1.0f)    // purple
			};
			XMFLOAT4 vLightPos[3] =
			{
				XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),  // directional (none, not used)
				XMFLOAT4(10.0f, 10.0f, 0.0f, 1.0f),   // Point (Position, used)
				XMFLOAT4(-30.f, 10.0f, 0.0f, 1.0f),   // Spot (Position, used)
			};
			XMFLOAT4 vRadius =
			{
				XMFLOAT4{40.0f,   // Point Light Radius
				0.6f,   // Spot Inner Cone ratio 
				0.77f,   // Spot Outer Cone ratio
				30.0f},   // Spot Light Radius
			};

			XMFLOAT4 specularColor =
			{
				XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
			};
			XMFLOAT4 specularPower =
			{
				XMFLOAT4(1024.f,512.0f,wave,hover),
			};
			XMFLOAT3 cameraPos = { XMFLOAT3(cam.GetEyePos())};
			float buffer = 0.0f;

			// Spot Rotation
			//XMVECTOR vLightDir = XMLoadFloat4(&vLightDirs[2]);
			//vLightDir = XMVector3Transform(vLightDir, XMMatrixRotationY(delta));
			//XMStoreFloat4(&vLightDirs[2], vLightDir);


			 //Point position
			XMVECTOR vLightPosPoint = cam.GetLightPosPointVector();
			if (G_SUCCESS(input->GetState(G_KEY_1, outState)) && outState)
			{
				vLightPosPoint = cam.GetEyePosVector();
			}
			cam.SetLightPosPoint(vLightPosPoint);
			XMStoreFloat4(&vLightPos[1], vLightPosPoint);


			//Spot position
			XMVECTOR vLightPosSpot = cam.GetLightPosSpotVector();
			if (G_SUCCESS(input->GetState(G_KEY_2, outState)) && outState)
			{
				vLightPosSpot = cam.GetEyePosVector();
			}
			cam.SetLightPosSpot(vLightPosSpot);
			XMStoreFloat4(&vLightPos[2], vLightPosSpot);
			

			//// Assign to Constant buffer
			ConstantLights cBuffL;
			cBuffL.vLightDir[0] = vLightDirs[0];
			cBuffL.vLightDir[1] = vLightDirs[1];
			cBuffL.vLightDir[2] = vLightDirs[2];
			cBuffL.vLightColor[0] = vLightColors[0];
			cBuffL.vLightColor[1] = vLightColors[1];
			cBuffL.vLightColor[2] = vLightColors[2];
			cBuffL.vLightPos[0] = vLightPos[0];
			cBuffL.vLightPos[1] = vLightPos[1];
			cBuffL.vLightPos[2] = vLightPos[2];
			cBuffL.vRadius = vRadius;
			cBuffL.specularColor = specularColor;
			cBuffL.specularPower = specularPower;
			cBuffL.cameraPos = cameraPos;
			cBuffL.buffer = buffer;

			myContext->UpdateSubresource(cBuffLight.p, 0, nullptr, &cBuffL, 0, 0);
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetConstantBuffers(0, 1, &cBuffLight.p);
			myContext->VSSetConstantBuffers(1, 1, &cBuffLight.p);

#pragma endregion

			// View

#pragma region "Camera Controls"
			if (G_SUCCESS(input->GetState(G_KEY_A, outState)) && outState)
			{
				cam.MoveLeft();
			}
			if (G_SUCCESS(input->GetState(G_KEY_D, outState)) && outState)
			{
				cam.MoveRight();
			}
			if (G_SUCCESS(input->GetState(G_KEY_S, outState)) && outState)
			{
				cam.MoveBack();
			}
			if (G_SUCCESS(input->GetState(G_KEY_W, outState)) && outState) 
			{
				cam.MoveForward();
				//cam.MoveForward(camSpeed, delta);
			}
			if (G_SUCCESS(input->GetState(G_KEY_Q, outState)) && outState) // UP
			{
				cam.MoveUp();
			}
			if (G_SUCCESS(input->GetState(G_KEY_E, outState)) && outState) // DOWN
			{
				cam.MoveDown();
			}
			if (G_SUCCESS(input->GetState(G_KEY_X, outState)) && outState) // ZOOM OUT
			{
				//if (cam1Fov < 2.5)
				//{
				//	cam1Fov += 0.01;
				//}
				if (fovDegrees < 130)
				{
					fovDegrees += 0.5;
				}
			}
			if (G_SUCCESS(input->GetState(G_KEY_Z, outState)) && outState) // ZOOM IN
			{
				//if (cam1Fov > 0.75)
				//{
				//	cam1Fov -= 0.01;
				//}
				if (fovDegrees > 30)
				{
					fovDegrees -= 0.5;
				}
			}
			if (G_SUCCESS(input->GetState(G_KEY_C, outState)) && outState) // RESET FOV
			{
				//cam1Fov = 3.14 / 2.0f;
				fovDegrees = 90.f;
			}

			if (G_SUCCESS(input->GetState(G_KEY_V, outState)) && outState) // Increase NearZ
			{
				if (nearZ < farZ-0.2)
				{
					nearZ += 1.0;
				}
			}
			if (G_SUCCESS(input->GetState(G_KEY_B, outState)) && outState) // Decrease FarZ
			{
				if (farZ > nearZ+20)
				{
					farZ -= 10;
				}
			}
			if (G_SUCCESS(input->GetState(G_KEY_N, outState)) && outState) // RESET NearZ and FarZ
			{
				nearZ = 0.1f;
				farZ = 1000.f;
			}
			cam1Fov = (fovDegrees / 360.f) * 3.14f;
			cam.SetProjectionMatrix(XMMatrixPerspectiveFovLH(cam1Fov, aspectRatio / 2, nearZ, farZ));

			float x, y;
			if (G_SUCCESS(input->GetMouseDelta(x, y)))
			{
				if (G_SUCCESS(input->GetState(G_BUTTON_RIGHT, outState)) && outState)
				{
					cam.MouseRotation(y, x);
				}
			}

#pragma endregion

			// Update the View Matrix after camera movement
			cam.UpdateCamera();
			XMStoreFloat4x4(&MyShaderVars.vMatrix, cam.GetViewMatrix());

			// Projection Matrix

			temp = cam.GetProjectionMatrix();
			XMStoreFloat4x4(&MyShaderVars.pMatrix, temp);

			// Upload those matrices to the video card
			// Create and update a constant buffer (move variables from C++ to shaders)
			D3D11_MAPPED_SUBRESOURCE gpuBuffer;


			// connect contant buffer to pipeline
			ID3D11Buffer* constants[] = { cBuff };
			myContext->VSSetConstantBuffers(0, 1, constants);
			myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

#pragma region "First ViewPort (Space Them)"
			// 0 - Floor, 1- Ship, 2- Moon 3- Sky

#pragma region "Draw Sky"
			// set pipeline
			UINT sky_strides[] = { sizeof(SimpleVertex) };
			UINT sky_offsets[] = { 0 };
			ID3D11Buffer* meshVB4[] = { vBuffMeshSky };
			myContext->IASetVertexBuffers(0, 1, meshVB4, sky_strides, sky_offsets);
			myContext->IASetIndexBuffer(iBuffMeshSky, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderSky, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutSky);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(skyPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVSky.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			//temp = XMMatrixTranslation(XMVectorGetX(eyePosVector), XMVectorGetY(eyePosVector), XMVectorGetZ(eyePosVector));
			temp = XMMatrixTranslation(XMVectorGetX(cam.GetEyePosVector()), XMVectorGetY(cam.GetEyePosVector()), XMVectorGetZ(cam.GetEyePosVector()));

			//temp = XMMatrixMultiply(XMMatrixScaling(1000.f, 1000.f, 1000.f), temp);

			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			HRESULT hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->RSSetState(rastStateCullOff);

			myContext->DrawIndexed(meshs[3].indicesList.size(), 0, 0); //num indices from SkyBox

			myContext->ClearDepthStencilView(myDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

			myContext->RSSetState(rastStateCullOn);
#pragma endregion

#pragma region "Pyramid"

			myContext->IASetInputLayout(vLayout);

			UINT strides[] = { sizeof(VERTEX_3D) };
			UINT offsets[] = { 0 };
			ID3D11Buffer* tempVB[] = { vBuff };
			myContext->IASetVertexBuffers(0, 1, tempVB, strides, offsets);
			// Vertex Shader Stage
			myContext->VSSetShader(vShader, 0, 0);
			// Pixel Shader Stage
			myContext->PSSetShader(pShader, 0, 0);

			static float rot = 0; rot += 0.1f; // will want to use timer here in future
			temp = XMMatrixIdentity();
			temp = XMMatrixTranslation(0, 5, -2);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);

			XMMATRIX temp2 = XMMatrixRotationY(rot);
			//XMMATRIX temp2 = XMMatrixRotationY(speed*delta);

			temp = XMMatrixMultiply(temp2, temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);

			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw LAST
			myContext->Draw(numVerts, 0);

#pragma endregion

#pragma region "Draw Floor"
			// Draw Floor
						// set pipeline
			UINT floor_strides[] = { sizeof(SimpleVertex) };
			UINT floor_offsets[] = { 0 };
			ID3D11Buffer* meshVB2[] = { vBuffMeshFloor };
			myContext->IASetVertexBuffers(0, 1, meshVB2, floor_strides, floor_offsets);
			myContext->IASetIndexBuffer(iBuffMeshFloor, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutFloor);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVFloor.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(100.f, 100.f, 100.f), temp);
			temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[0].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw Ship"
// Draw Floor
			// set pipeline
			UINT ship_strides[] = { sizeof(SimpleVertex) };
			UINT ship_offsets[] = { 0 };
			ID3D11Buffer* meshVB3[] = { vBuffMeshShip };
			myContext->IASetVertexBuffers(0, 1, meshVB3, ship_strides, ship_offsets);
			myContext->IASetIndexBuffer(iBuffMeshShip, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vWaveShader, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutShip);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVShip.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			//temp = XMMatrixMultiply(XMMatrixScaling(1, 1, 1), temp);
			temp = XMMatrixMultiply(XMMatrixScaling(250.f, 250.f, 250.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(0.f, 0.1f, 0.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[1].indicesList.size(), 0,0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw Earth"
// Draw Floor
			// set pipeline
			UINT earth_strides[] = { sizeof(SimpleVertex) };
			UINT earth_offsets[] = { 0 };
			ID3D11Buffer* meshVBEarth[] = { vBuffMeshEarth };
			myContext->IASetVertexBuffers(0, 1, meshVBEarth, earth_strides, earth_offsets);
			myContext->IASetIndexBuffer(iBuffMeshEarth, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderEarth, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutEarth);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVEarth.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();

			static float prot = 0; prot += 0.01f; // will want to use timer here in future
			XMMATRIX matRot = XMMatrixRotationY(prot);
			XMMATRIX matTrans = XMMatrixTranslation(-5.0f, 5.0f, -57.5f);
			XMMATRIX earth = XMMatrixMultiply(matTrans, matRot);

			temp = XMMatrixMultiply(XMMatrixScaling(105.f, 105.f, 105.f), earth);
			//temp = XMMatrixMultiply(XMMatrixTranslation(-0.5f, 0.1f, 0.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[4].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw Venus"
// Draw Floor
			// set pipeline
			UINT venus_strides[] = { sizeof(SimpleVertex) };
			UINT venus_offsets[] = { 0 };
			ID3D11Buffer* meshVBVenus[] = { vBuffMeshVenus };
			myContext->IASetVertexBuffers(0, 1, meshVBVenus, venus_strides, venus_offsets);
			myContext->IASetIndexBuffer(iBuffMeshVenus, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vWaveShader, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutVenus);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(pWaveShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVVenus.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();

			matRot = XMMatrixRotationY(prot);
			matTrans = XMMatrixTranslation(-20.0f, 7.5f, -40.5f);
			temp = XMMatrixMultiply(matTrans, matRot);

			temp = XMMatrixMultiply(XMMatrixScaling(15.f, 15.f, 15.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(150.f, 150.f, 150.f), temp);
			//temp = XMMatrixMultiply(XMMatrixTranslation(-0.5f, 0.1f, 0.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[5].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw Mars"
// Draw Floor
			// set pipeline
			UINT mars_strides[] = { sizeof(SimpleVertex) };
			UINT mars_offsets[] = { 0 };
			ID3D11Buffer* meshVBMars[] = { vBuffMeshMars };
			myContext->IASetVertexBuffers(0, 1, meshVBMars, mars_strides, mars_offsets);
			myContext->IASetIndexBuffer(iBuffMeshMars, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderMars, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutMars);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVMars.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();

			matRot = XMMatrixRotationY(prot);
			matTrans = XMMatrixTranslation(-35.0f, 7.5f, -70.5f);
			temp = XMMatrixMultiply(matTrans, matRot);

			temp = XMMatrixMultiply(XMMatrixScaling(15.f, 15.f, 15.f), temp);
			//temp = XMMatrixMultiply(XMMatrixTranslation(-0.5f, 0.1f, 0.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[6].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw Earth Moon"
			// Draw Mars
						// set pipeline
			UINT em_strides[] = { sizeof(SimpleVertex) };
			UINT em_offsets[] = { 0 };
			ID3D11Buffer* meshVBEM[] = { vBuffMeshEM };
			myContext->IASetVertexBuffers(0, 1, meshVBEM, em_strides, em_offsets);
			myContext->IASetIndexBuffer(iBuffMeshEM, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderEM, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutEM);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVEM.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			matTrans = XMMatrixMultiply(XMMatrixTranslation(-5.0f, 5.0f, -7.5f), matRot);
			temp = XMMatrixMultiply(matTrans, earth);
			temp = XMMatrixMultiply(XMMatrixScaling(15.f, 15.f, 15.f), temp);

			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[7].indicesList.size(), 0, 0);
#pragma endregion

#pragma region "Draw Moon"
// Draw Floor
			// set pipeline
			// Instance buffer is a second vertex buffer with diff info so we send a second a second second array
			UINT moon_strides[2] = { sizeof(SimpleVertex), sizeof(InstanceType) };
			UINT moon_offsets[2] = { 0, 0 };
			ID3D11Buffer* meshVBMoon[2] = { vBuffMeshMoon, instanceBuffer };
			myContext->IASetVertexBuffers(0, 2, meshVBMoon, moon_strides, moon_offsets); // 2 buffers
			myContext->IASetIndexBuffer(iBuffMeshMoon, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderMoonInst, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutMoon);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVMoon.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			//temp = XMMatrixMultiply(XMMatrixScaling(1, 1, 1), temp);
			temp = XMMatrixMultiply(XMMatrixScaling(15.f, 15.f, 15.f), temp);
			//temp = XMMatrixMultiply(XMMatrixTranslation(-0.9f, 0.3f, 0.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			//myContext->DrawInstanced(meshs[2].vertexList.size(), mInstanceCount, 0, 0); //num indices from stonehinge
			myContext->DrawIndexedInstanced(meshs[2].indicesList.size(), mInstanceCount, 0, 0, 0); //num indices from stonehinge

#pragma endregion

#pragma region "Draw Sun"
// Draw Floor
			// set pipeline
			UINT sun_strides[] = { sizeof(SimpleVertex) };
			UINT sun_offsets[] = { 0 };
			ID3D11Buffer* meshVBSun[] = { vBuffMeshMars };
			myContext->IASetVertexBuffers(0, 1, meshVBSun, sun_strides, sun_offsets);
			myContext->IASetIndexBuffer(iBuffMeshSun, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderMoon, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutSun);


			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(pWaveShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVSun.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixTranslation(115.0f, 20.0f, 45.0f), temp);
			temp = XMMatrixMultiply(XMMatrixRotationX(55.f), temp);
			temp = XMMatrixMultiply(XMMatrixScaling(150.f, 150.f, 150.f), temp);
			temp = XMMatrixMultiply(XMMatrixRotationZ(-90.f), temp);

			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[9].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw Stonehedge"
			// Stonehenge	
			// set pipeline
			UINT mesh_strides[] = { sizeof(_OBJ_VERT_) };
			UINT mesh_offsets[] = { 0 };
			ID3D11Buffer* meshVB[] = { vBuffMesh };
			myContext->IASetVertexBuffers(0, 1, meshVB, mesh_strides, mesh_offsets);
			myContext->IASetIndexBuffer(iBuffMesh, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShader, 0, 0);
			myContext->IASetInputLayout(vMeshLayout);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRV.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(0.2f, 0.2f, 0.2f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(75.f, 10.f, 0.0f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(2532, 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "Draw GeoShader Triangle"
			//Geometery
			UINT geo_strides[] = { sizeof(VERTEX_3D) };
			UINT geo_offsets[] = { 0 };
			ID3D11Buffer* meshVBG[] = { vBuffGeo };
			myContext->IASetVertexBuffers(0, 1, meshVBG, geo_strides, geo_offsets);
			myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			//myContext->RSSetState(rastStateCullOff);
			myContext->IASetInputLayout(vLayoutGeo);
			myContext->VSSetShader(vShaderGeo, 0, 0);
			myContext->GSSetShader(gShader, 0, 0);
			myContext->PSSetShader(geoPShader, 0, 0);

			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);

			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			myContext->GSSetConstantBuffers(0, 1, &cBuff.p);

			// Draw it
			myContext->Draw(1, 0); 

			myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			myContext->GSSetShader(NULL, 0, 0);
#pragma endregion

#pragma endregion


#pragma region "Second ViewPort (Holy Grail)"
			// Clear the screen to blue
			//const float sky_blue2[] = { 0.0f, 0.749f, 1.0f, 1 };

			//myContext->ClearRenderTargetView(myRenderTargetView, sky_blue2);

			myContext->ClearDepthStencilView(myDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

			viewPort2.Width = vpWidth / 2;
			viewPort2.Height = vpHeight;
			viewPort2.TopLeftX = vpWidth / 2;
			viewPort2.TopLeftY = 0;
			viewPort2.MinDepth = 0;
			viewPort2.MaxDepth = 1;
			
			myContext->RSSetViewports(1, &viewPort2);

#pragma region "Camera"
			//XMFLOAT3 cameraPos2 = { XMFLOAT3(cam2.GetEyePos()) };

			//cBuffL.cameraPos = cameraPos2;

			//myContext->UpdateSubresource(cBuffLight.p, 0, nullptr, &cBuffL, 0, 0);
			//myContext->PSSetShader(texPShader, 0, 0);
			//myContext->PSSetConstantBuffers(0, 1, &cBuffLight.p);

			//// Update the View Matrix after camera movement
			//cam2.UpdateCamera();
			//XMStoreFloat4x4(&MyShaderVars.vMatrix, cam2.GetViewMatrix());

			//// Projection Matrix
			//XMStoreFloat4x4(&MyShaderVars.pMatrix, cam2.GetProjectionMatrix());
			XMFLOAT3 cameraPos2 = { XMFLOAT3(cam.GetEyePos()) };

			cBuffL.cameraPos = cameraPos;

			myContext->UpdateSubresource(cBuffLight.p, 0, nullptr, &cBuffL, 0, 0);
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetConstantBuffers(0, 1, &cBuffLight.p);

			// Update the View Matrix after camera movement
			cam.UpdateCamera();
			XMStoreFloat4x4(&MyShaderVars.vMatrix, cam.GetViewMatrix());

			// Projection Matrix
			XMStoreFloat4x4(&MyShaderVars.pMatrix, cam.GetProjectionMatrix());
#pragma endregion
			myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

#pragma region "Draw Sky"
			// set pipeline
			UINT sky_strides0[] = { sizeof(SimpleVertex) };
			UINT sky_offsets0[] = { 0 };
			ID3D11Buffer* meshVB40[] = { vBuffMeshSky2 };
			myContext->IASetVertexBuffers(0, 1, meshVB40, sky_strides, sky_offsets);
			myContext->IASetIndexBuffer(iBuffMeshSky2, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderSky, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutSky2);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(skyPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVSky2.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			//temp = XMMatrixTranslation(XMVectorGetX(eyePosVector), XMVectorGetY(eyePosVector), XMVectorGetZ(eyePosVector));
			//temp = XMMatrixTranslation(XMVectorGetX(cam2.GetEyePosVector()), XMVectorGetY(cam2.GetEyePosVector()), XMVectorGetZ(cam2.GetEyePosVector()));
			temp = XMMatrixTranslation(XMVectorGetX(cam.GetEyePosVector()), XMVectorGetY(cam.GetEyePosVector()), XMVectorGetZ(cam.GetEyePosVector()));

			//temp = XMMatrixMultiply(XMMatrixScaling(1000.f, 1000.f, 1000.f), temp);

			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->RSSetState(rastStateCullOff);

			myContext->DrawIndexed(meshs[12].indicesList.size(), 0, 0); //num indices from SkyBox

			myContext->ClearDepthStencilView(myDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

			myContext->RSSetState(rastStateCullOn);
#pragma endregion

#pragma region "HG Draw Floor"
			// Draw HG Floor
			UINT floor_strides_HG[] = { sizeof(SimpleVertex) };
			UINT floor_offsets_HG[] = { 0 };
			ID3D11Buffer* meshVB_HG_Floor[] = { vBuffMeshFloorHG };
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Floor, floor_strides_HG, floor_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshFloorHG, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutFloorHG);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVFloorHG.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(200.f, 200.f, 200.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-2.85f, -0.19f, -4.9f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[8].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Bunny"
			// Draw HG Floor
			UINT bunny_strides[] = { sizeof(SimpleVertex) };
			UINT bunny_offsets[] = { 0 };
			ID3D11Buffer* meshVB_HG_Bunny[] = { vBuffMeshBunny };
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Bunny, bunny_strides, bunny_offsets);
			myContext->IASetIndexBuffer(iBuffMeshBunny, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShader, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutBunny);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVBunny.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(2.f, 2.f, 2.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(2.85f, 1.1f, -3.5f), temp);
			temp = XMMatrixMultiply(XMMatrixRotationX(67.5f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[10].indicesList.size(), 0, 0); //num indices from stonehinge

#pragma endregion
// row 1
#pragma region "HG Draw Knight"
			// Draw HG Floor
			UINT knight_strides_HG[] = { sizeof(SimpleVertex) };
			UINT knight_offsets_HG[] = { 0 };
			ID3D11Buffer* meshVB_HG_Knight[] = { vBuffMeshKnight };
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(0.5f, 1.55f, -5.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion  

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(1.5f, 1.55f, -5.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(2.5f, 1.55f, -5.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-.5f, 1.55f, -5.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-1.5f, 1.55f, -5.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion
// row 2
#pragma region "HG Draw Knight"
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(0.5f, 1.55f, -6.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(1.5f, 1.55f, -6.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(2.5f, 1.55f, -6.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-.5f, 1.55f, -6.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-1.5f, 1.55f, -6.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion
// row 3
#pragma region "HG Draw Knight"
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(0.5f, 1.55f, -7.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(1.5f, 1.55f, -7.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(2.5f, 1.55f, -7.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-.5f, 1.55f, -7.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Knight"
			// Draw HG Floor
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Knight, knight_strides_HG, knight_offsets_HG);
			myContext->IASetIndexBuffer(iBuffMeshKnight, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShaderFloor, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutKnight);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVKnight.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(4.f, 4.f, 4.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-1.5f, 1.55f, -7.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[11].indicesList.size(), 0, 0); //num indices from stonehinge
#pragma endregion

#pragma region "HG Draw Grail"
			// Draw HG Floor
			UINT grail_strides[] = { sizeof(SimpleVertex) };
			UINT grail_offsets[] = { 0 };
			ID3D11Buffer* meshVB_HG_Grail[] = { vBuffMeshGrail };
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Grail, grail_strides, grail_offsets);
			myContext->IASetIndexBuffer(iBuffMeshGrail, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShader, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutGrail);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVGrail.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(-.85f, 0.2f, -.5f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[13].indicesList.size(), 0, 0); //num indices from stonehinge

#pragma endregion

#pragma region "HG Draw Crow"
			// Draw HG Floor
			UINT crow_strides[] = { sizeof(SimpleVertex) };
			UINT crow_offsets[] = { 0 };
			ID3D11Buffer* meshVB_HG_Crow[] = { vBuffMeshCrow };
			myContext->IASetVertexBuffers(0, 1, meshVB_HG_Crow, crow_strides, crow_offsets);
			myContext->IASetIndexBuffer(iBuffMeshCrow, DXGI_FORMAT_R32_UINT, 0);
			myContext->VSSetShader(vMeshShader, 0, 0);
			myContext->IASetInputLayout(vMeshLayoutCrow);

			// Set texture 
			// Pixel Shader Stage
			myContext->PSSetShader(texPShader, 0, 0);
			myContext->PSSetShaderResources(0, 1, &textureRVCrow.p);
			myContext->PSSetSamplers(0, 1, &samplerState.p);


			// modify world matrix before drawing next obj
			temp = XMMatrixIdentity();
			temp = XMMatrixMultiply(XMMatrixScaling(0.5f, 0.5f, 0.5f), temp);
			temp = XMMatrixMultiply(XMMatrixTranslation(50.85f, 20.0f, .5f), temp);
			temp = XMMatrixMultiply(XMMatrixRotationX(67.5f), temp);
			temp = XMMatrixMultiply(XMMatrixRotationZ(90.f), temp);
			//temp = XMMatrixMultiply(XMMatrixScaling(20.f, 20.f, 20.f), temp);
			XMStoreFloat4x4(&MyShaderVars.wMatrix, temp);
			// send it to the CARD
			hr = myContext->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
			*((Shader_Vars*)(gpuBuffer.pData)) = MyShaderVars;
			// OR memcpy(gpuBuffer.pData, &MyMatrices, sizeof(WVP));
			myContext->Unmap(cBuff, 0);

			// Draw it
			myContext->DrawIndexed(meshs[14].indicesList.size(), 0, 0); //num indices from stonehinge

#pragma endregion



#pragma endregion

			// Present Backbuffer using Swapchain object
			// Framerate is currently unlocked, we suggest "MSI Afterburner" to track your current FPS and memory usage.
			mySwapChain->Present(1, 0); // set first argument to 1 to enable vertical refresh sync with display

			// Free any temp DX handles aquired this frame
			myRenderTargetView->Release();

			
			// Reset Time
			//delta = 0.0f;
			//}

		}

	}

}

