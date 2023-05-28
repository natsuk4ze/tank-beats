//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "player.h"
#include "player_parts_a.h"
#include "player_parts_b.h"
#include "player_parts_c.h"
#include "player_parts_d.h"
#include "player_parts_e.h"
#include "input.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "particle.h"

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	InitPlayer_Parts_a(0);
	InitPlayer_Parts_b(0);
	InitPlayer_Parts_c(0);
	InitPlayer_Parts_d(0);
	InitPlayer_Parts_e(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	UninitPlayer_Parts_a();
	UninitPlayer_Parts_b();
	UninitPlayer_Parts_c();
	UninitPlayer_Parts_d();
	UninitPlayer_Parts_e();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);

	if (player_parts_a->use == true)
	{
		UpdatePlayer_Parts_a();
		UpdatePlayer_Parts_b();
		UpdatePlayer_Parts_c();
		UpdatePlayer_Parts_d();
		UpdatePlayer_Parts_e();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawPlayer(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);

	if (player_parts_a->use == true)
	{
		DrawPlayer_Parts_a();
		DrawPlayer_Parts_b();
		DrawPlayer_Parts_c();
		DrawPlayer_Parts_d();
		DrawPlayer_Parts_e();
	}
}

//=============================================================================
//�p�[�c�̍��W���擾
//=============================================================================
D3DXVECTOR3 GetPartPos(D3DXVECTOR3 ppos, D3DXVECTOR3 prot, D3DXVECTOR3 pos)
{
	
	D3DXVECTOR3 x = D3DXVECTOR3(pos.x, 0.0f, 0.0f);
	D3DXVECTOR3 y = D3DXVECTOR3(0.0f, pos.y, 0.0f);
	D3DXVECTOR3 z = D3DXVECTOR3(0.0f, 0.0f, pos.z);

	x.x = pos.x*cosf(prot.z)*cosf(prot.y);
	x.y = pos.x*sinf(prot.z)*cosf(prot.x);
	x.z = -pos.x*cosf(prot.z)*sinf(prot.y);

	y.x = pos.y*cosf(prot.z)*sinf(prot.x)*sinf(prot.y);
	y.y = pos.y*cosf(prot.z)*cosf(prot.x);
	y.z = pos.y*cosf(prot.z)*sinf(prot.x)*cosf(prot.y);

	z.x = pos.z*cosf(prot.x)*sinf(prot.y);
	z.y = -pos.z*sinf(prot.x);
	z.z = pos.z * cosf(prot.x)*cosf(prot.y);

	return  x + y + z + ppos;
}
