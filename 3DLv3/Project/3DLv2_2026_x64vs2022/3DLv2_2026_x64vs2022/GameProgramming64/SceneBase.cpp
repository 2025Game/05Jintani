#include "SceneBase.h"

CSceneBase::CSceneBase(EScene scene)
{
	mSceneType = scene;
}

EScene CSceneBase::GetSceneType() const
{
	return mSceneType;
}
