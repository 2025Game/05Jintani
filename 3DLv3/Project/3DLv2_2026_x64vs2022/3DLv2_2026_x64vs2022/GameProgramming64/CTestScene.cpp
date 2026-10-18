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

	//°
	CCharacter3* floor = new CCube();
	floor->Position(CVector(0.0f, -1.0f, 0.0f));
	floor->Scale(CVector(80.0f, 0.5f, 50.0f));
	//•Ç
	CCharacter3* wall = new CCube();
	wall->Position(CVector(0.0f, 0.0f, 0.0f));
	wall->Scale(CVector(2.0f, 10.0f, 40.0f));
	//‚‘ä
	CCharacter3* box1 = new CCube();
	box1->Position(CVector(-7.0f, 0.0f, 0.0f));
	box1->Scale(CVector(5.0f, 5.0f, 5.0f));
	//áŠQ•¨‚P
	CCharacter3* box2 = new CCube();
	box2->Position(CVector(20.0f, 0.0f, 0.0f));
	box2->Scale(CVector(2.5f, 2.5f, 2.5f));
	//áŠQ•¨‚Q
	CCharacter3* box3 = new CCube();
	box3->Position(CVector(40.0f, 0.0f, 0.0f));
	box3->Scale(CVector(2.5f, 2.5f, 2.5f));
	//â“¹
	CCharacter3* slope = new CCube();
	slope->Position(CVector(15.0f, 5.0f, 30.0f));
	slope->Scale(CVector(20.0f, 2.0f, 7.0f));
	slope->Rotation(CVector(0.0f,0.0f,-36.0f));
	//ŠK’i1
	CCharacter3* stair1 = new CCube();
	stair1->Position(CVector(-15.0f, 5.0f, -30.0f));
	stair1->Scale(CVector(20.0f, 2.0f, 7.0f));
	stair1->Rotation(CVector(0.0f, 0.0f, 36.0f));
	//ŠK’i2
	CCharacter3* stair2 = new CCube();
	stair2->Position(CVector(15.0f, 5.0f, -30.0f));
	stair2->Scale(CVector(20.0f, 2.0f, 7.0f));
	stair2->Rotation(CVector(0.0f, 0.0f, -36.0f));

	mPlayer.Load(MODEL_FILE);
	CXCharacter* xchar = new CXPlayer();
	xchar->Init(&mPlayer);
	
	//ƒJƒƒ‰ˆÊ’u‚Ìİ’è
	CCamera::Instance()->Scale(CVector(0.0f, 1.0f, -7.0f));
}

void CTestScene::Update()
{
	//ƒJƒƒ‰‚Ìİ’è
	/*gluLookAt(1.0f, 25.0f, 80.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 1.0f, 0.0f);*/
		//ƒJƒƒ‰‚ÌXV
	CCamera::Instance()->Update();
	//‘SƒLƒƒƒ‰ƒNƒ^‚ÌXV
	CTaskManager::Instance()->Update();
	//‘SƒLƒƒƒ‰ƒNƒ^‚Ì•`‰æ
	CTaskManager::Instance()->Render();

}
