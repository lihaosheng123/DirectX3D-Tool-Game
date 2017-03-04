/********************************************************************************
* �^�C�g���@OPENGL 01
* �t�@�C�����@CTransferEffect.cpp
* �쐬�� AT13B284 42 ���ݐ�
* �쐬�� 2016/08/23
���X�|���S���̕`��p
********************************************************************************/
#include "main.h"
#include "Camera.h"
#include "sceneX.h"
#include "manager.h"
#include "scene.h"
#include "sceneMouse.h"
#include "score.h"

//=============================================================================
// �N���X�R���X�g���N�^
//=============================================================================
CTransferEffect::CTransferEffect()
{
	m_pTexture = NULL;			// Direct3D�e�N�X�`���̃|�C���^
	m_pVtxBuffer = NULL;		// Direct3D�o�b�t�@�ւ̃|�C���^
	for(int i = 0;i<TRANSFEREFFECT_MAX;i++)
	{
		m_TransferEffect[i].m_Buse = false;
	}
}
//=============================================================================
// �N���X�f�X�g���N�^
//=============================================================================
CTransferEffect::~CTransferEffect()
{

}
CTransferEffect* CTransferEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CTransferEffect *sceneTransferEffect;
	sceneTransferEffect = new CTransferEffect;

	sceneTransferEffect->Init(pos,rot,height ,width,TEXTURE_FILE);

	return sceneTransferEffect;
}
//=============================================================================
//  �֐����@�FInit
//  �@�\�T�v�F3D�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT CTransferEffect::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	for(int i = 0;i<TRANSFEREFFECT_MAX;i++)
	{
		m_TransferEffect[i].m_Position = pos;	// ���_���W
		m_TransferEffect[i].m_Rotation = rot;	// ��]

		m_TransferEffect[i].m_height = height;
		m_TransferEffect[i].m_width = width;


		m_TransferEffect[i].m_scl.x = 1.0f;
		m_TransferEffect[i].m_scl.y = 1.0f;
		m_TransferEffect[i].m_scl.z = 1.0f;

		m_TransferEffect[i].nCount = 0;			// �J�E���^
		m_TransferEffect[i].nPattern = 0;		// �p�^�[��No.	
	//���_�o�b�t�@�̐���
	if( FAILED ( device -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * TRANSFEREFFECT_MAX * 4,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&m_pVtxBuffer,
												NULL
	) ) )
	{
		return E_FAIL;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( device, TEXTURE_FILE, &m_pTexture );
	}
	//�t�B�[���h���_�o�b�t�@�̏�����
	VERTEX_3D *pVtx;

	m_pVtxBuffer -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for(int i = 0;i<TRANSFEREFFECT_MAX;i++, pVtx += 4 )
	{
	pVtx[ 0 ].pos = D3DXVECTOR3(- m_TransferEffect[i].m_width/2, m_TransferEffect[i].m_height,0.0f);	// ���_���W
	pVtx[ 1 ].pos = D3DXVECTOR3( m_TransferEffect[i].m_width/2, m_TransferEffect[i].m_height,0.0f);
	pVtx[ 2 ].pos = D3DXVECTOR3( -m_TransferEffect[i]. m_width/2,0.0f,0.0f);
	pVtx[ 3 ].pos = D3DXVECTOR3( m_TransferEffect[i].m_width/2,0.0f,0.0f);

	// ���_�F�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//UV�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_TRANSFEREFFECT, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_TRANSFEREFFECT);
	pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_TRANSFEREFFECT, TEXTURE_SIZE_Y_TRANSFEREFFECT);
	}
	/* ���_��� �J�M���� */
	m_pVtxBuffer -> Unlock();
	return S_OK;
}
//=============================================================================
//  �֐����@�FDraw
//  �@�\�T�v�F3D�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void CTransferEffect::Draw (void)
{


	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	for(int i = 0;i<TRANSFEREFFECT_MAX;i++)
	{
		if(m_TransferEffect[i].m_Buse == true)
	{
	// �r���[�}�g���b�N�X���擾
	device->GetTransform( D3DTS_VIEW, &m_TransferEffect[i].mtxView );

	// ���C�g�����B�ǂ̊p�x���猩�Ă������悤�ɂ��邽�߁A�r���{�[�h�̉A�e�𖳂����B
	device->SetRenderState( D3DRS_LIGHTING, FALSE );

	// �����_�[�X�e�[�g�̐ݒ�iz�e�X�g�j
	device->SetRenderState( D3DRS_ZENABLE, TRUE );
	device->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z�l�̍X�V
	// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j
	device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// ���̒l���A���t�@�l���傫����Ε`�悷��B
	device->SetRenderState( D3DRS_ALPHAREF, 200 );						// �A���t�@�l�B0�œ����ȕ����B
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF( FVF_VERTEX_3D );

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_TransferEffect[i].m_mtxWorld );

	// �r���[�}�g���b�N�X�̋t�s������߂�B
	D3DXMatrixInverse( &m_TransferEffect[i].m_mtxWorld, NULL, &m_TransferEffect[i].mtxView );

	m_TransferEffect[i].m_mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
	m_TransferEffect[i].m_mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
	m_TransferEffect[i].m_mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
	// �X�P�[���𔽉f
	D3DXMatrixScaling( &m_TransferEffect[i].mtxScl, m_TransferEffect[i].m_scl.x, m_TransferEffect[i].m_scl.y, m_TransferEffect[i].m_scl.z );
	D3DXMatrixMultiply( &m_TransferEffect[i].m_mtxWorld, &m_TransferEffect[i].m_mtxWorld, &m_TransferEffect[i].mtxScl );

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &m_TransferEffect[i].mtxRot, m_TransferEffect[i].m_Rotation.y, m_TransferEffect[i].m_Rotation.x, m_TransferEffect[i].m_Rotation.z );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
	D3DXMatrixMultiply( &m_TransferEffect[i].m_mtxWorld, &m_TransferEffect[i].m_mtxWorld, &m_TransferEffect[i].mtxRot );

	// �ʒu�𔽉f
	D3DXMatrixTranslation( &m_TransferEffect[i].mtxTrans, m_TransferEffect[i].m_Position.x, m_TransferEffect[i].m_Position.y, m_TransferEffect[i].m_Position.z );
	D3DXMatrixMultiply( &m_TransferEffect[i].m_mtxWorld, &m_TransferEffect[i].m_mtxWorld, &m_TransferEffect[i].mtxTrans );

	// ���[���h�}�g���b�N�X��ݒ�
	device->SetTransform( D3DTS_WORLD, &m_TransferEffect[i].m_mtxWorld );

	// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
	device->SetStreamSource( 0, m_pVtxBuffer, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

	// �e�N�X�`���̐ݒ�
	device->SetTexture( 0,m_pTexture );
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	// �u�����h���Z����
	device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// ���f�X�e�B�l�[�V�����J���[�̎w��


	// �|���S���̕`��
	device->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
							( i * 4 ),								// �`�悷��ŏ��̒��_
							2 );										// �`�悷��v���~�e�B�u��
	
	
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	// �����_�[�X�e�[�g�̐ݒ���f�t�H���g�ɖ߂��B
	device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// �f�t�H���g�ɖ߂��B
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// �f�t�H���g�ɖ߂��B

	// �ʏ�u�����h
	device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��

	// ���C�g�_��
	device->SetRenderState( D3DRS_LIGHTING, TRUE );
		}
	}
}
//=============================================================================
//  �֐����@�FUpdate
//  �@�\�T�v�F3D�̍X�V����
//  �߂�l�@�F
//=============================================================================
void CTransferEffect::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CBullet *m_Bullet = game ->GetBullet();
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	for(int i = 0;i<TRANSFEREFFECT_MAX;i++,pVtx += 4 )
	{
		if(m_TransferEffect[i].m_Buse == true)
	{
		m_TransferEffect[i].nCount++;
		if((m_TransferEffect[i].nCount % INTERVAL_PATTERN_TRANSFEREFFECT) == 0)
		{// �A�j���[�V�����؂�ւ�
			m_TransferEffect[i].nPattern++;
			if(m_TransferEffect[i].nPattern >= NUM_PATTERN_TRANSFEREFFECT )
			{// �A�j���[�V�����p�^�[�����I��
				m_TransferEffect[i].m_Buse = false;
			}
			pVtx[0].tex = D3DXVECTOR2(m_TransferEffect[i].nPattern * TEXTURE_SIZE_X_TRANSFEREFFECT, m_TransferEffect[i].nPattern * TEXTURE_SIZE_Y_TRANSFEREFFECT);
			pVtx[1].tex = D3DXVECTOR2((m_TransferEffect[i].nPattern + 1) * TEXTURE_SIZE_X_TRANSFEREFFECT, m_TransferEffect[i].nPattern * TEXTURE_SIZE_Y_TRANSFEREFFECT);
			pVtx[2].tex = D3DXVECTOR2(m_TransferEffect[i].nPattern * TEXTURE_SIZE_X_TRANSFEREFFECT,(m_TransferEffect[i].nPattern + 1) * TEXTURE_SIZE_Y_TRANSFEREFFECT);
			pVtx[3].tex = D3DXVECTOR2((m_TransferEffect[i].nPattern + 1) * TEXTURE_SIZE_X_TRANSFEREFFECT, (m_TransferEffect[i].nPattern + 1) * TEXTURE_SIZE_Y_TRANSFEREFFECT);

			// ���_�f�[�^���A�����b�N����
			m_pVtxBuffer->Unlock();
		}
	}

	}
}
//=============================================================================
//  �֐����@�FUninit
//  �@�\�T�v�FCTransferEffect�̏I������
//  �߂�l�@�F
//=============================================================================
void CTransferEffect::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
void CTransferEffect::SetTransferEffect(D3DXVECTOR3 pos)
{
	
	for(int i = 0; i < TRANSFEREFFECT_MAX; i++)
	{	
		if(m_TransferEffect[i].m_Buse == false)
		{
			m_TransferEffect[i].m_Position = pos;
			m_TransferEffect[i].nCount = 0;
			m_TransferEffect[i].nPattern = 0;
			m_TransferEffect[i].m_Buse = true;
			break;
		}
	}
}