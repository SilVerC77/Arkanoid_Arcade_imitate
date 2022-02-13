/**
* @file CQuadPolygon.cpp
* @brief ƒ|ƒŠƒSƒ“EƒNƒ‰ƒX
* @author DŒË@Šì—²
* @date “ú•ti2018.07.27j
*/

#include "stdafx.h"
#include "CQuadPolygon.h"

/**
* @fn std::unique_ptr<CQuadPolygon> CQuadPolygon::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief ƒCƒ“ƒXƒ^ƒ“ƒX‚ð¶¬‚µ‰Šú‰» yƒNƒ‰ƒXƒƒ\ƒbƒhz
* @param pDevice_			ƒfƒoƒCƒX
* @param pDeviceContext_	ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
* @param viewPort_[]		ƒrƒ…[ƒ|[ƒg
* @param shaderName_		ƒVƒF[ƒ_[ƒvƒƒOƒ‰ƒ€
* @param position_			ƒEƒBƒ“ƒhƒE‚ÌˆÊ’u
* @param size_				ƒXƒvƒ‰ƒCƒg‚Ì‘å‚«‚³
* @param texels			ƒeƒNƒZƒ‹‚Ì”z—ñ
* @return					CQuadPolygon‚Ìƒ†ƒj[ƒNƒ|ƒCƒ“ƒ^
*/
std::unique_ptr<CQuadPolygon> CQuadPolygon::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	std::unique_ptr<CQuadPolygon> object = unique_ptr<CQuadPolygon>(new CQuadPolygon());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels);
	return object;
}

/**
* @fn void CQuadPolygon::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief ƒCƒ“ƒXƒ^ƒ“ƒX‚ð‰Šú‰»
* @param pDevice_			ƒfƒoƒCƒX
* @param pDeviceContext_	ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
* @param viewPort_[]		ƒrƒ…[ƒ|[ƒg
* @param shaderName_		ƒVƒF[ƒ_[ƒvƒƒOƒ‰ƒ€
* @param position_			ƒEƒBƒ“ƒhƒE‚ÌˆÊ’u
* @param size_				ƒXƒvƒ‰ƒCƒg‚Ì‘å‚«‚³
* @param texels			ƒeƒNƒZƒ‹‚Ì”z—ñ
* @return					–³‚µ
*/
void CQuadPolygon::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	m_damage = FALSE;
	m_pDeviceContext = pDeviceContext_;	//!< ƒŒƒ“ƒ_ƒŠƒ“ƒO‚É•K—v@ƒŽÀs’†‚É•Ï‰»‚µ‚È‚¢„
	m_viewPort[0] = viewPort_[0];		//!< ƒŒƒ“ƒ_ƒŠƒ“ƒO‚É•K—v@ƒŽÀs’†‚É•Ï‰»‚µ‚È‚¢„
	m_originalSize = size_;
	m_VBSize = size_;
	m_active = TRUE;
	m_state = eWaiting;
	m_position.setup({ position_.x, position_.y, position_.z, 0.0f }, 0.0f, 0.0f, 0.0f, XMFLOAT3(1.0f, 1.0f, 1.0f));	//!< ˆÊ’u

	// ƒfƒtƒHƒ‹ƒgƒuƒŒƒ“ƒhƒXƒe[ƒg
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	/*
	blendDesc.AlphaToCoverageEnable = TRUE;						//!< ƒ}ƒ‹ƒ`ƒTƒ“ƒvƒŠƒ“ƒO‚Å•`‰æƒ^[ƒQƒbƒg‚Éƒ¿’l‚ðŽg—p‚·‚é
	blendDesc.IndependentBlendEnable = FALSE;					//!< RenderTarget[0]‚Ì‚ÝŽg—p‚·‚é
	blendDesc.RenderTarget[0].BlendEnable = FALSE;				//!< ƒuƒŒƒ“ƒfƒBƒ“ƒO‚Í—LŒø
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;		//!< ƒ\[ƒX‚ÌRGB’l‚ð‘I‘ð
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;		//!< ƒfƒBƒXƒeƒBƒl[ƒVƒ‡ƒ“‚ÌRGB’l‚ð‘I‘ð
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;		//!< RGB’l‚ÌƒuƒŒƒ“ƒhÝ’è src + dest
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;	//!< ƒ\[ƒX‚Ìƒ¿’l‚ð‘I‘ð@u_COLORv‚ÅI‚í‚é’l‚Í‘I‘ð•s‰Â
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;//!< ƒfƒBƒXƒeƒBƒl[ƒVƒ‡ƒ“‚Ìƒ¿’l‚ð‘I‘ð@u_COLORv‚ÅI‚í‚é’l‚Í‘I‘ð•s‰Â
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;//!< ƒ¿’l‚ÌƒuƒŒƒ“ƒhÝ’è
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;	//!< RGB’l‚Ì‚¤‚¿A‘‚«ž‚Þ’lAuD3D11_COLOR_WRITE_ENABLE—ñ‹“Œ^v‚Ì‘g‚Ý‡‚í‚¹
	*/

	// ¾ËÆÄºúÓ»µE°ªÀ» ¼³Á¤ÇÕ´Ï´Ù.
	blendDesc.RenderTarget[0].BlendEnable = FALSE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;// INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	pDevice_->CreateBlendState(&blendDesc, &m_pDefaultBlendState);

	// ƒAƒ‹ƒtƒ@ƒuƒŒƒ“ƒhƒXƒe[ƒg
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	// ¾ËÆÄºúÓ»µE°ªÀ» ¼³Á¤ÇÕ´Ï´Ù.
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	pDevice_->CreateBlendState(&blendDesc, &m_pAlphaBlendState);


	createVertexShader(pDevice_, shaderName_);		//!<’¸“_EƒVƒF[ƒ_‚Ìì¬
	createVertexInputLayout(pDevice_);					//!<’¸“_ƒCƒ“ƒvƒbƒgƒŒƒCƒAƒEƒg‚ðì¬
	createPixelShader(pDevice_, shaderName_);		//!<ƒsƒNƒZƒ‹EƒVƒF[ƒ_‚Ìì¬
	createVertexBuffer(pDevice_, size_, texels);	//!<’¸“_ƒoƒbƒtƒ@[ì¬
	createConstBuffer(pDevice_);								//!<’è”ƒoƒbƒtƒ@ì¬
}

void CQuadPolygon::createVertexShader(ID3D11Device* pDevice_, LPCWSTR shaderName_)
{
	HRESULT hr;
	ID3DBlob* pErrors = NULL;
	/**
	* hlslƒtƒ@ƒCƒ‹“Ç‚Ýž‚Ý ƒuƒƒuì¬@ƒuƒƒu‚Æ‚ÍƒVƒF[ƒ_[‚Ì‰ò‚Ý‚½‚¢‚È‚à‚ÌBXXƒVƒF[ƒ_[‚Æ‚µ‚Ä“Á’¥‚ðŽ‚½‚È‚¢BŒã‚ÅŠeŽíƒVƒF[ƒ_[‚É¬‚è“¾‚é
	*/
	hr = D3DCompileFromFile(
		shaderName_,	 //!< ƒtƒ@ƒCƒ‹–¼
		NULL,			 //!< ƒ}ƒNƒ’è‹`(‚È‚µ)
		NULL,			 //!< ƒCƒ“ƒNƒ‹[ƒhEƒtƒ@ƒCƒ‹’è‹`(‚È‚µ)
		"VS",			 //!< uVSŠÖ”v‚ªƒVƒF[ƒ_‚©‚çŽÀs‚³‚ê‚é
		"vs_5_0",		 //!< ’¸“_ƒVƒF[ƒ_
		0,				 //!< ƒRƒ“ƒpƒCƒ‹EƒIƒvƒVƒ‡ƒ“
		0,				 //!< ƒGƒtƒFƒNƒg‚ÌƒRƒ“ƒpƒCƒ‹EƒIƒvƒVƒ‡ƒ“(‚È‚µ)
		&m_pBlobVS,		 //!< ƒRƒ“ƒpƒCƒ‹‚³‚ê‚½ƒoƒCƒgEƒR[ƒh
		&pErrors);		 //!< ƒGƒ‰[ƒƒbƒZ[ƒW

	SAFE_RELEASE(pErrors);
	if (FAILED(hr))
	{
		TCHAR   str[256];
		wsprintf(str, L"CQuadPolygon::init HLSL (VS)“Ç‚Ýž‚ÝŽ¸”s %s", shaderName_);
		throw str;
	}
	/**
	* ƒuƒƒu‚©‚ç’¸“_ƒVƒF[ƒ_[ì¬
	*/
	hr = pDevice_->CreateVertexShader(
		m_pBlobVS->GetBufferPointer(),	//!< ƒoƒCƒgEƒR[ƒh‚Ö‚Ìƒ|ƒCƒ“ƒ^
		m_pBlobVS->GetBufferSize(),		//!< ƒoƒCƒgEƒR[ƒh‚Ì’·‚³
		NULL,
		&m_pVertexShader);				//!< ’¸“_ƒVƒF[ƒ_‚ðŽó‚¯Žæ‚é•Ï”
	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pBlobVS);			//!< ƒoƒCƒgEƒR[ƒh‚ð‰ð•ú
		throw L"CQuadPolygon::init ’¸“_ƒVƒF[ƒ_[ì¬Ž¸”s";
	}
}

void CQuadPolygon::createVertexInputLayout(ID3D11Device* pDevice_)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//!< ƒVƒOƒlƒ`ƒƒ
			0,								//!< ¬•ª‚ÌƒZƒ}ƒ“ƒeƒBƒbƒNEƒCƒ“ƒfƒbƒNƒX”Ô†
			DXGI_FORMAT_R32G32B32_FLOAT,	//!< ƒGƒŒƒƒ“ƒg‚ÌƒtƒH[ƒ}ƒbƒg
			0,								//!< “ü—ÍƒXƒƒbƒg”Ô†
			0,								//!< æ“ª‚Ü‚Å‚ÌƒIƒtƒZƒbƒg’liƒoƒCƒg”j
			D3D11_INPUT_PER_VERTEX_DATA,	//!< “ü—Íƒf[ƒ^‚ÍŠe’¸“_‚Ìƒf[ƒ^
			0								//!< ƒCƒ“ƒXƒ^ƒ“ƒX–ˆ‚ÌŒJ‚è•Ô‚µ‰ñ”
		},
		{
			"TEXCOORD",						//!< ƒVƒOƒlƒ`ƒƒ
			0,								//!< ¬•ª‚ÌƒZƒ}ƒ“ƒeƒBƒbƒNEƒCƒ“ƒfƒbƒNƒX”Ô†
			DXGI_FORMAT_R32G32_FLOAT,		//!< ƒGƒŒƒƒ“ƒg‚ÌƒtƒH[ƒ}ƒbƒg
			0,								//!< “ü—ÍƒXƒƒbƒg”Ô†
			sizeof(XMFLOAT3),				//!< æ“ª‚Ü‚Å‚ÌƒIƒtƒZƒbƒg’liƒoƒCƒg”j
			D3D11_INPUT_PER_VERTEX_DATA,	//!< “ü—Íƒf[ƒ^‚ÍŠe’¸“_‚Ìƒf[ƒ^
			0								//!< ƒCƒ“ƒXƒ^ƒ“ƒX–ˆ‚ÌŒJ‚è•Ô‚µ‰ñ”
		}
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	/**
	* ’¸“_ƒCƒ“ƒvƒbƒgƒŒƒCƒAƒEƒg‚ðì¬
	*/
	if (FAILED(pDevice_->CreateInputLayout(layout, numElements, m_pBlobVS->GetBufferPointer(), m_pBlobVS->GetBufferSize(), &m_pInputLayout)))
		throw L"CQuadPolygon::init ’¸“_ƒCƒ“ƒvƒbƒgƒŒƒCƒAƒEƒgì¬Ž¸”s";
}

void CQuadPolygon::createPixelShader(ID3D11Device* pDevice_, LPCWSTR shaderName_)
{
	HRESULT hr;
	ID3DBlob* pErrors = NULL;
	/**
	* ƒuƒƒu‚©‚çƒsƒNƒZƒ‹ƒVƒF[ƒ_[ì¬
	*/
	hr = D3DCompileFromFile(
		shaderName_,	//!< ƒtƒ@ƒCƒ‹–¼
		NULL,			//!< ƒ}ƒNƒ’è‹`(‚È‚µ)
		NULL,			//!< ƒCƒ“ƒNƒ‹[ƒhEƒtƒ@ƒCƒ‹’è‹`(‚È‚µ)
		"PS",			//!< uPSŠÖ”v‚ªƒVƒF[ƒ_‚©‚çŽÀs‚³‚ê‚é
		"ps_5_0",		//!< ƒsƒNƒZƒ‹EƒVƒF[ƒ_
		0,				//!< ƒRƒ“ƒpƒCƒ‹EƒIƒvƒVƒ‡ƒ“
		0,				//!< ƒGƒtƒFƒNƒg‚ÌƒRƒ“ƒpƒCƒ‹EƒIƒvƒVƒ‡ƒ“(‚È‚µ)
		&m_pBlobVS,		//!< ƒRƒ“ƒpƒCƒ‹‚³‚ê‚½ƒoƒCƒgEƒR[ƒh
		&pErrors);		//!< ƒGƒ‰[ƒƒbƒZ[ƒW

	SAFE_RELEASE(pErrors);
	if (FAILED(hr))
	{
		TCHAR   str[256];
		wsprintf(str, L"CQuadPolygon::init HLSL (PS)“Ç‚Ýž‚ÝŽ¸”s %s", shaderName_);
		throw str;
	}
	hr = pDevice_->CreatePixelShader(
		m_pBlobVS->GetBufferPointer(),	//!< ƒoƒCƒgEƒR[ƒh‚Ö‚Ìƒ|ƒCƒ“ƒ^
		m_pBlobVS->GetBufferSize(),		//!< ƒoƒCƒgEƒR[ƒh‚Ì’·‚³
		NULL,
		&m_pPixelShader);				//!< ƒsƒNƒZƒ‹EƒVƒF[ƒ_‚ðŽó‚¯Žæ‚é•Ï”
	SAFE_RELEASE(m_pBlobVS);				//!< ƒoƒCƒgEƒR[ƒh‚ð‰ð•ú
	if (FAILED(hr))
		throw L"CQuadPolygon::init ƒsƒNƒZƒ‹ƒVƒF[ƒ_[ì¬Ž¸”s";
}

void CQuadPolygon::createVertexBuffer(ID3D11Device* pDevice_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	m_VBLeftTop = { 0.0f - (size_.x / 2.0f), 0.0f - (size_.y / 2.0f) };
	m_VBRightBottom = { 0.0f + (size_.x / 2.0f), 0.0f + (size_.y / 2.0f) };
	m_texels = texels;
	for (size_t i = 0; i < texels.size(); i++)
	{
		VertexWithTex<XMFLOAT3> vertices[] =
		{
		{ XMFLOAT3(m_VBLeftTop.x,		m_VBLeftTop.y,		0),texels[i].v1 },	//!<’¸“_1
		{ XMFLOAT3(m_VBLeftTop.x,		m_VBRightBottom.y,	0),texels[i].v2 },	//!<’¸“_2
		{ XMFLOAT3(m_VBRightBottom.x,	m_VBLeftTop.y,		0),texels[i].v3 },	//!<’¸“_3
		{ XMFLOAT3(m_VBRightBottom.x,	m_VBRightBottom.y,	0),texels[i].v4 }		//!<’¸“_4	
		};

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DYNAMIC; //!< D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VertexWithTex<XMFLOAT3>) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ID3D11Buffer* pVB;
		initData.pSysMem = vertices;
		if (FAILED(pDevice_->CreateBuffer(&bd, &initData, &pVB)))
		{
			throw L"CQuadPolygon::init ’¸“_ƒoƒbƒtƒ@ì¬Ž¸”s";
		}
		m_pVertexBuffer.push_back(pVB);
	}

}
void CQuadPolygon::createConstBuffer(ID3D11Device* pDevice_)
{
	D3D11_BUFFER_DESC cb;
	cb.Usage = D3D11_USAGE_DYNAMIC;				 //!< “®“I(ƒ_ƒCƒiƒ~ƒbƒN)Žg—p–@
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	 //!< ’è”ƒoƒbƒtƒ@
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	 //!< CPU‚©‚ç‘‚«ž‚Þ
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	cb.ByteWidth = sizeof(ShaderGlobal_0);						//!< ƒoƒbƒtƒ@EƒTƒCƒY
	if (FAILED(pDevice_->CreateBuffer(&cb, NULL, &m_pConstantBuffer))) //!< ’è”ƒoƒbƒtƒ@‚Ìì¬@‚±‚±‚Å‚Í•ÏŠ·s—ñ“n‚µ—p
	{
		throw L"CQuadPolygon::init ’è”ƒoƒbƒtƒ@ì¬Ž¸”s";
	}
}

CQuadPolygon::CQuadPolygon()
{
}

CQuadPolygon::~CQuadPolygon()
{
}

/**
* @fn void CQuadPolygon::computeMatrixFromPos (void)
* @brief ƒ[ƒ‹ƒhs—ñ‚ð‹‚ß‚é
* @param					–³‚µ
* @param					–³‚µ
* @return					–³‚µ
*/
void CQuadPolygon::computeMatrixFromPos(void)
{
	XMMATRIX scale = XMMatrixScaling(m_position.scale.x, m_position.scale.y, m_position.scale.z);
	XMMATRIX pitch = XMMatrixRotationX(XMConvertToRadians(m_position.pitch));
	XMMATRIX yaw = XMMatrixRotationY(XMConvertToRadians(m_position.yaw));
	XMMATRIX roll = XMMatrixRotationZ(XMConvertToRadians(m_position.roll));
	XMMATRIX trans = XMMatrixTranslation(getPos().x, getPos().y, getPos().z);
	XMMATRIX finalWorld = scale * pitch * yaw * roll * trans;

	XMStoreFloat4x4(&m_matScale, scale);
	XMStoreFloat4x4(&m_matPitch, pitch);
	XMStoreFloat4x4(&m_matYaw, yaw);
	XMStoreFloat4x4(&m_matRoll, roll);
	XMStoreFloat4x4(&m_matTran, trans);
	XMStoreFloat4x4(&m_mFinalWorld, finalWorld);
}

/**
* @fn void CQuadPolygon::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t texelIndex_, XMFLOAT4 diffuse_)
* @brief ƒŒƒ“ƒ_ƒŠƒ“ƒO
* @param matView_	ƒrƒ…[s—ñ
* @param matProj_	ƒvƒƒWƒFƒNƒVƒ‡ƒ“s—ñ
* @param texelIndex_	ƒeƒNƒZƒ‹EƒCƒ“ƒfƒbƒNƒX
* @param diffuse_	ƒfƒBƒtƒ…[ƒY
* @return			–³‚µ
*/
void CQuadPolygon::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_, size_t texelIndex_, XMFLOAT4 diffuse_) {
	if (!m_active)
	{
		return;
	}

	computeMatrixFromPos();

	//! ƒVƒF[ƒ_[@’è”ƒoƒbƒtƒ@
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(m_pDeviceContext->Map(
		m_pConstantBuffer,			//!< ƒ}ƒbƒv‚·‚éƒŠƒ\[ƒX
		0, 							//!< ƒTƒuƒŠƒ\[ƒX‚ÌƒCƒ“ƒfƒbƒNƒX”Ô†
		D3D11_MAP_WRITE_DISCARD,	//!< ‘‚«ž‚ÝƒAƒNƒZƒX
		0,
		&pData)))					//!< ƒf[ƒ^‚Ì‘‚«ž‚Ýæƒ|ƒCƒ“ƒ^
	{
		ShaderGlobal_0 sg;
		XMStoreFloat4x4(&sg.matWVP, XMLoadFloat4x4(&m_mFinalWorld) * XMLoadFloat4x4(&matView_) * XMLoadFloat4x4(&matProj_));
		XMStoreFloat4x4(&sg.matWVP, XMMatrixTranspose(XMLoadFloat4x4(&sg.matWVP)));
		sg.diffuse = diffuse_;
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(ShaderGlobal_0));

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);									//!< ’¸“_ƒCƒ“ƒvƒbƒgƒŒƒCƒAƒEƒg‚ðƒZƒbƒg
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//!< ƒvƒŠƒ~ƒeƒBƒuEƒgƒ|ƒƒW[‚ðƒZƒbƒg
	UINT stride = sizeof(VertexWithTex<XMFLOAT3>);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer[texelIndex_], &stride, &offset);//!< ’¸“_ƒoƒbƒtƒ@[‚ðƒZƒbƒg
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);							//!< Žg—p‚·‚éƒVƒF[ƒ_[‚Ì“o˜^@ieffect‚ÌhƒeƒNƒjƒbƒNh‚É‘Š“–j
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< VS‚É’è”ƒoƒbƒtƒ@‚ðÝ’è
	m_pDeviceContext->RSSetViewports(1, m_viewPort);									//!< RS‚Éƒrƒ…[ƒ|[ƒg‚ðÝ’è
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);								//!< PS‚ÉƒsƒNƒZƒ‹EƒVƒF[ƒ_‚ðÝ’è
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< PS‚É’è”ƒoƒbƒtƒ@‚ðÝ’è
																						//! ƒTƒ“ƒvƒ‰[‚ÆƒeƒNƒXƒ`ƒƒ[‚ÌÝ’è
	callbackTextureProc_(m_pDeviceContext);												//! ƒTƒ“ƒvƒ‰[‚ÆƒeƒNƒXƒ`ƒƒ[‚Í—˜—pŽÒ‚Å—pˆÓ‚·‚é
	m_pDeviceContext->Draw(4, 0);														//!<  ƒvƒŠƒ~ƒeƒBƒu‚ðƒŒƒ“ƒ_ƒŠƒ“ƒO
}

/**
* @fn BOOL CQuadPolygon::collision(XMFLOAT4 pos_, FLOAT range_)
* @brief Õ“Ë
* @param pos_	ˆÊ’u
* @param range_	Õ“Ë‚Ì”ÍˆÍ
* @return		Õ“Ë
*/
BOOL CQuadPolygon::collision(XMFLOAT4 pos_, FLOAT range_)
{
	return collision(pos_, getPos(), range_);
}

BOOL CQuadPolygon::collision(XMFLOAT2 pos_, FLOAT range_)
{
	XMFLOAT4 pos = getPos();
	FLOAT dist2 =
		(pos_.x - pos.x) * (pos_.x - pos.x) +
		(pos_.y - pos.y) * (pos_.y - pos.y);
	return dist2 <= (range_ * range_);
}

BOOL CQuadPolygon::collision(XMFLOAT2 pos_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float myLeft = myPos.x - (mySize.x / 2.0f);
	float myTop = myPos.y + (mySize.y / 2.0f);
	float myRight = myPos.x + (mySize.x / 2.0f);
	float myBottom = myPos.y - (mySize.y / 2.0f);

	bool ret = (myLeft <= pos_.x && pos_.x <= myRight) && (myBottom <= pos_.y && pos_.y <= myTop);
	return ret;
}

/**
* @fn BOOL CQuadPolygon::collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_)
* @brief Õ“Ë
* @param pos1_	ˆÊ’u
* @param pos2_	ˆÊ’u
* @param range_	Õ“Ë‚Ì”ÍˆÍ
* @return		Õ“Ë
*/
BOOL CQuadPolygon::collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_)
{
	FLOAT dist2 =
		(pos1_.x - pos2_.x) * (pos1_.x - pos2_.x) +
		(pos1_.y - pos2_.y) * (pos1_.y - pos2_.y) +
		(pos1_.z - pos2_.z) * (pos1_.z - pos2_.z);

	return dist2 <= (range_ * range_);
}
BOOL CQuadPolygon::collision(CQuadPolygon* target_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float myLeft = myPos.x - (mySize.x / 2.0f);
	float myTop = myPos.y + (mySize.y / 2.0f);
	float myRight = myPos.x + (mySize.x / 2.0f);
	float myBottom = myPos.y - (mySize.y / 2.0f);
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (myLeft < targetRight&& myTop > targetBottom && myRight > targetLeft && myBottom < targetTop);
}
BOOL CQuadPolygon::collisionBottom(CQuadPolygon* target_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float colLeft = myPos.x - (mySize.x / 2.0f);
	float colTop = myPos.y - (mySize.y / 2.0f) + 1.0f;
	float colRight = myPos.x + (mySize.x / 2.0f);
	float colBottom = myPos.y - (mySize.y / 2.0f) - 30.0f;
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (colLeft < targetRight&& colTop > targetBottom && colRight > targetLeft && colBottom < targetTop);
}
BOOL CQuadPolygon::collisionTop(CQuadPolygon* target_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float colLeft = myPos.x - (mySize.x / 2.0f);
	float colTop = myPos.y + (mySize.y / 2.0f) + 0.01f;
	float colRight = myPos.x + (mySize.x / 2.0f);
	float colBottom = myPos.y + (mySize.y / 2.0f) - 0.01f;
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (colLeft < targetRight&& colTop > targetBottom && colRight > targetLeft && colBottom < targetTop);
}
BOOL CQuadPolygon::collisionLeft(CQuadPolygon* target_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float colLeft = myPos.x - (mySize.x / 2.0f) - 5.0f;
	float colTop = myPos.y + (mySize.y / 2.0f) - 1.0f;
	float colRight = myPos.x - (mySize.x / 2.0f) + 5.0f;
	float colBottom = myPos.y - (mySize.y / 2.0f) + 1.0f;
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (colLeft < targetRight&& colTop > targetBottom && colRight > targetLeft && colBottom < targetTop);
}
BOOL CQuadPolygon::collisionRight(CQuadPolygon* target_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float colLeft = myPos.x + (mySize.x / 2.0f) - 5.0f;
	float colTop = myPos.y + (mySize.y / 2.0f) - 1.0f;
	float colRight = myPos.x + (mySize.x / 2.0f) + 5.0f;
	float colBottom = myPos.y - (mySize.y / 2.0f) + 1.0f;
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (colLeft < targetRight&& colTop > targetBottom && colRight > targetLeft && colBottom < targetTop);
}

BOOL CQuadPolygon::collisionOffset(CQuadPolygon* target_, XMFLOAT4 offset_, XMFLOAT2 scale_)
{

	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	myPos.x += offset_.x;
	myPos.y += offset_.y;
	myPos.z += offset_.z;
	myPos.w += offset_.w;
	float myLeft = myPos.x - (mySize.x * scale_.x);
	float myTop = myPos.y + (mySize.y * scale_.y);
	float myRight = myPos.x + (mySize.x * scale_.x);
	float myBottom = myPos.y - (mySize.y * scale_.y);
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (myLeft < targetRight&& myTop > targetBottom && myRight > targetLeft && myBottom < targetTop);
}
//15---------------------------------------------------------------------------------------------------
eDirection CQuadPolygon::collisionTest(CQuadPolygon* _target)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float myLeft = myPos.x - (mySize.x / 2.0f);
	float myTop = myPos.y + (mySize.y / 2.0f);
	float myRight = myPos.x + (mySize.x / 2.0f);
	float myBottom = myPos.y - (mySize.y / 2.0f);
	XMFLOAT4 targetPos = _target->getPos();
	XMFLOAT2 targetSize = _target->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);
	//接触してない長さ
	XMFLOAT2 untouch = { 0.0f, 0.0f };
	untouch.x = abs((myRight - targetLeft) - (targetRight - myLeft));
	untouch.y = abs((myTop - targetBottom) - (targetTop - myBottom));
	//接触した範囲
	XMFLOAT2 touch = { 0.0f, 0.0f };
	touch.x = mySize.x + targetSize.x - untouch.x;
	touch.y = mySize.y + targetSize.y - untouch.y;
	//重ねた範囲の長さで長いほうは当たった側
	if (touch.x < touch.y) {
		if (myPos.x < targetPos.x) return eRight;
		else					   return eLeft;
	}
	else {
		if (myPos.y < targetPos.y) return eUp;
		else				       return eDown;
	}
}
//^^---------------------------------------------------------------------------------------------------


/**
* @fn void CQuadPolygon::release()
* @brief ƒŠƒŠ[ƒX
* @param	–³‚µ
* @return	–³‚µ
*/
void CQuadPolygon::release()
{
	/**
	*  •K‚¸¶¬‚µ‚½‚Ì‚Æ‹t‚Ì‡”Ô‚ÅƒŠƒŠ[ƒX
	*/
	SAFE_RELEASE(m_pConstantBuffer);
	for (size_t i = 0; i < m_pVertexBuffer.size(); i++)
	{
		SAFE_RELEASE(m_pVertexBuffer[i]);
	}
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexShader);
}
