#include "CCamera.h"

CCamera::CCamera()
{
		pitch = 0;
		yaw = 0;
		roll = 0;

		xPosition = 0;
		yPosition = 0;
		zPosition = 0;

		cameraOffset = D3DXVECTOR3(0.0, 0.0, 0.0);
		targetPosition = D3DXVECTOR3(0.0, 0.0, 0.0);
		cameraPosition = D3DXVECTOR3(0.0, 0.0, 0.0);

		cameraXAxis = D3DXVECTOR3(1.0, 0.0, 0.0);
		cameraYAxis = D3DXVECTOR3(0.0, 1.0, 0.0);
		cameraZAxis = D3DXVECTOR3(0.0, 0.0, 1.0);
}

CCamera::~CCamera(void)
{
		//Destructor!
}

void CCamera::thirdPersonCamera(D3DXVECTOR3 targetPos, D3DXVECTOR3 cameraPos)
{
		targetPosition = targetPos;
		cameraPosition = cameraPos;

		
		cameraOffset = cameraZAxis = cameraPosition - targetPosition;
		D3DXVec3Normalize(&cameraZAxis, &D3DXVECTOR3(0.0, 0.0, 1.0));
}

void CCamera::calculateViewMatrix(D3DXMATRIX *viewMatrix)
{
		//  Z   Y
		//  |  /
		//  | /
		//  |/
		//  +------ X
		//  Camera Axes
		
		//Set the Camera axes	
		cameraXAxis = D3DXVECTOR3(1.0, 0.0, 0.0); //Typically refered to as 'Right'
		cameraYAxis = D3DXVECTOR3(0.0, 1.0, 0.0); //Typically refered to as 'Up'	
		cameraZAxis = D3DXVECTOR3(0.0, 0.0, 1.0); //Typically refered to as 'Look'
		
		//Pitch is defined as rotation about the X-Axis		
		D3DXMATRIX pitchMatrix;	
		D3DXMatrixRotationAxis(&pitchMatrix, &cameraXAxis, pitch);
	
		//Using the Pitch Matrix, rotate cameraZAxis and cameraYAxis about the X-Axis		
		D3DXVec3TransformCoord(&cameraZAxis, &cameraZAxis, &pitchMatrix);
		D3DXVec3TransformCoord(&cameraYAxis, &cameraYAxis, &pitchMatrix);
		
		//Yaw is defined as rotation about the Y-Axis	
		D3DXMATRIX yawMatrix;	
		D3DXMatrixRotationAxis(&yawMatrix, &cameraYAxis, yaw);
	
		//Using the Yaw Matrix, rotate cameraZAxis and cameraXAxis about the Y-Axis		
		D3DXVec3TransformCoord(&cameraZAxis, &cameraZAxis, &yawMatrix);
		D3DXVec3TransformCoord(&cameraXAxis, &cameraXAxis, &yawMatrix);
		
		//Roll is defined as rotation about the Z-Axis
		D3DXMATRIX rollMatrix;
		D3DXMatrixRotationAxis(&rollMatrix, &cameraZAxis, roll);
	
		//Using the Roll Matrix, rotate cameraYAxis and cameraXAxis about the Z-Axis	
		D3DXVec3TransformCoord(&cameraXAxis, &cameraXAxis, &rollMatrix);
		D3DXVec3TransformCoord(&cameraYAxis, &cameraYAxis, &rollMatrix);
		
		//Now we build our view matrix using our transformed camera axes	
		D3DXMatrixIdentity(viewMatrix);
		D3DXMatrixLookAtLH(viewMatrix, &cameraPosition, &targetPosition, &cameraYAxis);
		
		viewMatrix->_11 = cameraXAxis.x; viewMatrix->_12 = cameraYAxis.x; viewMatrix->_13 = cameraZAxis.x;
		viewMatrix->_21 = cameraXAxis.y; viewMatrix->_22 = cameraYAxis.y; viewMatrix->_23 = cameraZAxis.y;
		viewMatrix->_31 = cameraXAxis.z; viewMatrix->_32 = cameraYAxis.z; viewMatrix->_33 = cameraZAxis.z;
		
		viewMatrix->_41 = -D3DXVec3Dot(&cameraPosition, &cameraXAxis);
		viewMatrix->_42 = -D3DXVec3Dot(&cameraPosition, &cameraYAxis);	
		viewMatrix->_43 = -D3DXVec3Dot(&cameraPosition, &cameraZAxis);
	
}



void CCamera::setRotation(D3DXVECTOR3 rotation)
{
		pitch = rotation.x;
		yaw = rotation.y;
		roll = rotation.z;
}



void CCamera::setPosition(D3DXVECTOR3 position, float camOffset)
{
		cameraPosition.x = position.x;
		cameraPosition.y = position.y;
		cameraPosition.z = position.z - camOffset;
}
