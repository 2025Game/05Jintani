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
	//コライダの設定
	mCollider[0].Set(this,&mMatrix,
		CVector(-1.0f, 2.0f, -1.0f),CVector(1.0f, 2.0f, 1.0f),CVector(1.0f, 2.0f, -1.0f));
	//コライダの設定
	mCollider[1].Set(this,&mMatrix,
		CVector(-1.0f, 2.0f, -1.0f),CVector(-1.0f, 2.0f, 1.0f),CVector(1.0f, 2.0f, 1.0f));
	//コライダの設定
	mCollider[2].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, -1.0f), CVector(1.0f, 2.0f, -1.0f), CVector(- 1.0f, 2.0f, -1.0f));
	//コライダの設定
	mCollider[3].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, -1.0f), CVector(1.0f, 0.0f, -1.0f), CVector(1.0f, 2.0f, -1.0f));
	//コライダの設定
	mCollider[4].Set(this, &mMatrix,
		CVector(- 1.0f, 0.0f, -1.0f), CVector(-1.0f, 2.0f, 1.0f), CVector(-1.0f, 2.0f, -1.0f));
	//コライダの設定
	mCollider[5].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, -1.0f), CVector(-1.0f, 0.0f, 1.0f), CVector(-1.0f, 2.0f, 1.0f));
	//コライダの設定
	mCollider[6].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, 1.0f), CVector(1.0f, 2.0f, 1.0f), CVector(-1.0f, 2.0f, 1.0f));
	//コライダの設定
	mCollider[7].Set(this, &mMatrix,
		CVector(-1.0f, 0.0f, 1.0f), CVector(1.0f, 0.0f, 1.0f), CVector(1.0f, 2.0f, 1.0f));
	//コライダの設定
	mCollider[8].Set(this, &mMatrix,
		CVector(1.0f, 0.0f, -1.0f), CVector(1.0f, 2.0f, 1.0f), CVector(1.0f, 2.0f, -1.0f));
	//コライダの設定
	mCollider[9].Set(this, &mMatrix,
		CVector(1.0f, 0.0f, -1.0f), CVector(1.0f, 0.0f, 1.0f), CVector(1.0f, 2.0f, 1.0f));
}

void CCube::Update()
{
	CTransform::Update();
}
