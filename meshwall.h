//=============================================================================
//
// ���b�V���ǂ̏��� [meshwall.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
	int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

#endif