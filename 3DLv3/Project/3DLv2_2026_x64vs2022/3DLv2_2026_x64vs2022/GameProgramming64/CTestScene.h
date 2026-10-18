#pragma once
#ifndef CTESTSCENE_H
#define CTESTSCENE_H

#include "CSceneBase.h"
#include "CModel.h"
#include "CXCharacter.h"
#include "CColliderMesh.h"

//テストシーン
class CTestScene :public CSceneBase
{
public:
	CTestScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
private:
	CModelX mPlayer;
	CColliderMesh mColliderMesh; //メッシュコライダ
};

#endif
