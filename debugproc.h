//=============================================================================
//
// �f�o�b�O�\������ [debugproc.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(const char *fmt,...);

#endif