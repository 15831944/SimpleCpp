#include "StdAfx.h"
#include "3dgraphicitem.h"
#include "3dGraphics.h"
#include <windows.h>
#include "D3dPresenter.h"

#define TRACE
 
C3dGraphicItem::C3dGraphicItem(C3dGraphics *p3dGraph, int nTexturePixW, int nTexturePixH )
: m_p3dGraphic(p3dGraph)
, m_pRendTexture(0)
, m_pVertexBuffer(0)
, m_pSysTexture(0)
, m_fAngleX(0)
, m_fAngleY(0)
, m_fAngleZ(0)
, m_fX(0*LOG_UNIT_SIZE)
, m_fY(0)
, m_fZ(0)
, m_fSizeX(1*LOG_UNIT_SIZE)
, m_fSizeY(1*LOG_UNIT_SIZE)
 ,m_fSizeZ(1*LOG_UNIT_SIZE)
 , m_nTextureXPix(nTexturePixW)
 , m_nTextureYPix(nTexturePixH)
 , m_fAlpha(1)
 , m_nPrimitiveCount(2)
{
	//m_strId.append("item");
	memset(&m_hLock, 0, sizeof(m_hLock));
	InitializeCriticalSection(&m_hLock);
}

C3dGraphicItem::~C3dGraphicItem(void)
{
	DeleteCriticalSection(&m_hLock);
	if (m_pRendTexture)
	{
		m_pRendTexture->Release();
		m_pRendTexture = NULL;
	}
	if (m_pSysTexture)
	{
		m_pSysTexture->Release();
		m_pSysTexture = NULL;
	}
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}


}
int C3dGraphicItem::Create(float fX, float fY, float fZ)
{
	if (!m_p3dGraphic)
	{
		return S_FALSE;
	}
	m_fX = fX;
	m_fY = fY;
	m_fZ = fZ;
	HRESULT hr = S_OK;
	IDirect3DDevice9* pDev = m_p3dGraphic->m_pGraphicEngine->GetD3DDevice9();

	if (!pDev)
		return -1;
	hr = D3DXCreateTexture(	
		pDev,
		m_nTextureXPix,
		m_nTextureYPix,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,
		D3DPOOL_SYSTEMMEM,
		&m_pSysTexture);
	if (FAILED(hr))
	{
		TRACE("����sys ����ʧ��\n");
		return S_FALSE;
	}
	else
	{
		TRACE("����sys ����ɹ�\n");
	}
#if 1
	hr = D3DXCreateTexture(	
		pDev,
		m_nTextureXPix,
		m_nTextureYPix,
		0,
		D3DUSAGE_RENDERTARGET ,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pRendTexture);
	if (FAILED(hr))
	{
		TRACE("���� ��Ⱦ���� ʧ��\n");
		return S_FALSE;
	}
	else
	{
		TRACE("���� ��Ⱦ���� �ɹ�\n");
	}
	int nMipmapLevels = 0;
	nMipmapLevels =  m_pRendTexture->GetLevelCount();
#else
	hr = ::D3DXCreateTextureFromFile( pDev, "1.jpg", &m_pRendTexture );
	if (FAILED(hr))
	{
		TRACE("����ͼƬ����ͼʧ��\n");
		return S_FALSE;
	}
	else
	{
		TRACE("����ͼƬ����ͼ�ɹ�\n");
	}
	#endif
	
	//
	D3DLOCKED_RECT	d3dLock;
	//D3DLOCKED_RECT	d3dLockF;
	hr = m_pSysTexture->LockRect(0, &d3dLock, NULL, D3DLOCK_DISCARD);
	//hr = m_pFileTexture->LockRect(0, &d3dLockF, NULL, D3DLOCK_DISCARD);

	//memcpy(d3dLock.pBits, d3dLockF.pBits,  m_nYPix*m_nXPix*4);
	memset(d3dLock.pBits, 0, m_nTextureYPix*m_nTextureXPix*4);
	//memcpy(d3dLock.pBits, bmp.bmBits, m_nTextureYPix*m_nTextureXPix*4);
	unsigned char * pPix = (unsigned char*)d3dLock.pBits;
	int nW = m_nTextureXPix*4;
	int nLinePos = 0;
	unsigned char *pPixLine = pPix;
	for (int j=0; j<m_nTextureYPix/2; j++)
	{
		for (int i=0; i<nW; i+=4)
		{
			pPixLine[i+3] = 0xff;
			pPixLine[i+1] = 0xff;
		}
		nLinePos += nW;
		pPixLine += nW;
	}

	m_pSysTexture->UnlockRect(0);
	//m_pFileTexture->UnlockRect(0);

/*
 	CComPtr<IDirect3DSurface9> pSysSurface, pSurface;
 	m_pSysTexture->GetSurfaceLevel(0, &pSysSurface);
 	m_pRTTexture->GetSurfaceLevel(0, &pSurface);
	m_pDMD3D9->GetD3DDevice9()->StretchRect( pSysSurface, 
											NULL,
											pSurface, NULL,
											D3DTEXF_NONE ) ;
											*/
	hr  = pDev->UpdateTexture(m_pSysTexture, m_pRendTexture);
	if (FAILED(hr))
	{
		TRACE("���� ��Ⱦ���� ʧ��\n");
		return S_FALSE;
	}
	else
	{
		TRACE("���� ��Ⱦ���� �ɹ�\n");
	}

	InitGeometry();
	return S_OK;
}
 int C3dGraphicItem::SetGeometry(float x, float y, float z, 
						float xangle, float yangle, float zangle,
						float cx, float cy, float cz)
 {
	 m_fX = x;
	 m_fY = y;
	 m_fZ = z;
	 m_fAngleX = xangle;
	 m_fAngleY = yangle;
	 m_fAngleZ = zangle;
	 m_fSizeX = cx;
	 m_fSizeY = cy;
	 m_fSizeZ = cz;
	return S_OK;
 }
 int C3dGraphicItem::SetSize(float cx, float cy, float cz)
 {
	 m_fSizeX = cx;
	 m_fSizeY = cy;
	 m_fSizeZ = cz;
	return S_OK;
 }
 int C3dGraphicItem::SetAngle(float xAngle, float yAngle, float zAngle)
 {
	 m_fAngleX = xAngle;
	 m_fAngleY = yAngle;
	 m_fAngleZ = zAngle;
	 return S_OK;
 }
 int C3dGraphicItem::SetPos(float x, float y, float z)
 {
	 m_fX = x;
	 m_fY = y;
	 m_fZ = z;
	 return S_OK;
 }
 int C3dGraphicItem::GetPos(float &fX, float &fY, float &fZ)
 {
	 fX = m_fX;
	 fY = m_fY;
	 fZ = m_fZ;
	 return 0;
 }
 int C3dGraphicItem::GetSize(float &fCX, float &fCY, float &fCZ)
 {
	fCX = m_fSizeX;
	fCY = m_fSizeY;
	fCZ = m_fSizeZ;
	 return 0;
 }
 bool C3dGraphicItem::HitTest(float fX, float fY)
 {
	if (m_fX<fX && fX < m_fX+m_fSizeX
		&& m_fY<fY && fY < m_fY+m_fSizeY)
	{
		debug("%s, true\n", __FUNCTION__);
		return true;
	}
	debug("%s, false\n", __FUNCTION__);
	return false;
 }
 int C3dGraphicItem::Render(C3dGraphics *pGraphic)
 {
	HRESULT hr = S_OK;
	EnterCriticalSection(&m_hLock) ;
	
	IDirect3DDevice9* pDev = pGraphic->m_pGraphicEngine->GetD3DDevice9();
	if (!pDev)
	{
		LeaveCriticalSection(&m_hLock);

		return -1;
	}

	SetPos(pDev, m_fX, m_fY, m_fZ, 
		m_fAngleX, m_fAngleY, m_fAngleZ,
		m_fSizeX, m_fSizeY, m_fSizeZ);

	//�ر�...��Ȼ��Ҫ ���õƹ� ���򿴲���������
	pDev->SetRenderState( D3DRS_LIGHTING, false );


	pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDev->SetRenderState(D3DRS_SRCBLEND,   D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND,   D3DBLEND_INVSRCALPHA);
	//pDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
 	//pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	

	//pDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1); 
/*
	pDev->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1 );


	pDev->SetTextureStageState(0, D3DTSS_COLORARG1,  D3DTA_TEXTURE);
	pDev->SetTextureStageState(0, D3DTSS_COLORARG2,  D3DTA_TEXTURE);   //Ignored
	pDev->SetTextureStageState(0, D3DTSS_COLOROP,    D3DTOP_SELECTARG1);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1,  D3DTA_DIFFUSE);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG2,  D3DTA_TEXTURE);   //Ignored
	pDev->SetTextureStageState(0, D3DTSS_ALPHAOP,    D3DTOP_SELECTARG1);

	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
*/
/* ʹ�� ͼƬ��  alpha ͨ��
	// set alpha blending states
	// use alhpa in material's diffuse component for alpha
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAOP,    D3DTOP_SELECTARG1);
	// set blending factors so that alpha component determines transparency
	pDev->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
*/
	//�����ڻ�����, alpha Ҳ�����ǻ�ϳ�����
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	//ʹ�õ� appha ������ ���� alphaͨ��
	//pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// ʹ�� ������ �� ����ĳ˻� ��Ϊ���� alpha ��ֵ
	pDev->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE /*D3DTOP_SELECTARG1*/);
	// set blending factors so that alpha component determines transparency
	//pDev->SetRenderState(D3DRS_SRCBLEND,  /*D3DBLEND_SRCALPHA*/D3DBLEND_SRCCOLOR);
	//pDev->SetRenderState(D3DRS_DESTBLEND, /*D3DBLEND_INVSRCALPHA*/D3DBLEND_DESTCOLOR);
	pDev->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA/*D3DBLEND_SRCCOLOR*/);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA/*D3DBLEND_DESTCOLOR*/);
	//pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);


	
	if (   m_pRendTexture)
	{
		hr = pDev->SetTexture( 0, m_pRendTexture);
		if (FAILED(hr))
		{
			TRACE("SetTexture() false\n");
		}
		else
		{
			//TRACE("SetTexture() success\n");
		}
	}
	//�����Զ����FVF
	hr = pDev->SetFVF( D3DFVF_CUSTOMVERTEX);
	//�󶨶��㻺�������豸����Դ
	hr = pDev->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(VERTEX_CUSTOM1) );


	
	//hr = pDev->SetVertexShader( D3DFVF_CUSTOMVERTEX);
	if (FAILED(hr))
	{
		TRACE("SetFVF() false\n");
	}
	

	//����ͼԪ�����в���1ΪͼԪ��ʽ������3Ϊ��������Ŀ
	hr = pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, m_nPrimitiveCount );

	hr = pDev->SetTexture( 0, NULL );

	pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	LeaveCriticalSection(&m_hLock);

	return hr;
}
bool C3dGraphicItem::Lock()
{
	EnterCriticalSection(&m_hLock) ;

	return TRUE;
}
void C3dGraphicItem::Unlock()
{

	LeaveCriticalSection(&m_hLock);
}
HRESULT C3dGraphicItem::CreateTexture()//����ʧ֮�� ��Ҫ���´���
{

	return S_OK;
}
 HRESULT C3dGraphicItem::InitGeometry()
{

	TRACE("CD3DRenderObj::InitGeometry()\n");
	if (!m_p3dGraphic)
		return S_FALSE;
	m_nVertexPoints = 4;
	m_nPrimitiveCount = 2;
	VERTEX_CUSTOM1 verticesRect[4];
	int nAlpha = m_fAlpha*255;

	
	verticesRect[0].x = -1.0*LOG_UNIT_SIZE/2.0, verticesRect[0].y = 1.0*LOG_UNIT_SIZE/2.0, verticesRect[0].z = 0;
	verticesRect[0].color = D3DCOLOR_ARGB( nAlpha, 255, 255, 255);
	verticesRect[0].tx = 0, verticesRect[0].ty = 0;

	verticesRect[1].x = 1.0*LOG_UNIT_SIZE/2.0, verticesRect[1].y = 1.0*LOG_UNIT_SIZE/2.0, verticesRect[1].z = 0;
	verticesRect[1].color = D3DCOLOR_ARGB( nAlpha, 255, 255, 255);
	verticesRect[1].tx = 1*LOG_UNIT_SIZE, verticesRect[1].ty = 0;

	verticesRect[2].x = -1.0*LOG_UNIT_SIZE/2.0, verticesRect[2].y = -1.0*LOG_UNIT_SIZE/2.0, verticesRect[2].z = 0;
	verticesRect[2].color = D3DCOLOR_ARGB( nAlpha,255, 255, 255);
	verticesRect[2].tx = 0, verticesRect[2].ty = 1*LOG_UNIT_SIZE;

	verticesRect[3].x = 1.0*LOG_UNIT_SIZE/2.0, verticesRect[3].y = -1.0*LOG_UNIT_SIZE/2.0, verticesRect[3].z = 0;
	verticesRect[3].color = D3DCOLOR_ARGB( nAlpha, 255, 255, 255);
	verticesRect[3].tx = 1*LOG_UNIT_SIZE, verticesRect[3].ty = 1*LOG_UNIT_SIZE;
	
	/*verticesRect[0].x = 0, verticesRect[0].y = 0, verticesRect[0].z = 0;
	verticesRect[0].color = D3DCOLOR_ARGB( nAlpha, 255, 255, 255);
	verticesRect[0].tx = 0, verticesRect[0].ty = 0;

	verticesRect[1].x = 1.0, verticesRect[1].y = 0, verticesRect[1].z = 0;
	verticesRect[1].color = D3DCOLOR_ARGB( nAlpha, 255, 255, 255);
	verticesRect[1].tx = 1*LOG_UNIT_SIZE, verticesRect[1].ty = 0;

	verticesRect[2].x = 0, verticesRect[2].y = 1, verticesRect[2].z = 0;
	verticesRect[2].color = D3DCOLOR_ARGB( nAlpha,255, 255, 255);
	verticesRect[2].tx = 0, verticesRect[2].ty = 1*LOG_UNIT_SIZE;

	verticesRect[3].x = 1.0*LOG_UNIT_SIZE, verticesRect[3].y = 1.0*LOG_UNIT_SIZE, verticesRect[3].z = 0;
	verticesRect[3].color = D3DCOLOR_ARGB( nAlpha, 255, 255, 255);
	verticesRect[3].tx = 1*LOG_UNIT_SIZE, verticesRect[3].ty = 1*LOG_UNIT_SIZE;
	*/

	IDirect3DDevice9* p3dDev = m_p3dGraphic->m_pGraphicEngine->GetD3DDevice9();//m_pDMD3D9->GetD3DDevice9();
	if (p3dDev == NULL)
	{
		return S_FALSE;
	}
	//�������㻺����������ȡ�ӿ�IDirect3DVertexBuffer9��ָ��
	HRESULT hr = p3dDev->CreateVertexBuffer(
		sizeof(verticesRect), //�������ߴ�
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL );
	//�Ѷ����������붥�㻺����
	void* pVertices;
	hr = m_pVertexBuffer->Lock( 0, sizeof(verticesRect), (void**)&pVertices, 0 );
	memcpy( pVertices, verticesRect, sizeof(verticesRect) );
	hr = m_pVertexBuffer->Unlock();

	return S_OK;
}
void C3dGraphicItem::SetPos(IDirect3DDevice9 *pDev, float x, float y, float z, 
								 float xangle, float yangle, float zangle,
								 float cx, float cy, float cz)
{
	if (!pDev)
		return ;
	D3DXMATRIX MatTemp;  // ������ת����ʱ����,����
	D3DXMATRIX MatScale;
	D3DXMATRIX MatRot;   // ���յ���ת����Ӧ����pMatWorld.
	D3DXMATRIX matWorld;
	//�ѽǶȱ�ɻ���
	xangle = xangle * D3DX_PI / (double)180; //����ת�ǻ���ɻ���
	yangle = yangle * D3DX_PI / (double)180; //����ת�ǻ���ɻ���
	zangle = zangle * D3DX_PI / (double)180; //����ת�ǻ���ɻ���

	//��������Ϊ������(0,0); (2,0); (0,2); (2,2)�༭���Ͳ��������겻ͬ��
	//���������õ��ǵѿ������꣬�������� 0��0��������ʹ�õ���TEXTӳ�����꣬������0��0��������22
	x = x+cx/2.0-1.0; //ģ����00�㣬��ͼ�������Ϊͼ��ԭ�㡣������Ҫ��ͼ�ε����Ͻ���Ϊ
	y = -y-cy/2.0+1.0; //���ʱ��ͼ��λ��ԭ�㡣������ƽ�ơ���ͼ�����Ͻ�����Ļ���ϽǶ��롣
	//x = x ; 
	//y = -y ;

// 	x *= LOG_UNIT_SIZE;
// 	y *= LOG_UNIT_SIZE;
	// ʹ�ô����ҵľ��󴮽�˳������ת֮ǰ������������ռ���
	// ��λ�ý���ƽ�ơ�
	D3DXMatrixTranslation(&matWorld, x, y, z);

	D3DXMatrixScaling(&MatScale, cx, cy, cz); //����
	D3DXMatrixMultiply(&matWorld, &MatScale, &matWorld);

	D3DXMatrixIdentity(&MatRot);

	// ���ڽ��������Ӧ�����������,��ת��
	if(xangle || yangle || zangle) {
		// �������ϳ���ת����
		D3DXMatrixRotationX(&MatTemp, xangle);         // Pitch
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
		D3DXMatrixRotationY(&MatTemp, yangle);           // Yaw
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
		D3DXMatrixRotationZ(&MatTemp, zangle);          // Roll
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);

		// Ӧ����ת���󣬵õ������������
		D3DXMatrixMultiply(&matWorld, &MatRot, &matWorld);
	}
	pDev->SetTransform( D3DTS_WORLD, &matWorld );	
}
int C3dGraphicItem::Release()
{
	if (m_pRendTexture)
	{
		m_pRendTexture->Release();
		m_pRendTexture = NULL;
	}
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (m_pSysTexture)
	{
		m_pSysTexture->Release();
		m_pSysTexture = NULL;
	}

	return 0;
}
int		C3dGraphicItem::ReCreate(C3dGraphics *p3dGraphics)
{

	m_p3dGraphic = p3dGraphics;
	//
	HRESULT hRt = Create(m_fX, m_fY, m_fZ);
	
	return hRt;
}

int C3dGraphicItem::SetVisible( bool bVisible/*=true*/ )
{
	m_bVisible = bVisible;
	return 0;
}
int C3dGraphicItem::SetAlpha(float fAlpha)
{
	m_fAlpha = fAlpha;

	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
	}
	InitGeometry();

	return 0;
}

bool C3dGraphicItem::IsVisible()
{

	return m_bVisible;
}
