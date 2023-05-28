//=============================================================================
//
// �r���{�[�h���� [billboard.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define BILLBOARD_MAX (1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBillboard(int type);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

#endif
