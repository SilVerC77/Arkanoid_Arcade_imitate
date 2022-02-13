/**
* @file COriginalGameApp.h
* @author 織戸　喜隆
* @date 日付（2017.02.14）
*/
#pragma once
#pragma once

#include "stdafx.h"
#include "CApplication.h"
#include "CPicture.h"
#include "MediaResource.h"
#include "UVAnimation.h"
#include "CFont.h"
#include "Original/CVaus.h"
#include "Original/Block.h"
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//作成者：汪博
//#include "BGM.h"
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
// 作成者：細田弥卯（2021_09_29）
#include "CSound.h"
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
 //___________________________________________________________________________________________________
 //変数定義
 //__________________________________________________________________________________________________
struct Record {
	int score;
	int digit;
	int round;
	string name;
};

class COriginalGameApp :
	public CApplication
{
	typedef CApplication super;
private:
	int m_activeEnemies = 0;

	CPicture* createSprite(LPCWSTR path_, float width_ = WINDOW_WIDTH, float height_ = WINDOW_HEIGHT);
	void renderSprite(CPicture* object);
	void renderSprite(CPicture* object, XMFLOAT3 color);
	void renderSprite(CPicture* object, XMFLOAT4 color);
	void disposeSprite(CPicture* object);
	CFont* createFont(LPCWSTR path_, int digits, float width = WINDOW_WIDTH, float height = WINDOW_HEIGHT);
	void renderFont(CFont* object, int num_);
	void disposeFont(CFont* objects);
	bool createSpaceship(void);
	void initCameraInfo();
	void doOpenning();
	void doPlaying();
	void doGameClear();
	void doGameOver();
	void doEnding();

	void procTitle();
	void procGame();
	void procClear();
	void procOver();
	void procResult();

	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//作成者：細田弥卯　音声作成、プレイ、破棄
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	CSound* createSound(const char* filePath_, const bool loop_ = false);
	void playSound(CSound* const objects);
	void disposeSound(CSound* const objects);
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿

	//________________________________________________________________________
	//蝦名伸太郎　許弘毅　追加
	//________________________________________________________________________
	const XMFLOAT2 FONT_SIZE = { 34.0f,29.0f };		//スコアのサイズ
	const XMFLOAT2 SCORE_POS = { -250.f,490.f };		//スコアの位置
	const XMFLOAT2 HISCORE_POS = { 83.f,490.f };		//ハイスコアの位置
	const XMFLOAT2 HEADER_POS = { -98.f,525.5f };
	const XMFLOAT2 HEADER_SIZE = { 530.f,29.f };
	Record g_sRecord[5] = { {0,0,0,""},{0,0,0,""},{0,0,0,""},{0,0,0,""},{0,0,0,""}, };
	Record g_sRecordNow = { 0,0,0,"" };
	CSound* g_pSound = NULL;
	CPicture* g_pHeader = NULL;
	CFont* g_pScore = NULL;								//スコア
	CFont* g_pHiScore = NULL;							//ハイスコア
	int g_iScore = 0;									//スコア値
	int g_iDigit = 1;									//変動するスコアの桁数
	int g_iHiScore = 0;
	int g_iHiDigit = 1;
	int g_iAllScore[5];
	bool g_bNewRecord=true;

	void procTitleBegin();
	void procTitleMain();
	void procTitleEnd();
	void procPlayBegin();
	void procPlayMain();
	void procPlayEnd();
	void procOverBegin();
	void procOverMain();
	void procOverEnd();
	void procClearBegin();
	void procClearMain();
	void procClearEnd();
	void procResultBegin();
	void procResultMain();
	void procResultEnd();
	
	void procHeader();

	void renderFont(CFont* object, string _str);
	CPicture* createSprite(LPCWSTR path_, const XMFLOAT2 _size, const XMFLOAT2 _pos = { 0.f,0.f });
	void setSound(const char* _sfx);
	//function
	float DegtoRad(float _degree);
	float calLength(XMFLOAT2 _a, XMFLOAT2 _b);
	float calLength(XMFLOAT4 _a, XMFLOAT4 _b);
	void drawRect(const string _color = "green", const XMFLOAT2 _pos = { 0.f,0.f }, const XMFLOAT2 _size = { 10.f,10.f });
	void drawLine(const string _color, XMFLOAT4 _start, XMFLOAT4 _end);
	void drawLine(const string _color, XMFLOAT4 _start, float _length, float _degree);
	void ShowScore(CFont*& _font, const int& _score, int& _digit, const XMFLOAT2 _pos, const XMFLOAT2 _size);
	int calDigit(int _number) {
		int digit = 0;
		do {
			_number /= 10;
			digit++;
		} while (_number > 0);
		return digit;
	}

	void StageBlock();

public:
	COriginalGameApp();
	~COriginalGameApp();
	void render(XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
	void release();
};
