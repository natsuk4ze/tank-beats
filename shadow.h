//=============================================================================
//
// �e���� [shadow.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

#define SHADOW_MAX (2)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitShadow(int type);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);



#endif
