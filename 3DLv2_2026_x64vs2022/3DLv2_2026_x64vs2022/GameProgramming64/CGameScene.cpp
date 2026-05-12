#include "CGameScene.h"
#include "CCharacter3.h"
#include "CTaskManager.h"
#include "CXPlayer.h"
//背景モデルデータの指定
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
{
}
void CGameScene::Load()
{
	//課題 背景モデルデータの読み込み
	mBackGround.Load(MODEL_BACKGROUND);
	//キャラクタのインスタンス作成
	CCharacter3* character = new CCharacter3();
	//キャラクタのモデルの設定
	character->Model(&mBackGround);
	mPlayer.Load(MODEL_FILE);
	CXCharacter* xchar = new CXPlayer();
	xchar->Init(&mPlayer);
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
}
void CGameScene::Update()
{
	//カメラの設定
	gluLookAt(1.0f, 2.0f, 10.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	//全キャラクタの更新
	CTaskManager::Instance()->Update();
	//衝突処理の呼び出し
	CTaskManager::Instance()->Collision();
	//課題 全キャラクタの描画
	CTaskManager::Instance()->Render();
	//コライダの描画
	CCollisionManager::Instance()->Render();
}