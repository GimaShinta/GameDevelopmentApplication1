#include "Bomb.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"
#include "../Player/Player.h"

Bomb::Bomb() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Bomb::~Bomb()
{
}

void Bomb::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");

	//エラーチェック
	if (animation[0] == -1)
	{
		throw("ボックスエネミーの画像がありません\n");
	}

	//向きの設定
	radian = -1.6f;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0, 1.0f);
}

void Bomb::Update()
{
	//移動処理
	Movement();
}

void Bomb::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基にハコテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

void Bomb::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Bomb::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		delete_flag = FALSE;
	}
	else
	{
		delete_flag = TRUE;
	}
}

void Bomb::Movement()
{
	//進行方向に向かって、位置座標を変更する
	location += direction;
}
