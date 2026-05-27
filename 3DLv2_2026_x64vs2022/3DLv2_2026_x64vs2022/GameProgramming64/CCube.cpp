#include "CCube.h"

//モデルデータの指定
#define MODEL_CUBE "res\\cube.obj", "res\\cube.mtl"

//静的メンバ変数の定義
CModel CCube::msModel;
CCube::CCube()
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty()) {
		//課題 モデルデータを読み込み
		msModel.Load(MODEL_CUBE);
	}
	//モデルポインタの設定
	mpModel = &msModel;
	//課題 コライダの設定
	mCollider[0].Set(
		this,
		&mMatrix,
		CVector(-1.0f, 2.0f, -1.0f),
		CVector(1.0f, 2.0f, 1.0f),
		CVector(1.0f, 2.0f, -1.0f)
		);
	//課題 コライダの設定
	mCollider[1].Set(
		this,
		&mMatrix,
		CVector(-1.0f, 2.0f, -1.0f),
		CVector(-1.0f, 2.0f, 1.0f),
		CVector(1.0f, 2.0f, 1.0f)
		);
}

void CCube::Update()
{
	// 現在の回転を取得
	CVector r = Rotation();
	// Y軸回転を加算
	r = r + CVector(0.0f, 1.0f, 0.0f);
	// 回転を設定
	Rotation(r);

	CTransform::Update();
}