#pragma once

#include <d3d11.h>
#include <DirectXMath.h>  // Directs  (gateware also has its own)
#include "../../Gateware/Interface/G_Math/GMathDefines.h"
#include "../../Gateware/Interface/G_Math/GMatrix.h"
#include "../../Gateware/Interface/G_System/GInput.h"

using namespace DirectX;

class Camera
{
	XMVECTOR eyePosVector = { 4,7,-20 };
	XMFLOAT3 eyePos = { 4, 7, -20 };
	XMFLOAT3 eyeRot{ 0,0,0 };
	XMVECTOR eyeRotVector;

	XMVECTOR vUp = { 0,1,0 };
	XMVECTOR vDown = { 0,-1,0 };
	XMVECTOR vForward = { 0,0,1 };
	XMVECTOR vLeft = { -1,0,0 };
	XMVECTOR vRight = { 1, 0, 0 };
	XMVECTOR vBack = { 0,0,-1 };

	XMVECTOR vUpD = { 0,1,0 };
	XMVECTOR vDownD = { 0,-1,0 };
	XMVECTOR vForwardD = { 0,0,1 };
	XMVECTOR vLeftD = { -1,0,0 };
	XMVECTOR vRightD = { 1, 0, 0 };
	XMVECTOR vBackD = { 0,0,-1 };

	XMMATRIX viewMatrix = XMMatrixLookAtLH(eyePosVector, { 0,0,0 }, { 0,1,0 });;
	XMMATRIX projectionMatrix;

	float x = 0.0f;
	float y = 0.0f;
	float outState = 0.0f;


	XMVECTOR lightPosVectorPoint = { 10.f,10.f,0.f, 1.0f };
	XMVECTOR lightPosVectorSpot = { -30.f, 10.0f, 0.0f, 1.0f};

	XMFLOAT3 lightPosPoint = { 10.f,10.f,0.f};
	XMFLOAT3 lightPosSpot = { -30.f, 10.0f, 0.0f};

public:

	void UpdateCamera();
	void MoveLeft();
	void MoveRight();
	void MoveBack();
	void MoveForward();
	void MoveUp();
	void MoveDown();
	void Move(XMVECTOR _direction);
	void MouseRotation(float _x, float _y);
	void RotateCamera(float _x, float _y);
	void SetEyePos(XMFLOAT3 _eyePos); 
	void SetProjectionMatrix(XMMATRIX _projMatrix);
	void SetEyeRot(XMFLOAT3 _eyeRot);
	void SetEyeRotVector(XMVECTOR _eyeRot);
	void SetEyePosVector(XMVECTOR _eyePosVector);

	void MoveLeft(float cameraSpeed, float delta);
	void MoveRight(float cameraSpeed, float delta);
	void MoveBack(float cameraSpeed, float delta);
	void MoveForward(float cameraSpeed, float delta);
	void MoveUp(float cameraSpeed, float delta);
	void MoveDown(float cameraSpeed, float delta);


	XMFLOAT3 GetEyePos();
	XMVECTOR GetEyePosVector(); 
	XMMATRIX GetViewMatrix();     
	XMMATRIX GetProjectionMatrix(); 
	XMVECTOR GetForwardVector();
	XMVECTOR GetRightVector();
	XMFLOAT3 GetEyeRot();
	XMVECTOR GetEyeRotVector();


	// Lighting
	void SetLightPosPoint(XMVECTOR _lightPosPoint);
	void SetLightPosSpot(XMVECTOR _lightPosPoint);

	XMVECTOR GetLightPosPointVector();
	XMVECTOR GetLightPosSpotVector();

};

#pragma region "Light Get/Set"
// Lighting stuff
void Camera::SetLightPosPoint(XMVECTOR _lightPosPoint)
{
	this->lightPosVectorPoint = _lightPosPoint;
}

void Camera::SetLightPosSpot(XMVECTOR _lightPosSpot)
{
	this->lightPosVectorSpot = _lightPosSpot;
}

XMVECTOR Camera::GetLightPosPointVector()
{
	return this->lightPosVectorPoint;
}

XMVECTOR Camera::GetLightPosSpotVector()
{
	return this->lightPosVectorSpot;
}
#pragma endregion

#pragma region "Camera Get/Set"
// Everything Camera
void Camera::SetProjectionMatrix(XMMATRIX _projMatrix)
{
	this->projectionMatrix = _projMatrix;
}

void Camera::SetEyePos(XMFLOAT3 _eyePos)
{
	this->eyePos = _eyePos;
}

void Camera::SetEyePosVector(XMVECTOR _eyePosVector)
{
	this->eyePosVector = _eyePosVector;
}

void Camera::SetEyeRot(XMFLOAT3 _eyeRot)
{
	this->eyeRot = _eyeRot;
}

void Camera::SetEyeRotVector(XMVECTOR _eyeRotVector)
{
	this->eyeRotVector = _eyeRotVector;
}

XMFLOAT3 Camera::GetEyePos()
{
	return this->eyePos;
}
XMVECTOR Camera::GetEyePosVector()
{
	return this->eyePosVector;
}
XMFLOAT3 Camera::GetEyeRot()
{
	return this->eyeRot;
}
XMVECTOR Camera::GetEyeRotVector()
{
	return this->eyeRotVector;
}
XMVECTOR Camera::GetForwardVector()
{
	return this->vForward;
}
XMVECTOR Camera::GetRightVector()
{
	return this->vRightD;
}
XMMATRIX Camera::GetViewMatrix()
{
	return this->viewMatrix;
}
XMMATRIX Camera::GetProjectionMatrix()
{
	return this->projectionMatrix;
}
#pragma endregion

#pragma region "Cam Move Non-Time Based"
void Camera::MoveLeft()
{
	this->eyePosVector += vLeft;
}
void Camera::MoveRight()
{
	this->eyePosVector += vRight;
}
void Camera::MoveBack()
{
	this->eyePosVector += vBack;
}
void Camera::MoveForward()
{
	this->eyePosVector += vForward;
}
void Camera::MoveUp()
{
	this->eyePosVector += vUp;
}
void Camera::MoveDown()
{
	this->eyePosVector += vDown;
}
#pragma endregion

#pragma region "Cam Move Time based"
void Camera::MoveLeft(float cameraSpeed, float delta)
{
	this->eyePosVector += (vLeft * cameraSpeed * delta);
}
void Camera::MoveRight(float cameraSpeed, float delta)
{
	this->eyePosVector += (vRight * cameraSpeed * delta);
}
void Camera::MoveBack(float cameraSpeed, float delta)
{
	this->eyePosVector += (vBack * cameraSpeed * delta);
}
void Camera::MoveForward(float cameraSpeed, float delta)
{
	this->eyePosVector += (vForward * cameraSpeed * delta);
}
void Camera::MoveUp(float cameraSpeed, float delta)
{
	this->eyePosVector += (vUp * cameraSpeed * delta);
}
void Camera::MoveDown(float cameraSpeed, float delta)
{
	this->eyePosVector += (vDown * cameraSpeed * delta);
}
#pragma endregion


void Camera::Move(XMVECTOR _direction)
{
	this->eyePosVector += _direction;
}

void Camera::MouseRotation(float _x, float _y)
{
		this->eyeRot.x += _x * 0.0015f;
		this->eyeRot.y += _y * 0.0015f;
		this->eyeRot.z += 0;
		eyeRotVector = XMLoadFloat3(&eyeRot);
}

void Camera::RotateCamera(float _x, float _y)
{
	this->eyeRot.x += _x;
	this->eyeRot.y += _y;
	this->eyeRot.z += 0;
	eyeRotVector = XMLoadFloat3(&eyeRot);
}

void Camera::UpdateCamera()
{
	XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(this->eyeRot.x, this->eyeRot.y, 0.0f);
	XMVECTOR camTarget = XMVector3TransformCoord(vForwardD, rotMatrix);

	camTarget += eyePosVector;
	XMStoreFloat3(&eyePos, eyePosVector);

	XMVECTOR upDir = XMVector3TransformCoord(vUpD, rotMatrix);

	viewMatrix = XMMatrixLookAtLH(eyePosVector, camTarget, upDir);

	XMMATRIX rotMatrix2 = XMMatrixRotationRollPitchYaw(eyeRot.x, eyeRot.y, 0.0f);
	vForward = XMVector3TransformCoord(vForwardD, rotMatrix2);
	vLeft = XMVector3TransformCoord(vLeftD, rotMatrix2);
	vRight = XMVector3TransformCoord(vRightD, rotMatrix2);
	vBack = XMVector3TransformCoord(vBackD, rotMatrix2);

}