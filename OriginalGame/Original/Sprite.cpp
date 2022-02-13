#include "stdafx.h"
#include "COriginalGameApp.h"
#include "GameResource.h"
#include "UV.h"

/**
 * 関数名 : createSprite()
 * 処理内容 : 指定されたパスにある画像を、指定されたサイズで作成する
 * 引数 :	path_		画像のあるパス
 *			width_		作成する画像の幅
 *			height_		作成する画像の高さ
 * 戻り値 : 作成した画像を管理するオブジェクト
 */
CPicture* COriginalGameApp::createSprite(LPCWSTR path_, float width_, float height_)
{
	vector <QuadrangleTexel>  singleTexels =
	{
		QuadrangleTexel{ { 0.0, 1.0 },{ 0.0, 0.0 },{ 1.0, 1.0 },{ 1.0, 0.0 } }	//!< 指定するUV座標の配列が一つの配列
	};
	XMFLOAT2 spriteSize = { width_, height_ };
	CPicture* object = NULL;
	//
	if (path_ == Tex_Block) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsBlock);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Frame_Break) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsBreak);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Item) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsItem);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Enemy) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsEnemy);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Frame_Exit) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsExit);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Enemy_Explosion) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsExplode);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Boss) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsBoss);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Boss_Bullet) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsBossBullet);				//!< 指定するUV座標の配列
	}
	else if (path_ == Tex_Header) {
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelsHeader);				//!< 指定するUV座標の配列
	}
	else {
		// 基本的な作成
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
			spriteSize,					//スプライトのサイズ
			singleTexels);				//!< 指定するUV座標の配列
	}
	return object;
}

CFont* COriginalGameApp::createFont(LPCWSTR path_, int digits_, float width_, float height_)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	if (path_ == Tex_Alphabet) {
		objects = CFont::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelAlphabet,				//指定するUV座標の配列
			digits_);					//桁数
	}

	else {
		objects = CFont::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },	//スプライトの位置
			spriteSize,					//スプライトのサイズ
			kTexelNumbers,				//指定するUV座標の配列
			digits_);					//桁数
	}
	return objects;
}
