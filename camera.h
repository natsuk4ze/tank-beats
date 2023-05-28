//=============================================================================
//
// �J�������� [camera.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);

#endif

