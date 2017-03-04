/********************************************************************************
* �^�C�g���@OPENGL 01
* �t�@�C�����@sceneBillboard.cpp
* �쐬�� AT13B284 42 ���ݐ�
* �쐬�� 2016/04/26
meshfield�̕`��p
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneBillboard.h"


//=============================================================================
// �N���X�R���X�g���N�^
//=============================================================================
CSceneBillboard::CSceneBillboard()
{
	m_pTexture = NULL;			// Direct3D�e�N�X�`���̃|�C���^
	m_pVtxBuffer = NULL;		// Direct3D�o�b�t�@�ւ̃|�C���^
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
}
//=============================================================================
// �N���X�f�X�g���N�^
//=============================================================================
CSceneBillboard::~CSceneBillboard()
{

}
CSceneBillboard* CSceneBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CSceneBillboard *sceneBillboard;
	sceneBillboard = new CSceneBillboard;
	sceneBillboard->Init(pos,rot,height ,width,TEXTURE_FILE);
	return sceneBillboard;
}
//=============================================================================
//  �֐����@�FInit
//  �@�\�T�v�F3D�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT CSceneBillboard::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();


	m_Position = pos;	// ���_���W
	m_Rotation = rot;	// ��]

	m_height = height;
	m_width = width;


	m_scl.x = 1.0f;
	m_scl.y = 1.0f;
	m_scl.z = 1.0f;


	//���_�o�b�t�@�̐���
	if( FAILED ( device -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * 1 * 4,
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

	//�t�B�[���h���_�o�b�t�@�̏�����
	VERTEX_3D *pVtx;

	m_pVtxBuffer -> Lock( 0, 0, ( void** ) &pVtx, 0 );



		pVtx[ 0 ].pos = D3DXVECTOR3(- m_width/2, m_height,0.0f);	// ���_���W
		pVtx[ 1 ].pos = D3DXVECTOR3( m_width/2, m_height,0.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3( - m_width/2,0.0f,0.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3( m_width/2,0.0f,0.0f);

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

	

	// ���W�ϊ��ςݒ��_�ݒ�
	pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	
	/* ���_��� �J�M���� */
	m_pVtxBuffer -> Unlock();
	return S_OK;
}
//=============================================================================
//  �֐����@�FDraw
//  �@�\�T�v�F3D�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void CSceneBillboard::Draw (void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// �J�����Őݒ肵���r���[�}�g���b�N�X���󂯎�邽�߂̕ϐ�

	//CRenderer *m_Renderer =  GetRenderer();
	//LPDIRECT3DDEVICE9 device = m_Renderer->GetDevice();
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	// �r���[�}�g���b�N�X���擾
	device->GetTransform( D3DTS_VIEW, &mtxView );

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
	D3DXMatrixIdentity( &m_mtxWorld );

	// �r���[�}�g���b�N�X�̋t�s������߂�B
	D3DXMatrixInverse( &m_mtxWorld, NULL, &mtxView );

	m_mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
	m_mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
	m_mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

	// �X�P�[���𔽉f
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl );

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot );

	// �ʒu�𔽉f
	D3DXMatrixTranslation( &mtxTrans, m_Position.x, m_Position.y, m_Position.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans );

	// ���[���h�}�g���b�N�X��ݒ�
	device->SetTransform( D3DTS_WORLD, &m_mtxWorld );

	// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
	device->SetStreamSource( 0, m_pVtxBuffer, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

	// �e�N�X�`���̐ݒ�
	device->SetTexture( 0,m_pTexture );

	// �|���S���̕`��
	device->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
							( 0 * 4 ),								// �`�悷��ŏ��̒��_
							2 );										// �`�悷��v���~�e�B�u��
		

	// �����_�[�X�e�[�g�̐ݒ���f�t�H���g�ɖ߂��B
	device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// �f�t�H���g�ɖ߂��B
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// �f�t�H���g�ɖ߂��B

	// ���C�g�_��
	device->SetRenderState( D3DRS_LIGHTING, TRUE );

}
//=============================================================================
//  �֐����@�FUpdate
//  �@�\�T�v�F3D�̍X�V����
//  �߂�l�@�F
//=============================================================================
void CSceneBillboard::Update(void)
{

}
//=============================================================================
//  �֐����@�FUninit
//  �@�\�T�v�FCSceneBillboard�̏I������
//  �߂�l�@�F
//=============================================================================
void CSceneBillboard::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}