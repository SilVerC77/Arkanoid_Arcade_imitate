#pragma once
#include "GameResource.h"
#include "stdafx.h"
#include "CPicture.h"

class CBlock {
	int iHp;
	int iIndex;
	int iScore;
	int iAnimIndex;
	int iAnimCounter;
	bool bShine;
public:
	CPicture* body;
	CPicture* shadow;
public:
	//コンストラクタ
	CBlock();
	//デストラクタ
	~CBlock();

public:
	XMFLOAT4 getPos()const { return body->getPos(); }					//位置取得
	void setPos(float _x, float _y);
	void setInfo(const string& _color, const int& _round);
	void damage() {										//当たられた時HPを減らす
		iHp--;
		bShine = true;
		iAnimCounter = 0;
		//if (iIndex == 9)body->setAnimation(10);
		//else if (iIndex == 10) body->setAnimation(13);
	}

	void damageAnim(const int& _rate);
	int getIndex()const { return iIndex; }				//番号を取得
	int getHP()const { return iHp; }					//今のHPを取得
	int getScore()const { return iScore; }				//スコア取得
	XMFLOAT2 getSize()const { return body->getSize(); }
	bool getDamage()const { return bShine; }
	bool canDrop() {
		if (iIndex > 10)return true;
		else return false;
	}
};

