#include "Block.h"

CBlock::CBlock() :
	body(NULL),
	shadow(NULL),
	iHp(0),
	iIndex(0),
	iScore(0),
	iAnimIndex(0),
	iAnimCounter(0),
	bShine(true)
{};
CBlock::~CBlock()
{
	if (body) body->release();
	if (shadow)shadow->release();
};

void CBlock::setPos(float _x, float _y)
{									//位置を設定
	if (body)	body->setPos(_x, _y);
	if (shadow) shadow->setPos(_x + getSize().x / 2.f, _y - getSize().y);
}

void CBlock::setInfo(const string& _color, const int& _round)
{				//基本情報設定
		//受け取った文字列を番号にする
	if (_color == "White") iIndex = 1;
	else if (_color == "Orange") iIndex = 2;
	else if (_color == "LightBlue") iIndex = 3;
	else if (_color == "Green") iIndex = 4;
	else if (_color == "Red") iIndex = 5;
	else if (_color == "Blue") iIndex = 6;
	else if (_color == "Pink") iIndex = 7;
	else if (_color == "Yellow") iIndex = 8;
	else if (_color == "Silver") iIndex = 9;
	else if (_color == "Gold") iIndex = 10;
	else if (_color == "White_Item") iIndex = 11;
	else if (_color == "Orange_Item") iIndex = 12;
	else if (_color == "LightBlue_Item") iIndex = 13;
	else if (_color == "Green_Item") iIndex = 14;
	else if (_color == "Red_Item") iIndex = 15;
	else if (_color == "Blue_Item") iIndex = 16;
	else if (_color == "Pink_Item") iIndex = 17;
	else if (_color == "Yellow_Item") iIndex = 18;
	else iIndex = 0;

	//Silverの時のHPはラウンドによる違う
	//Goldは壊せないから大きい数字を渡す
	//それ以外の色は一回で壊せる
	if (iIndex == 9) {
		if (_round <= 8)		iHp = 2;
		else if (_round <= 16)	iHp = 3;
		else if (_round <= 24)	iHp = 4;
		else if (_round > 24)	iHp = 5;
	}
	else if (iIndex == 10)	iHp = INT_MAX;
	else iHp = 1;

	//ブロックのスコアを与える
	if (iIndex == 1 || iIndex == 11) iScore = 50;
	else if (iIndex == 2 || iIndex == 12) iScore = 60;
	else if (iIndex == 3 || iIndex == 13) iScore = 70;
	else if (iIndex == 4 || iIndex == 14) iScore = 80;
	else if (iIndex == 5 || iIndex == 15) iScore = 90;
	else if (iIndex == 6 || iIndex == 16) iScore = 100;
	else if (iIndex == 7 || iIndex == 17) iScore = 110;
	else if (iIndex == 8 || iIndex == 18) iScore = 120;
	else iScore = 0;

	int color = (iIndex - 1) % 10;
	if (body) body->setAnimation(color);
	//フラグ初期化
	bShine = true;
}

void CBlock::damageAnim(const int& _rate)
{
	if (iIndex != 9 && iIndex != 10)return;
	int animindex = body->getAnimIndex();
	if (bShine) {
		if (animindex == 8)animindex = 10;
		else if (animindex == 9)animindex = 13;
		iAnimCounter++;
	}
	if (iAnimCounter > _rate) {
		iAnimCounter = 0;
		animindex++;
	}
	if (iIndex == 9) {
		if (animindex > 12) {
			animindex = 8;
			bShine = false;
		}
	}
	else if (iIndex == 10) {
		if (animindex > 15) {
			animindex = 9;
			bShine = false;
		}
	}
	body->setAnimation(animindex);
}
