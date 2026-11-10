#include "CCube.h"

//モデルデータの指定
#define MODEL_CUBE "res\\cube.obj", "res\\cube.mtl"
//静的メンバ変数の定義
CModel CCube::msModel;

CCube::CCube()
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_CUBE);
	}
	//モデルポインタの設定
	mpModel = &msModel;
	//コライダの設定top
	mCollider[0].Set(this,&mMatrix,
		CVector(-1.0f, 2.0f, -1.0f),CVector(1.0f, 2.0f, 1.0f),CVector(1.0f, 2.0f, -1.0f));
	//コライダの設定top
	mCollider[1].Set(this,&mMatrix,
		CVector(-1.0f, 2.0f, -1.0f),CVector(-1.0f, 2.0f, 1.0f),CVector(1.0f, 2.0f, 1.0f));
	//コライダの設定left
	mCollider[2].Set(this, &mMatrix,
		CVector(1.0f, 2.0f, -1.0f), CVector(-1.0f, 0.0f, -1.0f), CVector(- 1.0f, 2.0f, -1.0f));
	//コライダの設定left
	mCollider[3].Set(this, &mMatrix,
		CVector(1.0f, 2.0f, -1.0f), CVector(1.0f, 0.0f, -1.0f), CVector(-1.0f, 0.0f, -1.0f));
	//コライダの設定front
	mCollider[4].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, -1.0f), CVector(-1.0f, 0.0f, 1.0f), CVector(-1.0f, 2.0f, 1.0f));
	//コライダの設定front
	mCollider[5].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, -1.0f), CVector(-1.0f, 2.0f, 1.0f), CVector(-1.0f, 2.0f, -1.0f));
	//コライダの設定right
	mCollider[6].Set(this, &mMatrix,
		CVector(1.0f, 2.0f, 1.0f), CVector(-1.0f, 2.0f, 1.0f), CVector(-1.0f, 0.0f, 1.0f));
	//コライダの設定right
	mCollider[7].Set(this, &mMatrix,
		CVector(1.0f, 2.0f, 1.0f), CVector(-1.0f, 0.0f, 1.0f), CVector(1.0f, 0.0f, 1.0f));
	//コライダの設定back
	mCollider[8].Set(this, &mMatrix,
		CVector(1.0f, 2.0f, 1.0f), CVector(1.0f, 0.0f, -1.0f), CVector(1.0f, 2.0f, -1.0f));
	//コライダの設定back
	mCollider[9].Set(this, &mMatrix,
		CVector(1.0f, 2.0f, 1.0f), CVector(1.0f, 0.0f, 1.0f), CVector(1.0f, 0.0f, -1.0f));
}

void CCube::Update()
{
	CTransform::Update();
}
