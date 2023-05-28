//=============================================================================
//
// ���b�V���ǂ̏��� [meshwall.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "meshwall.h"
#include "input.h"
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_MESH_WALL		(8)			// �ǂ̑���
#define	TEXTURE_FILENAME	"data/TEXTURE/bg003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_WALL		(5.0f)						// �ړ����x
#define	VALUE_ROTATE_WALL	(D3DX_PI * 0.001f)			// ��]���x

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pD3DTexture = NULL;	// �e�N�X�`���ǂݍ��ݏꏊ

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pD3DIdxBuff;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3 rot;						// �|���S���̉�]�p
	int nNumBlockX, nNumBlockY;				// �u���b�N��
	int nNumVertex;							// �����_��	
	int nNumVertexIndex;					// ���C���f�b�N�X��
	int nNumPolygon;						// ���|���S����
	float fBlockSizeX, fBlockSizeY;			// �u���b�N�T�C�Y
} MESH_WALL;

MESH_WALL g_aMeshWall[MAX_MESH_WALL];		// ���b�V���ǃ��[�N
int g_nNumMeshField = 0;					// ���b�V���ǂ̐�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
	int nNumBlockX, int nNumBlockY, float fBlockSizeX, float fBlockSizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESH_WALL *pMesh;

	if (g_nNumMeshField >= MAX_MESH_WALL)
	{
		return E_FAIL;
	}

	// �e�N�X�`���̓ǂݍ���
	if (!g_pD3DTexture)
	{
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,		// �t�@�C���̖��O
			&g_pD3DTexture);		// �ǂݍ��ރ������[
	}

	pMesh = &g_aMeshWall[g_nNumMeshField];
	g_nNumMeshField++;

	// �|���S���\���ʒu�̒��S���W��ݒ�
	pMesh->pos = pos;

	pMesh->rot = rot;

	// �u���b�N���̐ݒ�
	pMesh->nNumBlockX = nNumBlockX;
	pMesh->nNumBlockY = nNumBlockY;

	// ���_���̐ݒ�
	pMesh->nNumVertex = (nNumBlockX + 1) * (nNumBlockY + 1);

	// �C���f�b�N�X���̐ݒ�
	pMesh->nNumVertexIndex = (nNumBlockX + 1) * 2 * nNumBlockY + (nNumBlockY - 1) * 2;

	// �|���S�����̐ݒ�
	pMesh->nNumPolygon = nNumBlockX * nNumBlockY * 2 + (nNumBlockY - 1) * 4;

	// �u���b�N�T�C�Y�̐ݒ�
	pMesh->fBlockSizeX = fBlockSizeX;
	pMesh->fBlockSizeY = fBlockSizeY;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * pMesh->nNumVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pMesh->pD3DVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * pMesh->nNumVertexIndex,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pMesh->pD3DIdxBuff,				// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
#if 0
		const float texSizeX = 1.0f / g_nNumBlockX;
		const float texSizeZ = 1.0f / g_nNumBlockY;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pMesh->pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < (pMesh->nNumBlockY + 1); nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < (pMesh->nNumBlockX + 1); nCntVtxX++)
			{
				// ���_���W�̐ݒ�
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].vtx.x = -(pMesh->nNumBlockX / 2.0f) * pMesh->fBlockSizeX + nCntVtxX * pMesh->fBlockSizeX;
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].vtx.y = pMesh->nNumBlockY * pMesh->fBlockSizeY - nCntVtxY * pMesh->fBlockSizeY;
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].vtx.z = 0.0f;

				// �@���̐ݒ�
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].nor = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);

				// ���ˌ��̐ݒ�
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].diffuse = col;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxY;
			}
		}

		// ���_�f�[�^���A�����b�N����
		pMesh->pD3DVtxBuff->Unlock();
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pMesh->pD3DIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		int nCntIdx = 0;
		for (int nCntVtxY = 0; nCntVtxY < pMesh->nNumBlockY; nCntVtxY++)
		{
			if (nCntVtxY > 0)
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				pIdx[nCntIdx] = (nCntVtxY + 1) * (pMesh->nNumBlockX + 1);
				nCntIdx++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (pMesh->nNumBlockX + 1); nCntVtxX++)
			{
				pIdx[nCntIdx] = (nCntVtxY + 1) * (pMesh->nNumBlockX + 1) + nCntVtxX;
				nCntIdx++;
				pIdx[nCntIdx] = nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX;
				nCntIdx++;
			}

			if (nCntVtxY < (pMesh->nNumBlockY - 1))
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				pIdx[nCntIdx] = nCntVtxY * (pMesh->nNumBlockX + 1) + pMesh->nNumBlockX;
				nCntIdx++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		pMesh->pD3DIdxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	MESH_WALL *pMesh;
	int nCntMeshField;

	for (nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &g_aMeshWall[nCntMeshField];

		if (pMesh->pD3DVtxBuff)
		{// ���_�o�b�t�@�̊J��
			pMesh->pD3DVtxBuff->Release();
			pMesh->pD3DVtxBuff = NULL;
		}

		if (pMesh->pD3DIdxBuff)
		{// �C���f�b�N�X�o�b�t�@�̊J��
			pMesh->pD3DIdxBuff->Release();
			pMesh->pD3DIdxBuff = NULL;
		}
	}

	if (g_pD3DTexture)
	{// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	MESH_WALL *pMesh;
	int nCntMeshField;

	for (nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &g_aMeshWall[nCntMeshField];

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pMesh->mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pMesh->rot.y, pMesh->rot.x, pMesh->rot.z);
		D3DXMatrixMultiply(&pMesh->mtxWorld, &pMesh->mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pMesh->pos.x, pMesh->pos.y, pMesh->pos.z);
		D3DXMatrixMultiply(&pMesh->mtxWorld, &pMesh->mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pMesh->mtxWorld);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetStreamSource(0, pMesh->pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetIndices(pMesh->pD3DIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexture);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pMesh->nNumVertex, 0, pMesh->nNumPolygon);
	}
}

