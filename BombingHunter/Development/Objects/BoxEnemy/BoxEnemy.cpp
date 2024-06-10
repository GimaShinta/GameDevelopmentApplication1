#include "BoxEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"
#include "../Bomb/Bomb.h"
#include "../Player/Player.h"

BoxEnemy::BoxEnemy():animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

BoxEnemy::~BoxEnemy()
{
}

void BoxEnemy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ボックスエネミーの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0);

}

void BoxEnemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();
}

void BoxEnemy::Draw() const
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

void BoxEnemy::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	if (dynamic_cast<BoxEnemy*>(hit_object) != nullptr)
	{
		delete_flag = FALSE;
	}
	else
	{
		delete_flag = TRUE;
	}
}

void BoxEnemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
	if (((location.x + direction.x) < box_size.x)
		|| (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	//進行方向に向かって、位置座標を変更する
	location += direction;
}

void BoxEnemy::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
