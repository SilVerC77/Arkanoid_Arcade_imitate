/**
* @file CPicture.h
* @brief ƒeƒNƒZƒ‹•t‚«‚ÌƒsƒNƒ`ƒƒ[EEƒNƒ‰ƒX
* @author DŒË@Šì—²
* @date “ú•ti2017.02.14j
*/
#pragma once

#include "stdafx.h"
#include "CQuadPolygon.h"
#include "CTexture.h"

/*! @class CPicture
@brief  ƒ|ƒŠƒSƒ“EƒNƒ‰ƒX
*/
class CPicture :
	public CQuadPolygon
{
	typedef CQuadPolygon super;
private:
	std::unique_ptr<CQuadPolygon>	m_pPolygon = NULL;
	std::unique_ptr<CTexture>				m_pPolygonTex = NULL;
	//	int								m_animIndex = 0;
public:
	/*
	static std::unique_ptr<CPicture> create (
		ID3D11Device*			pDevice_,		//!< ƒfƒoƒCƒX
		ID3D11DeviceContext*	pDeviceContext_,//!< ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
		D3D11_VIEWPORT			viewPort_[],	//!< ƒrƒ…[ƒ|[ƒg
		LPCWSTR					shaderName_,	//!< ƒVƒF[ƒ_[ƒvƒƒOƒ‰ƒ€
		LPCWSTR					textureName_,	//!< ‰æ‘œƒtƒ@ƒCƒ‹
		XMFLOAT4				position_,		//!< ƒEƒBƒ“ƒhƒE‚ÌˆÊ’u
		XMFLOAT2				size_,			//!< ƒXƒvƒ‰ƒCƒg‚Ì‘å‚«‚³
		std::vector<QuadrangleTexel>	texels);		//!< ƒeƒNƒZƒ‹‚Ì”z—ñ
	*/
	static CPicture* create(
		ID3D11Device* pDevice_,		//!< ƒfƒoƒCƒX
		ID3D11DeviceContext* pDeviceContext_,//!< ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
		D3D11_VIEWPORT			viewPort_[],	//!< ƒrƒ…[ƒ|[ƒg
		LPCWSTR					shaderName_,	//!< ƒVƒF[ƒ_[ƒvƒƒOƒ‰ƒ€
		LPCWSTR					textureName_,	//!< ‰æ‘œƒtƒ@ƒCƒ‹
		XMFLOAT4				position_,		//!< ƒEƒBƒ“ƒhƒE‚ÌˆÊ’u
		XMFLOAT2				size_,			//!< ƒXƒvƒ‰ƒCƒg‚Ì‘å‚«‚³
		std::vector<QuadrangleTexel>	texels);		//!< ƒeƒNƒZƒ‹‚Ì”z—ñ

	CPicture();
	~CPicture();
	virtual void init(
		ID3D11Device* pDevice_,		//!< ƒfƒoƒCƒX
		ID3D11DeviceContext* pDeviceContext_,//!< ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
		D3D11_VIEWPORT			viewPort_[],	//!< ƒrƒ…[ƒ|[ƒg
		LPCWSTR					shaderName_,	//!< ƒVƒF[ƒ_[ƒvƒƒOƒ‰ƒ€
		LPCWSTR					textureName_,	//!< ‰æ‘œƒtƒ@ƒCƒ‹
		XMFLOAT4				position_,		//!< ƒEƒBƒ“ƒhƒE‚ÌˆÊ’u
		XMFLOAT2				size_,			//!< ƒXƒvƒ‰ƒCƒg‚Ì‘å‚«‚³
		std::vector<QuadrangleTexel>	texels);		//!< ƒeƒNƒZƒ‹‚Ì”z—ñ
	virtual void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, size_t texelIndex_ = 0, XMFLOAT4 diffuse_ = { 0, 0, 0, 0 });
	void release();
	void stepAnimation();
	void setAnimation(int animIndex);
	void setAnimationRange(int animBeginIndex_, int animEndIndex_);


	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//許弘毅　追加
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	int getAnimIndex() { return (int)m_animIndex; }
};
