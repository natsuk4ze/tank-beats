//=============================================================================
//
// �v���C���[���� [player.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLYER_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//�p�[�c�̍��W���擾
D3DXVECTOR3 GetPartPos(D3DXVECTOR3 ppos, D3DXVECTOR3 prot, D3DXVECTOR3 pos);

#endif
