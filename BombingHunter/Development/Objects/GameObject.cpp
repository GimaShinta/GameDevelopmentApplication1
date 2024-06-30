#include "GameObject.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	image_size(0.7),
	number_size(1.0),
	radian(0.0f),
	image(NULL),
	sound(NULL),
	delete_flag(FALSE),
	flip_flag(FALSE),
	animation_flag(FALSE),
	anumber_flag(FALSE),
	score(0),
	transparent(255),
	gradually(-5),
	anim_count(0),
	reach_count(0)
{
}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{

}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{
	//当たり判定の可視化
	//Vector2D t1 = location - (box_size / 2.0f);
	//Vector2D br = location + (box_size / 2.0f);

	//DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

//終了時処理
void GameObject::Finalize()
{

}

//各オブジェクトの削除フラグ取得
bool GameObject::GetDeleteFlag()
{
	return this->delete_flag;
}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//スコアの値を取得
int GameObject::GetScore()
{
	return this->score;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//進行方向設定処理
void GameObject::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

//画像反転フラグの取得
void GameObject::SetFlipFlag(bool flag)
{
	this->flip_flag = flag;
}

//当たり判定の大きさを取得する
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}
