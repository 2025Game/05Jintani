#include "CCamera.h"
#include "glut.h"

#define ROTATION_RATE 0.5f

CCamera* CCamera::spInstance = nullptr;
CCamera* CCamera::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CCamera();
	}
	return spInstance;
}

void CCamera::Start(double left, double right
	, double bottom, double top)
{
	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

	//プロジェクション行列への切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//表示エリアの設定
	gluOrtho2D(left, right, bottom, top);
}

void CCamera::End()
{
	//プロジェクション行列を戻す
	glPopMatrix();
	//モデルビューモードへ切り替え
	glMatrixMode(GL_MODELVIEW);

	//モデルビュー行列を戻す
	glPopMatrix();
	//Depthテストオン
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void CCamera::Update()
{
	//課題 Jキーで左回転、Lキーで右回転
	if (mInput.Key('J'))
	{
		mRotation = mRotation + CVector(0.0f, 2.0f, 0.0f);
	}
	else if (mInput.Key('L'))
	{
		mRotation = mRotation + CVector(0.0f, -2.0f, 0.0f);
	}

	// Nキーでマウスカーソルを非表示
	if (mInput.Key('N'))
	{
		mInput.MouseShowCursor(false);
	}
	// Mキーでマウスカーソルを表示
	if (mInput.Key('M'))
	{
		mInput.MouseShowCursor(true);
	}

	CTransform::Update();
	//カメラの位置、注視点、上方向を計算する
	CVector mCenter = CVector() * mMatrix;
	CVector mEye = CVector(1.0f, 1.0f, 1.0f) * mMatrix;
	CVector mUp = CVector(0.0f, 1.0f, 0.0f);
	//カメラの位置、注視点、上方向を設定する
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z()
		, mCenter.X(), mCenter.Y(), mCenter.Z()
		, mUp.X(), mUp.Y(), mUp.Z());

	double x, y;
	//マウスの位置を取得する
	mInput.MouseGetPosition(&x, &y);
	//前回のマウスの位置と今回のマウスの位置の差分を計算して、
	//カメラの回転に反映する
	Rotation(Rotation() + CVector(0.0f, (mX - x) * ROTATION_RATE, 0.0f));
	//マウスの位置を保存する
	mX = x;
	mY = y;

	// モデルビュー行列を取得する
	glGetFloatv(
		GL_MODELVIEW_MATRIX,
		mModelViewMatrix.M());

	// モデルビュー行列の逆行列を求める
	mModelViewInverse =
		mModelViewMatrix.Inverse();

	// 移動成分をクリア
	mModelViewInverse.M()[3] = 0.0f;
	mModelViewInverse.M()[7] = 0.0f;
	mModelViewInverse.M()[11] = 0.0f;
	mModelViewInverse.M()[12] = 0.0f;
	mModelViewInverse.M()[13] = 0.0f;
	mModelViewInverse.M()[14] = 0.0f;
}

void CCamera::Parent(CTransform* parent)
{
	mpParent = parent;
}

const CMatrix& CCamera::ModelViewInverse()
{
	return mModelViewInverse;
}