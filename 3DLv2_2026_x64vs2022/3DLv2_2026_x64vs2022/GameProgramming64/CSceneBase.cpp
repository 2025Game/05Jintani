#include "CSceneBase.h"


//コンストラクタ
CSceneBase::CSceneBase(EScene scene)
{
	mSceneType = scene;
}

EScene CSceneBase::GetSceneType() const
{
	return mSceneType;
}
