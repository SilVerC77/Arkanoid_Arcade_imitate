/* Vaus
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021 / 09 / 29
 */
#pragma once
#include "CPicture.h"
const float PI = (float)3.14159;	//π

 //Vausのクラス=========================================================================
class CVaus {
	ePowerType ePower;				//パワー
	ePowerType eOldPower;			//前のパワー
	float fSpeed;					//Vaus移動速度
	int iCounter;					//連弾の間隔
	bool bStart;					//開始時ボールを持つ

//外で呼び出したい画像
public:
	CPicture* body = NULL;					//アニメーション
	CPicture* shadow = NULL;				//Vausの影
	CPicture* dead = NULL;
	CPicture* laser[2];	//弾
public:
	//コンストラクタ
	CVaus();
	//デストラクタ
	~CVaus();
	//メソッド
public:
	XMFLOAT2 getSize()const { return body->getSize(); }		//サイズ取得	
	XMFLOAT4 getPos()const { return body->getPos(); }		//位置取得
	ePowerType getPower()const { return ePower; }			//パワー取得
	void setPos(XMFLOAT2 _pos);								//位置設定
	void setPos(XMFLOAT4 _pos);								//位置設定
	void setPos(float _posx, float _posy);					//位置設定
	void move(BOOL _left, BOOL _right);						//移動処理
	void move(float _BallPos);								//自動移動
	void border(float _left, float _right,					//移動制限
		bool _break = false);
	//void procLaser();										//弾処理
	void releaseBall(BOOL _press);							//ボール発射
	bool canShoot(const float _speed, const int _rate, BOOL _press);
	bool powerChange();										//パワー変えたか
	void setPower(ePowerType _power) {						//パワー変える
		ePower = _power;
		iCounter = 0;//初期化
	}
	void dispose();
};

//Ballのクラス=========================================================================
class CBall {
	XMFLOAT2 f2Dir;			//Ball方向
	XMFLOAT2 f2OldPos;		//前の位置
	float fSpeed;			//Ball速さ
	float fRad;				//Ball角度
	float fOffset;			//ずれた距離
	bool bfly;				//Ball動かせるフラグ
	bool bDead;				//Ballのフラグ
public:
	CPicture* body = NULL;			//アニメーション
	CPicture* shadow = NULL;		//Ballの影
public:
	//コンストラクタ
	CBall(float _degree = 60.f, float _speed = 12.f, bool _fly = false);
	~CBall();
public:
	XMFLOAT2 getSize()const { return body->getSize(); }							//サイズ取得
	XMFLOAT4 getPos()const { return body->getPos(); };					//位置取得
	void move(const float _limit = 100.f);								//移動
	void border(float _left, float _top, float _right					//移動範囲とその処理
		, float _bottom = WINDOW_TOP);
	void setPos(XMFLOAT4 _pos);											//位置設定
	void setPos(float _x, float _y);
	void setPos(CVaus* _vaus);
	float getAngle(const char _unit = 'd')const;						//移動角度取得
	void setAngle(float _degree);										//移動角度設定
	float getSpeed()const { return fSpeed; }
	void setSpeed(float _speed) { fSpeed = _speed; }
	bool collisionRay(CPicture* _target, XMFLOAT2& _contact,			//レイ
		float& hit_near, eDirection& _direction);
	void bounce(eDirection _dir, CPicture* _target = NULL);				//跳ね
	void bounce(CVaus* _vaus);											//Vausとの処理
	void disposeBall();
};