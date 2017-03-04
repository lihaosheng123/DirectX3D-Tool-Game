///********************************************************************************
//* �^�C�g���@01
//* �t�@�C�����@CDoor.cpp
//* �쐬�� AT13B284 42 ���ݐ�
//* �쐬�� 2016/07/11
//* Door�`��
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "CDoor.h"
//�O���[�o���ϐ�

//=============================================================================
// �N���X�R���X�g���N�^
//=============================================================================
CDoor::CDoor()
{
}
//=============================================================================
// �N���X�f�X�g���N�^
//=============================================================================
CDoor::~CDoor()
{

}
//=============================================================================
//  �֐����@�FInit
//  �@�\�T�v�F3D�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT CDoor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	CEffect *m_Effect = game->GetEffect();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	////////////
	m_pTexture = NULL;			// Direct3D�e�N�X�`���̃|�C���^

	m_Mesh = NULL;

	m_BuffMat = NULL;

	D3DXCreateTextureFromFile(device, "data\\TEXTURE\\door.png", &m_pTexture);// �e�N�X�`���ǂݍ���
	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_FILE,
		D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
		device,
		NULL,
		&m_BuffMat,		// �}�e���A�����
		NULL,
		&m_nNumMat,			// �}�e���A����
		&m_Mesh)))		// ���b�V�����
	{
		return E_FAIL;
	}
	// ���f���̏����ݒ�
	m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	// ���_���W
	m_Rotation = D3DXVECTOR3(rot.x, rot.y, rot.z);	// ��]
	m_Changge = 0;
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	return S_OK;
}
//=============================================================================
//  �֐����@�FUninit
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void CDoor::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}
//------------------------------------------------------------------------------
//	�֐���:	void CDoor::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CDoor::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

							// ���݂̃}�e���A�������擾����B
	device->GetMaterial(&matDef);
	// �����_�[�X�e�[�g�̐ݒ�iz�e�X�g�j
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z�l�̍X�V
															// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j


															//���f���ɖ���ɂȂ�
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);	// y,x,z
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);



	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);



	// ���[���h�}�g���b�N�X��ݒ�
	device->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �L���X�g�ϊ�
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		device->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		device->SetTexture(0, m_pTexture);
		// ���b�V���̕`��
		m_Mesh->DrawSubset(nCntMat);
	}
	// �����_�[�X�e�[�g�̐ݒ���f�t�H���g�ɖ߂��B
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// �f�t�H���g�ɖ߂��B
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// �f�t�H���g�ɖ߂��B
																	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	device->SetMaterial(&matDef);


}
//------------------------------------------------------------------------------
//	�֐���:	void CDoor::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CDoor::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CDoor *m_Door = BuildManager->GetDoor();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	m_NumCheck.x = (int)(m_BuildCamera->m_3DPos.x) - (int)(m_BuildCamera->m_3DPos.x) % 50;
	m_NumCheck.z = (int)(m_BuildCamera->m_3DPos.z) - (int)(m_BuildCamera->m_3DPos.z) % 50;
	m_NumCheck.y = 0 + m_Changge;

	if (m_Input->GetKeyboardTrigger(DIK_U))
	{
		m_Changge += 50;
	}

	if (m_Input->GetKeyboardTrigger(DIK_O))
	{
		m_Changge -= 50;
	}
	switch (m_type)
	{
	case CDoor::DOOR_BUILDING_FRONT:
		m_Door->m_Position.x = (int)m_NumCheck.x;	// ���_���W
		m_Door->m_Position.z = (int)m_NumCheck.z;
		m_Door->m_Position.y = (int)m_NumCheck.y;
		m_Door->m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		break;
	case CDoor::DOOR_BUILDING_BACK:
		m_Door->m_Position.x = (int)m_NumCheck.x;	// ���_���W
		m_Door->m_Position.z = (int)m_NumCheck.z;
		m_Door->m_Position.y = (int)m_NumCheck.y;
		m_Door->m_Rotation = D3DXVECTOR3(0.0f, 3.14f, 0.0f);

		break;
	case CDoor::DOOR_BUILDING_LEFT:
		m_Door->m_Position.x = (int)m_NumCheck.x;	// ���_���W
		m_Door->m_Position.z = (int)m_NumCheck.z;
		m_Door->m_Position.y = (int)m_NumCheck.y;
		m_Door->m_Rotation = D3DXVECTOR3(0.0f, -1.57f, 0.0f);

		break;
	case CDoor::DOOR_BUILDING_RIGHT:
		m_Door->m_Position.x = (int)m_NumCheck.x;	// ���_���W
		m_Door->m_Position.z = (int)m_NumCheck.z;
		m_Door->m_Position.y = (int)m_NumCheck.y;
		m_Door->m_Rotation = D3DXVECTOR3(0.0f, 1.57f, 0.0f);

		break;
	case CDoor::DOOR_BUILDING_FALSE:
		m_Door->m_Position.x = 5000.0f;
		m_Door->m_Position.z = 5000.0f;
		m_Door->m_Position.y = 5000.0f;

		break;
	case CDoor::DOOR_MAX:
		break;
	default:
		break;
	}

}
CDoor* CDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CDoor *Door;
	Door = new CDoor;
	Door->Init(pos, rot, height, width, TEXTURE_FILE);
	return Door;
}