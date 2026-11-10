#include "CTestScene.h"
#include "CCharacter3.h"
#include "CTaskManager.h"
#include "CCube.h"
#include "CXPlayer.h"
#include "CCamera.h"


CTestScene::CTestScene() : CSceneBase(EScene::eTest)
{

}

void CTestScene::Load()
{

	//床
	CCharacter3* floor = new CCube();
	floor->Position(CVector(0.0f, -1.0f, 0.0f));
	floor->Scale(CVector(40.0f, 0.5f, 50.0f));//80.0f, 0.5f, 50.0f
	//壁
	CCharacter3* wall = new CCube();
	wall->Position(CVector(0.0f, 0.0f, 0.0f));
	wall->Scale(CVector(2.0f, 10.0f, 40.0f));
	//高台
	CCharacter3* box1 = new CCube();
	box1->Position(CVector(-7.0f, 0.0f, 0.0f));
	box1->Scale(CVector(5.0f, 5.0f, 5.0f));
	//障害物１
	CCharacter3* box2 = new CCube();
	box2->Position(CVector(20.0f, 0.0f, 0.0f));
	box2->Scale(CVector(2.5f, 2.5f, 2.5f));
	//障害物２
	CCharacter3* box3 = new CCube();
	box3->Position(CVector(40.0f, 0.0f, 0.0f));
	box3->Scale(CVector(2.5f, 2.5f, 2.5f));
	//坂道
	CCharacter3* slope = new CCube();
	slope->Position(CVector(15.0f, 5.0f, 30.0f));
	slope->Scale(CVector(20.0f, 2.0f, 7.0f));
	slope->Rotation(CVector(0.0f,0.0f,-36.0f));
	//階段1
	CCharacter3* stair1 = new CCube();
	stair1->Position(CVector(-15.0f, 5.0f, -30.0f));
	stair1->Scale(CVector(20.0f, 2.0f, 7.0f));
	stair1->Rotation(CVector(0.0f, 0.0f, 36.0f));
	//階段2
	CCharacter3* stair2 = new CCube();
	stair2->Position(CVector(15.0f, 5.0f, -30.0f));
	stair2->Scale(CVector(20.0f, 2.0f, 7.0f));
	stair2->Rotation(CVector(0.0f, 0.0f, -36.0f));

	mPlayer.Load(MODEL_FILE);
	CXCharacter* xchar = new CXPlayer();
	xchar->Init(&mPlayer);
	
	//カメラ位置の設定
	CCamera::Instance()->Scale(CVector(0.0f, 1.0f, -7.0f));
}

void CTestScene::Update()
{
	//カメラの設定
	/*gluLookAt(1.0f, 25.0f, 80.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 1.0f, 0.0f);*/

	//全キャラクタの更新
	CTaskManager::Instance()->Update();
	//カメラの更新
	CCamera::Instance()->Update();
	//衝突処理の呼び出し
	CTaskManager::Instance()->Collision();
	//全キャラクタの描画
	CTaskManager::Instance()->Render();

}
