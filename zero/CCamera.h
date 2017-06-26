////////////////////////////////////////////////////
//CCamera.h
//Zero, Created 22/06/2017
////////////////////////////////////////////////////
#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>

class CCamera
{
public:
		CCamera();
		~CCamera(void);

		void thirdPersonCamera(D3DXVECTOR3 targetPos, D3DXVECTOR3 cameraPos);
		void calculateViewMatrix(D3DXMATRIX *viewMatrix);
		void setRotation(D3DXVECTOR3 rotation);
		void setPosition(D3DXVECTOR3 position, float camOffset);
private:
		float pitch;
		float yaw;
		float roll;

		float xPosition;
		float yPosition;
		float zPosition;

		D3DXVECTOR3 targetPosition, cameraPosition, cameraOffset;
		D3DXVECTOR3 cameraYAxis, cameraZAxis, cameraXAxis;
};

#endif
