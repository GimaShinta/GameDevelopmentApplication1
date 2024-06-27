#include "EnemyBullet.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//型変換用
#include "../Player/Player.h"

EnemyBullet::EnemyBullet() :animation_count(0)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

EnemyBullet::~EnemyBullet()
{
}

//初期化処理
void EnemyBullet::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	//エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("テキ弾の画像がありません\n");
		}
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = (64.0f/3)*2;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0, 0);

}

//更新処理
void EnemyBullet::Update()
{
	//移動処理
	Movement();

	if (animation_flag == TRUE)
	{
		//アニメーション制御
		AnimationControl();
	}
}

//描画処理
void EnemyBullet::Draw() const
{
	//情報を基にテキ弾の画像を描画する
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void EnemyBullet::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//当たり判定通知処理
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//ヒット時通知
	if (dynamic_cast<Player*>(hit_object) != nullptr)
	{
		//消す（アニメーション可能）
		animation_flag = TRUE;

		//スコア
		score += -100;
	}
	else
	{
		//消さない
		animation_flag = FALSE;
	}
}

//移動処理
void EnemyBullet::Movement()
{
	//進行方向に向かって、位置座標を変更する
	if (animation_flag == TRUE)
	{
		direction = 0;
	}
	location += direction;
}

//アニメーション制御
void EnemyBullet::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//15フレーム目に到達したら
	if (animation_count >= 15)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if(image==animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else
		{
			//消す
			delete_flag = TRUE;
		}
	}
}
