#ifndef CTASK_H
#define CTASK_H
class CTaskManager;
class CCollisionManager;
//識別タグ
enum class ETag {
	ENONE, //未設定
	EPLAYER, //プレイヤー
	ESWORD, //剣
};
/*
タスククラス
タスクリストの要素
*/
class CTask {
	friend CTaskManager;
	friend CCollisionManager;
public:
	// タグの取得
	ETag& Tag() { return mTag; }
	//タグの設定
	//tag :識別タグ
	void Tag(ETag tag) { mTag = tag; }
	//衝突処理
	virtual void Collision() {}

	//デフォルトコンストラクタ
	CTask()
		: mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true), mTag(ETag::ENONE) {}
	//デストラクタ virtualにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask() {}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}
protected:
	int mPriority;	//優先度
	bool mEnabled;	//有効フラグ
private:
	ETag mTag; //識別タグ
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
};

#endif
