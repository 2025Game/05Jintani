#include "CApplication3.h"

CApplication3::CApplication3()
{

}

CApplication3::~CApplication3()
{

}

void CApplication3::Start()
{
	//タイトルシーンのインスタンスを作成
	mpScene = std::make_unique<CTestScene>();
	mpScene->Load();	//テストシーンのロード

}

void CApplication3::Update()
{
	mpScene->Update();	//テストシーンの更新
}
