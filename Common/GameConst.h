/**
* @file GameConst.h
* @brief ’è”
*
* @author DŒË@Šì—²
* @date “ú•ti2017.02.14j
*/
#pragma once

#include "stdafx.h"

/**
 * ’è”
 */
#define APP_NAME L"Original Game"

 /*! @name ’è‹`ƒOƒ‹[ƒv ƒEƒCƒ“ƒhƒE
 ƒEƒCƒ“ƒhƒE‚ÉŠÖ‚·‚é’è”
 */
 /* @{ */
#define WINDOW_WIDTH	1920	//! ƒEƒBƒ“ƒhƒE•
#define WINDOW_HEIGHT	1080	//! ƒEƒBƒ“ƒhƒE‚‚³
const bool kFullScreen = TRUE;	//! ƒtƒ‹ƒXƒNƒŠ[ƒ“ƒ‚[ƒh

#define	ASPECT			((FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT)
#define WINDOW_LEFT		(-WINDOW_WIDTH / 2)
#define WINDOW_RIGHT	( WINDOW_WIDTH / 2)
#define WINDOW_TOP		( WINDOW_HEIGHT / 2)
#define WINDOW_BOTTOM	(-WINDOW_HEIGHT / 2)
const XMFLOAT2 kSpriteScreenkSize = { WINDOW_WIDTH , WINDOW_HEIGHT - 4 };
const FLOAT k1_1 = 1.0f;
const FLOAT k1_2 = 1.0f / 2;
const FLOAT k1_3 = 1.0f / 3;
const FLOAT k1_4 = 1.0f / 4;
const FLOAT k1_5 = 1.0f / 5;
const FLOAT k1_8 = 1.0f / 8;
const FLOAT k1_26 = 1.0f / 26;
/* @} */

/*! @name ’è‹`ƒOƒ‹[ƒv Shooting
ƒVƒ…[ƒeƒBƒ“ƒO‚ÅŽg—p‚·‚é’è”
*/
/* @{ */
const int kMaxHP = 7;
const XMFLOAT2 kCharSpriteSize = { 48.0f , 48.0f };
const XMFLOAT2 kBulletSize = { 16.0f , 16.0f };
const XMFLOAT2 kExplosionSize = { 80.0f , 80.0f };
const FLOAT kBullet_Left = -7.0f;
const FLOAT kBullet_Right = -7.0f + 12.0f;
const FLOAT kEnemyQuantity = 0.25f * 1.5;
const FLOAT kPlayerQuantity = 15.25f;
const int kTexelIntervalFrames = 15;
const int kIntervalShot = 64 * 4;
const int kExplosionTexelPauseFrames = 8;
const int kTexelPlayerBulletIndex = 0;
const int kTexelEnemyBulletIndex = 1;
/* @} */

/*! @name ’è‹`ƒOƒ‹[ƒv DotEat
ƒhƒbƒgƒC[ƒg‚ÅŽg—p‚·‚é’è”
*/
/* @{ */
const int kMapVertical = 9;		//! ƒ}ƒbƒv‚Ìs”
const int kMapHorizontal = 12;	//! ƒ}ƒbƒv‚Ì—ñ”
const int kChipWidth = 32;		//! ƒ}ƒbƒvƒ`ƒbƒv
const int kChipHeight = 32;
const XMFLOAT2 kBlockSize = { 32.0f , 32.0f };
const XMFLOAT2 kDotSize = { 16.0f , 16.0f };
const XMFLOAT2 kPlayerSize = { 32.0f , 32.0f };
const XMFLOAT2 kEnemySize = { 32.0f , 32.0f };
/* @} */

/**
 * Œ^
 */

 /**
 * @enum eGameStatus
 * ƒQ[ƒ€‚Ìisó‹µ
 */
typedef enum eGameStatus
{
	eNone,
	eOpening,
	ePlaying,
	eGameClear,
	eGameOver,
	eEnding
}eGameStatus;

/**
* @enum ePhase
* ƒtƒ[‚Ìisó‘Ô
*/
typedef enum ePhase
{
	eBegin = 0,
	eMain,
	eEnd,
}ePhase;

/**
* @enum eScrollMode
* ƒXƒNƒ[ƒ‹•ûŒü
*/
typedef enum eScrollMode
{
	eHorizontal,
	eVirtical
}eScrollMode;

/**
* @enum eObjectState
* ƒLƒƒƒ‰ƒNƒ^‚Ìó‘Ô
*/
typedef enum eObjectState
{
	eWaiting,
	eMoving
}eObjectStatus;

//15==============================================================================
//eDirection 方向
typedef enum eDirection {
	eLeft = 0,
	eRight,
	eUp,
	eDown,
	eCorner,
}eDirection;

typedef enum ePowerType {
	eNoPower = 0,
	eSpeedDown,
	eCatch,
	eLaser,
	eExpand,
	eDisruption,
	eBreak,
	ePlayerExtend, 
	eRelease
}ePower;

typedef enum eBlockColor {
	eWhite = 0,
	eOrange,
	eLightBlue,
	eGreen,
	eRed,
	eBlue,
	ePink,
	eYellow,
	eSilver,
	eGold
}eBlockColor;
//^^==============================================================================